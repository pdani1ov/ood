#include "../../../catch/catch.hpp"
#include "../streams/Compress.h"
#include "../streams/Decompress.h"
#include "../streams/MemoryOutputStream.h"
#include "../streams/MemoryInputStream.h"
#include "../streams/InputDataStream.h"
#include "../streams/Cryptographer.h"
#include "../streams/Encrypt.h"
#include "../streams//Decrypt.h"
#include <vector>

TEST_CASE("Check compress")
{
	std::string in = "mmmeee";
	std::string outStr = "";
	std::string result = std::to_string(uint8_t(3)) + std::to_string(uint8_t('m')) + 
		std::to_string(uint8_t(3)) + std::to_string(uint8_t('e'));
	std::vector<uint8_t> out;

	CCompress compresser(std::make_unique<CMemoryOutputStream>(out));
	compresser.WriteBlock(&in[0], 6);
	compresser.Close();

	for (size_t i = 0; i < out.size(); i++)
	{
		outStr += std::to_string(out[i]);
	}

	REQUIRE(result == outStr);
}

TEST_CASE("Check decompress")
{
	char buf[6];
	std::string outStr = "";
	std::string result = "mmmeee";
	std::vector<uint8_t> in(4);
	in[0] = uint8_t(3);
	in[1] = uint8_t('m');
	in[2] = uint8_t(3);
	in[3] = uint8_t('e');

	CDecompress decompresser(std::make_unique<CMemoryInputStream>(in));

	while (!decompresser.IsEOF())
	{
		decompresser.ReadBlock(&buf, 6);

		for (int i = 0; i < 3; i++)
		{
			outStr += buf[i];
		}
	}

	REQUIRE(result == outStr);
}

TEST_CASE("Check crypt and decrypt")
{
	std::vector<uint8_t> data;

	CCryptographer crypt(3);
	CEncrypt encrypter(std::make_unique<CMemoryOutputStream>(data), 3);

	encrypter.WriteByte('b');
	encrypter.WriteByte('y');
	encrypter.WriteByte('e');

	REQUIRE(data[0] == crypt.Encrypt('b'));
	REQUIRE(data[1] == crypt.Encrypt('y'));
	REQUIRE(data[2] == crypt.Encrypt('e'));

	CDecrypt decrypter(std::make_unique<CMemoryInputStream>(data), 3);
	REQUIRE(decrypter.ReadByte() == 'b');
	REQUIRE(decrypter.ReadByte() == 'y');
	REQUIRE(decrypter.ReadByte() == 'e');
}