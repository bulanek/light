#include <user_config.h>
#include <SmingCore/SmingCore.h>

#include "../include/DataParser.hpp"
#include "../include/Definitions.h"
#include "spi_flash.h"

// If you want, you can define WiFi settings globally in Eclipse Environment Variables

// CONSTANTS

const uint8_t PINS_LIGHT_SWITCH[] = { 13, 12, 14, 16 };
/// Number of used lights
const uint8_t LIGHTS_USED = 3;

const uint8_t PIN_LIGHT_INTERRUPT = 4;
const uint8_t PIN_PIR_ENABLE = 2;
const uint8_t PIN_PIR_OUTPUT = 5;
// TODO check the pin
const uint8_t PIN_WIFI_ENABLE = 1;

const uint16_t LIGHT_TIMEOUT_MS = 10000U;

const String CONFIG_NAME  = "light.conf";

const uint32_t CONFIGURATION_DATA_ADDRESS = 0xC0000;

// FUNCTIONS

void tcpServerClientConnected(TcpClient* client);
bool tcpServerClientReceive(TcpClient& client, char *data, int size);
void tcpServerClientComplete(TcpClient& client, bool succesfull);

/// Set or get lights
static inline void setLights(DataParser& rDataParser);
static inline void setPIR(DataParser& rDataParser);

static void writeDefaultConfig(DataParser& rDataParser);

// Will be called when WiFi hardware and software initialization was finished
// And system initialization was completed
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ready(void);
static inline void setupGPIO(void);
static inline void setupWifi(void);

/// GLOBAL VARIABLES

DataParser f_DataParser;
TcpServer f_Server(tcpServerClientConnected, tcpServerClientReceive,
                tcpServerClientComplete);
