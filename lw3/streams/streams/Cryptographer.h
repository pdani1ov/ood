#pragma once
#include <vector>
#include <algorithm>
#include <random>

class CCryptographer
{
public:
	CCryptographer(int key)
		:m_decryptTable(256),
		m_encryptTable(256)
	{

		for (unsigned i = 0; i <= 255; i++)
		{
			m_encryptTable[i] = i;
		}
		
		std::shuffle(m_encryptTable.begin(), m_encryptTable.end(), std::mt19937(key));

		for (unsigned i = 0; i <= 255; i++)
		{
			m_decryptTable[m_encryptTable[i]] = i;
		}
	}

	uint8_t Encrypt(uint8_t value)
	{
		return m_encryptTable[value];
	}

	uint8_t Decrypt(uint8_t value)
	{
		return m_decryptTable[value];
	}

private:
	std::vector<uint8_t> m_encryptTable;
	std::vector<uint8_t> m_decryptTable;
};