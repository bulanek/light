#include <user_config.h>
#include <SmingCore/SmingCore.h>

#include "../include/DataParser.hpp"
#include "../include/Definitions.h"

// If you want, you can define WiFi settings globally in Eclipse Environment Variables

// CONSTANTS

const uint8_t PINS_LIGHT_SWITCH[] = { 13, 12, 14, 16};
/// Number of used lights
const uint8_t LIGHTS_USED = 3;

const uint8_t PIN_LIGHT_INTERRUPT = 4;

const uint8_t PIN_PIR_ENABLE = 2;
const uint8_t PIN_PIR_OUTPUT = 5;

const uint16_t LIGHT_TIMEOUT_MS = 10000U;

String CONFIG_NAME = "light.conf";

void tcpServerClientConnected(TcpClient* client);
bool tcpServerClientReceive(TcpClient& client, char *data, int size);
void tcpServerClientComplete(TcpClient& client, bool succesfull);

/// Set or get lights
static void setLights(DataParser& rDataParser);
static void setPIR(DataParser& rDataParser);

static void writeDefaultConfig(const String& rConfigFile);
static void writeConfig(const String& rConfigFile);
static void readConfig(const String& rConfigFile, DataParser& rDataParser);

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
    for (uint8_t i = 0; i < LIGHTS_USED; ++i) {
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

	if ((f_LightsOn == 0U) && (pirValue == 1U) ) {
		f_LightsOn = 1U;
		f_DataParser.SetLightOn(1U);
		for (uint8_t i = 0U; i < LIGHTS_USED; ++i) {
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
    if (f_LightsOn != 0U)
    {
        f_LightsOn = 0U;
        for (uint8_t i = 0; i < LIGHTS_USED; ++i) {
            digitalWrite(PINS_LIGHT_SWITCH[i], 0U);
        }
    }
    else {
		f_LightsOn = 1U;
		for (uint8_t i = 0; i < LIGHTS_USED; ++i) {
			digitalWrite(PINS_LIGHT_SWITCH[i], (f_DataParser.GetLight(i)!=0));
		}
	}
    f_DataParser.SetLightOn(f_LightsOn);
    interrupts();
}
////////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME: tcpServerClientConnected
////////////////////////////////////////////////////////////////////////////////
void tcpServerClientConnected(TcpClient* client) {
	debugf("Application onClientCallback : %s\r\n",
			client->getRemoteIp().toString().c_str());
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME: tcpServerClientReceive
////////////////////////////////////////////////////////////////////////////////
bool tcpServerClientReceive(TcpClient& client, char *data, int size)
{
    debugf("Application DataCallback : %s, %d bytes \r\n",
            client.getRemoteIp().toString().c_str(), size);
    // One byte information
    if (size == DataParser::DATA_SIZE)
    {
        f_DataParser.SetData(*(uint16_t*) data);

        // Lights with lightsOn
        setLights(f_DataParser);
        // PIR enable
        setPIR(f_DataParser);

        if(f_DataParser.GetLightFlag() != 0)
        {
            writeConfig(CONFIG_NAME);
        }

        uint16_t data = htons(f_DataParser.GetData());

        if (!client.send((const char*) &data, DataParser::DATA_SIZE))
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

void writeDefaultConfig(const String& rConfigFile)
{
    for (uint8_t i = 0; i < DataParser::NUM_LIGHT; ++i)
    {
        f_DataParser.SetLight(i, 1);
    }
    f_DataParser.SetLightOn(1U);
    f_DataParser.SetPIREnable(1U);
    file_t fileDsc = fileOpen(rConfigFile,
            eFO_ReadWrite | eFO_CreateIfNotExist);
    uint16 data = f_DataParser.GetData();
    fileWrite(fileDsc, (void*) &data, DataParser::DATA_SIZE);
    fileClose(fileDsc);

}

void writeConfig(const String& rConfigFile)
{
    file_t fileDsc = fileOpen(rConfigFile,
            eFO_ReadWrite | eFO_CreateIfNotExist);

    uint16_t data = f_DataParser.GetData();
    fileWrite(fileDsc, (void*) &data, DataParser::DATA_SIZE);
    fileClose(fileDsc);
}

void readConfig(const String& rConfigFile, DataParser& rDataParser)
{
    file_t fileDsc = fileOpen(rConfigFile,
            eFO_ReadWrite | eFO_CreateIfNotExist);
    uint16_t data = 0;
        fileRead(fileDsc, (void*) &data, DataParser::DATA_SIZE);
        rDataParser.SetData(data);
    fileClose(fileDsc);
}

////////////////////////////////////////////////////////////////////////////////
// FUNCTION NAME: tcpServerClientComplete
////////////////////////////////////////////////////////////////////////////////
void tcpServerClientComplete(TcpClient& client, bool succesfull) {
	debugf("Application CompleteCallback : %s \r\n",
			client.getRemoteIp().toString().c_str());
}


// Will be called when WiFi station was connected to AP
void connectOk() {
	debugf("I'm CONNECTED");
	Serial.println(WifiStation.getIP().toString());
	Serial.println("I'm CONNECTED");
	f_Server.listen(80);
	f_Server.setTimeOut(0xFFFF);
}


// Will be called when WiFi station timeout was reached
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void connectFail() {
	debugf("I'm NOT CONNECTED!");
	WifiStation.waitConnection(connectOk, 10, connectFail); // Repeat and check again
}

// Will be called when WiFi hardware and software initialization was finished
// And system initialization was completed
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ready()
{
    debugf("READY!");

    attachInterrupt(PIN_PIR_OUTPUT, InterruptPIRChange, GPIO_PIN_INTR_ANYEDGE);
    attachInterrupt(PIN_LIGHT_INTERRUPT, InterruptLightChange,
            GPIO_PIN_INTR_POSEDGE);

    file_t fileDsc;
    f_LightsOn = 1U;
    if (fileExist(CONFIG_NAME) == false)
    {
        writeDefaultConfig(CONFIG_NAME);
    }
    else
    {
        readConfig(CONFIG_NAME, f_DataParser);
    }

    // on init all lights on.
    f_LightsOn = 1;
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

    interrupts();
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void init() {
	f_Timer.setCallback(PirOutputChangeTimerCallback);
	f_Timer.setIntervalMs(LIGHT_TIMEOUT_MS);
	noInterrupts();

	// Initialize wifi connection
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.systemDebugOutput(true); // Allow debug print to serial
	Serial.println("Sming. Let's do smart things!");

	// Set system ready callback method
	System.onReady(ready);

	// Station - WiFi client
	WifiStation.enable(true);
	WifiStation.config(WIFI_SSID, WIFI_PWD); // Put you SSID and Password here

	// Optional: Change IP addresses (and disable DHCP)

	WifiStation.setIP(IPAddress(String(IP_ADDRESS)));

	// Run our method when station was connected to AP (or not connected)
	// We recommend 20+ seconds at start
	WifiStation.waitConnection(connectOk, 30, connectFail);
}