/// Timer started while change of light.
Timer f_Timer;
/// All lights are on
volatile uint16_t f_LightsOn = 1;

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void PirOutputChangeTimerCallback(void)
{
    noInterrupts();
    f_LightsOn = 0U;
    f_DataParser.SetLightOn(0U);
    for (uint8_t i = 0; i < LIGHTS_USED; ++i)
    {
        digitalWrite(PINS_LIGHT_SWITCH[i], 0U);
    }
    interrupts();
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void IRAM_ATTR InterruptPIRChange(void)
{
    noInterrupts();
    uint8_t pirValue = digitalRead(PIN_PIR_OUTPUT);
    Serial.println("In InterruptPIRChange ");
    f_Timer.stop();

    if ((f_LightsOn == 0U) && (pirValue == 1U))
    {
        f_LightsOn = 1U;
        f_DataParser.SetLightOn(1U);
        for (uint8_t i = 0U; i < LIGHTS_USED; ++i)
        {
            digitalWrite(PINS_LIGHT_SWITCH[i], (f_DataParser.GetLight(i) != 0));
        }
    }

    if (pirValue == 0U)
    {
        f_Timer.restart();
    }
    interrupts();
}

////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void IRAM_ATTR InterruptLightChange(void)
{
    noInterrupts();
    Serial.println("In InterruptLightChange ");
    static uint8_t counterConfig = 0U;
    f_DataParser.SetConfigurationLight(counterConfig);
    if (f_LightsOn == 0U)
    {
        f_LightsOn = 1U;
        f_DataParser.SetLightOn(f_LightsOn);
    }
    for (int i = 0; i < DataParser::NUM_LIGHT; ++i) {
        digitalWrite(PINS_LIGHT_SWITCH[i], (f_DataParser.GetLight(i) != 0U));
    }
    interrupts();
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME: tcpServerClientConnected
////////////////////////////////////////////////////////////////////////////////
void tcpServerClientConnected(TcpClient* client)
{
    debugf("Application onClientCallback : %s\r\n",
                    client->getRemoteIp().toString().c_str());

    char message[] = "Connected to IP_ADDRESS";
    if(!client->send(message, sizeof(message)))
    {
        debugf("failed to response on connection");
    }
    const ConfigurationData data = f_DataParser.GetConfData();

    if (!client->send((const char*) &data, CONFIGURATION_DATA_SIZE))
    {
        debugf("Failed to send connection response\n");
    }
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME: tcpServerClientReceive
////////////////////////////////////////////////////////////////////////////////
bool tcpServerClientReceive(TcpClient& client, char *data, int size)
{
    debugf("Application DataCallback : %s, %d bytes \r\n",
                    client.getRemoteIp().toString().c_str(), size);
    // One byte information
    if (size == CONFIGURATION_DATA_SIZE)
    {
        f_DataParser.SetConfData(*(ConfigurationData*) data);

        // Lights with lightsOn
        setLights(f_DataParser);
        // PIR enable
        setPIR(f_DataParser);
        const ConfigurationData data = f_DataParser.GetConfData();

        if (f_DataParser.GetLightFlag() != 0)
        {
            spi_flash_write(CONFIGURATION_DATA_ADDRESS, (uint32_t*) &data,
                            CONFIGURATION_DATA_SIZE);
        }
        // TODO htons
        if (!client.send((const char*) &data, CONFIGURATION_DATA_SIZE))
        {
            debugf("Failed to send response\n");
        }
    }
    else
    {
        debugf("Unexpected data length, %i\n", size);
    }
    return true;
}

void setLights(DataParser& rDataParser)
{
    if (rDataParser.GetLightFlag() != 0)
    {
        f_LightsOn = rDataParser.GetLightOn();
        if (f_LightsOn)
        {
            for (uint8_t i = 0; i < LIGHTS_USED; ++i)
            {
                digitalWrite(PINS_LIGHT_SWITCH[i],
                                (rDataParser.GetLight(i) != 0));
            }
        }
        else
        {
            for (uint8_t i = 0; i < LIGHTS_USED; ++i)
            {
                digitalWrite(PINS_LIGHT_SWITCH[i], 0U);
            }
        }
    }
    else
    {
        rDataParser.SetLightOn(f_LightsOn);
        if (f_LightsOn)
        {
            for (uint16_t i = 0; i < LIGHTS_USED; ++i)
            {
                rDataParser.SetLight(i, (uint16_t) digitalRead(i));
            }
        }
    }
}

void setPIR(DataParser& rDataParser)
{
    if (rDataParser.GetLightFlag() != 0)
    {
        debugf("Set PIR");
        digitalWrite(PIN_PIR_ENABLE, (rDataParser.GetPIREnable() != 0));
        if (rDataParser.GetPIREnable() == 0)
        {
            debugf("GetPir Enable 0");

            if (f_Timer.isStarted())
            {
                f_Timer.stop();
            }
        }
    }
    else
    {
        rDataParser.SetPIREnable(digitalRead(PIN_PIR_ENABLE));
        debugf("Get PIR enable %i", rDataParser.GetPIREnable());
    }
}

void writeDefaultConfig(DataParser& rDataParser)
{
    for (uint8_t i = 0; i < DataParser::NUM_LIGHT; ++i)
    {
        rDataParser.SetLight(i, 1);
    }
    rDataParser.SetLightOn(1U);
    rDataParser.SetPIREnable(1U);
    rDataParser.SetConfiguration(DataParser::DEFAULT_CONFIGURATION);
}

void tcpServerClientComplete(TcpClient& client, bool succesfull)
{
    debugf("Application CompleteCallback : %s \r\n",
                    client.getRemoteIp().toString().c_str());
}


void gotIP(IPAddress address, IPAddress, IPAddress)
{
    debugf("I'm CONNECTED");
    Serial.println(address.toString());
    Serial.println("I'm CONNECTED");
    f_Server.listen(80);
    f_Server.setTimeOut(0xFFFF);
}

// Will be called when WiFi station timeout was reached
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void connectFail(String, uint8_t, uint8_t[6], uint8_t)
{
	debugf("I'm NOT CONNECTED!");
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void init() {
    noInterrupts();

	f_Timer.setCallback(PirOutputChangeTimerCallback);
    f_Timer.setIntervalMs(LIGHT_TIMEOUT_MS);

    // Initialize wifi connection
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.systemDebugOutput(true); // Allow debug print to serial
    Serial.println("Sming. Let's do smart things!");


    setupGPIO();
    setupWifi() ;

    // Set system ready callback method
    System.onReady(ready);
}


////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ready(void)
{
    f_LightsOn = 1U;

    ConfigurationData confData;

    SpiFlashOpResult flashResult = spi_flash_read(CONFIGURATION_DATA_ADDRESS,
                    (uint32_t*) &confData, CONFIGURATION_DATA_SIZE);
    if ((flashResult == SPI_FLASH_RESULT_OK)
                    && (confData.m_Identification == IDENTIFICATION_ID))
    {
       debugf("Read flash ok\r\n");
       f_DataParser.SetConfData(confData);
    }
    else if ((flashResult == SPI_FLASH_RESULT_OK) && (confData.m_Identification != IDENTIFICATION_ID))
    {
        debugf("First time read flash, id on flash: %i\r\n",
                        confData.m_Identification);
        writeDefaultConfig(f_DataParser);
        flashResult = spi_flash_write(CONFIGURATION_DATA_ADDRESS,
                        (uint32_t*) &f_DataParser.GetConfData(),
                        CONFIGURATION_DATA_SIZE);
        if (flashResult != SPI_FLASH_RESULT_OK)
        {
            debugf("spi_flash_write failed, %i\r\n", flashResult);
            assert(false);
        }
        else
        {
            debugf("Write on flash, configuration : %i\r\n",
                            f_DataParser.GetConfData().m_Configuration);
        }
    }
    else
    {
        debugf("Error occured, flashResult: %i(ok = %i), identification: %i\r\n",
                        flashResult, SPI_FLASH_RESULT_OK,
                        confData.m_Identification);
        assert(false);
    }
    interrupts();
}



static void setupGPIO(void)
{
    attachInterrupt(PIN_PIR_OUTPUT, InterruptPIRChange, GPIO_PIN_INTR_ANYEDGE);
    attachInterrupt(PIN_LIGHT_INTERRUPT, InterruptLightChange, GPIO_PIN_INTR_POSEDGE);

    // on init all lights on.
    for (uint8_t i = 0; i < LIGHTS_USED; ++i)
    {
        pinMode(PINS_LIGHT_SWITCH[i], OUTPUT);
        digitalWrite(PINS_LIGHT_SWITCH[i], (f_DataParser.GetLight(i) != 0));
    }

    // on init PIR enabled.
    pinMode(PIN_PIR_ENABLE, OUTPUT);
    digitalWrite(PIN_PIR_ENABLE, f_DataParser.GetPIREnable());
    pinMode(PIN_PIR_OUTPUT, INPUT);
    pinMode(PIN_LIGHT_INTERRUPT, INPUT);
//    pinMode(PIN_WIFI_ENABLE, INPUT | FUNCTION_3);
}


static void setupWifi(void)
{
    debugf("Start Wifi\r\n");
    WifiStation.config(WIFI_SSID, WIFI_PWD); // Put you SSID and Password here

	// Optional: Change IP addresses (and disable DHCP)

	WifiStation.setIP(IPAddress(String(IP_ADDRESS)));
	WifiEvents.onStationGotIP(gotIP);
	WifiEvents.onStationDisconnect(connectFail);
    WifiStation.enable(true);

}
