#ifndef DATAPARSER
#define DATAPARSER
#ifndef QT_CORE_LIB
#include "user_config.h"
#endif


typedef struct
{
    uint16_t m_Data;
    uint32_t m_Configuration;
} ConfigurationData;

class DataParser{

public:

    static const uint8_t NUM_LIGHT = 5U;
	static const uint16_t LIGHT_SET_MASK = 0x20;

	static const uint16_t LIGHT_MASK = 0x1F;
	static const uint16_t LIGHT_ON_MASK = 0x40;

	static const uint16_t PIR_MASK = 0x100;

	static const uint16_t DATA_SIZE = sizeof(PIR_MASK);

    static const uint32_t DEFAULT_CONFIGURATION = 0b1111101010010110;

    static const uint8_t  NUM_CONFIGURATIONS = 4U;


	DataParser() :
	    m_ConfData()
	{
	}
	DataParser(const ConfigurationData& rConfData)
	{
		m_ConfData  = rConfData;
	}

	inline void SetData(const uint16_t data)
	{
	    m_ConfData.m_Data = data;
	}

    inline const uint16_t GetData(void) const
	{
	    return m_ConfData.m_Data;
	}

    inline const ConfigurationData& GetConfData(void) const
    {
        return m_ConfData;
    }

    inline void SetConfData(ConfigurationData& rConfData)
    {
        m_ConfData = rConfData;
    }


	/// @param[in]	id	Id of light [0-3]
	///
	/// @retval zero in case of light turn off for id light.
	inline uint16_t GetLight(const uint16_t id) const
	{
		return (m_ConfData.m_Data & DataParser::LIGHT_MASK) & (1 << id);
	}

	/// Set lights.
	inline void SetLight(const uint16_t id, const uint16_t lightOn)
	{
		if (id >= NUM_LIGHT) {
			return;
		}
		if (lightOn != 0) {
			m_ConfData.m_Data = (1 << id) | m_ConfData.m_Data;
		} else {
			m_ConfData.m_Data = (~(1 << id)) & m_ConfData.m_Data;
		}
	}


	/// @return light flag
	/// @retval 0 : No setting of output pins, only fill data to this struct.
	/// @retval not 0 : Set output pins and let this struct as is.
	inline uint16_t GetLightFlag(void) const
	{
		return m_ConfData.m_Data & LIGHT_SET_MASK;
	}

	inline void SetLightFlag(const uint16_t lightFlag)
	{
	    if (lightFlag != 0)
        {
            m_ConfData.m_Data = m_ConfData.m_Data | LIGHT_SET_MASK;
        }
	    else{
	        m_ConfData.m_Data = m_ConfData.m_Data & (~LIGHT_SET_MASK);
	    }
	}

	inline uint16_t GetLightOn(void) const
	{
		return m_ConfData.m_Data & LIGHT_ON_MASK;
	}

	inline void SetLightOn( const uint16_t lightOn)
	{
		if (lightOn != 0)
		{
			m_ConfData.m_Data = m_ConfData.m_Data | LIGHT_ON_MASK;
		}else{
			m_ConfData.m_Data = m_ConfData.m_Data & (~LIGHT_ON_MASK);
		}
	}


	inline uint16_t GetPIREnable(void) const
	{
		return m_ConfData.m_Data & PIR_MASK;
	}

	inline void SetPIREnable(const uint16_t pirOn)
	{
		if (pirOn != 0)
		{
			m_ConfData.m_Data = m_ConfData.m_Data | PIR_MASK;
		}else{
			m_ConfData.m_Data = m_ConfData.m_Data & (~PIR_MASK);
		}
	}

    inline void SetConfiguration(const uint32_t& rConfiguration)
	{
	    m_ConfData.m_Configuration = rConfiguration;
	}

    inline uint32_t GetConfiguration(void) const
	{
	    return m_ConfData.m_Configuration;
	}

	inline void SetConfigurationLight(const uint8_t confNumber)
    {
        if (confNumber >= NUM_CONFIGURATIONS)
        {
            return;
        }
        for (uint8_t i = 0; i < NUM_LIGHT; ++i)
        {
            SetLight(i, m_ConfData.m_Configuration & ((1 <<  NUM_CONFIGURATIONS * confNumber) << i));
        }
    }

private:
	ConfigurationData m_ConfData;
};

#endif // DATAPARSER
