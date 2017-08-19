#ifndef DATAPARSER
#define DATAPARSER
#ifndef QT_CORE_LIB
#include "user_config.h"
#endif


class DataParser{

public:

	static const uint8_t NUM_LIGHT = 3U;
	static const uint16_t LIGHT_SET_MASK = 0x20;

	static const uint16_t LIGHT_MASK = 0x1F;
	static const uint16_t LIGHT_ON_MASK = 0x40;

	static const uint16_t PIR_MASK = 0x100;

	static const uint16_t DATA_SIZE = sizeof(PIR_MASK);

	static const uint16_t DEFAULT_CONFIGURATION = 0b1111101010010110;


	DataParser() :
		m_Data(0)
	{
	}
	DataParser(const uint16_t data)
	{
		m_Data = data;
	}

	inline void SetData(const uint16_t data)
	{
	    m_Data = data;
	}

    inline const uint16_t GetData(void) const
	{
	    return m_Data;
	}


	/// @param[in]	id	Id of light [0-3]
	///
	/// @retval zero in case of light turn off for id light.
	inline uint16_t GetLight(const uint16_t id) const
	{
		return (m_Data & DataParser::LIGHT_MASK) & (1 << id);
	}

	/// Set lights.
	inline void SetLight(const uint16_t id, const uint16_t lightOn)
	{
		if (id >= NUM_LIGHT) {
			return;
		}
		if (lightOn != 0) {
			m_Data = (1 << id) | m_Data;
		} else {
			m_Data = (~(1 << id)) & m_Data;
		}
	}


	/// @return light flag
	/// @retval 0 : No setting of output pins, only fill data to this struct.
	/// @retval not 0 : Set output pins and let this struct as is.
	inline uint16_t GetLightFlag(void) const
	{
		return m_Data & LIGHT_SET_MASK;
	}

	inline void SetLightFlag(const uint16_t lightFlag)
	{
	    if (lightFlag != 0)
        {
            m_Data = m_Data | LIGHT_SET_MASK;
        }
	    else{
	        m_Data = m_Data & (~LIGHT_SET_MASK);
	    }
	}

	inline uint16_t GetLightOn(void) const
	{
		return m_Data & LIGHT_ON_MASK;
	}

	inline void SetLightOn( const uint16_t lightOn)
	{
		if (lightOn != 0)
		{
			m_Data = m_Data | LIGHT_ON_MASK;
		}else{
			m_Data = m_Data & (~LIGHT_ON_MASK);
		}
	}


	inline uint16_t GetPIREnable(void) const
	{
		return m_Data & PIR_MASK;
	}

	inline void SetPIREnable(const uint16_t pirOn)
	{
		if (pirOn != 0)
		{
			m_Data = m_Data | PIR_MASK;
		}else{
			m_Data = m_Data & (~PIR_MASK);
		}
	}

	inline void SetConfigurationLight(const uint8_t confNumber)
    {
        if (confNumber >= 4U)
        {
            return;
        }
        for (uint8_t i = 0; i < 4; ++i)
        {
            SetLight(i, m_Configuration & ((1 << 4 * confNumber) << i));
        }
    }

private:
	uint16_t m_Data;
	/// 4x4 bit light configuration
	uint16_t m_Configuration;

};

#endif // DATAPARSER
