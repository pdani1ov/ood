#include <cstdint>
#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "Compress.h"
#include "Decrypt.h"
#include "Decompress.h"
#include "Encrypt.h"

struct Command
{
	std::string name = "";
	int arg = 0;
};

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::vector<Command> commands;
};

bool HasArg(std::string name)
{
	return name == "--encrypt" || name == "--descrypt";
}

std::optional<std::vector<Command>> ParseCommands(int argc, char* argv[])
{
	std::vector<Command> commands;

	int i = 1;
	while (i < argc - 2)
	{
		Command command;
		command.name = argv[i];

		if (!HasArg(command.name))
		{
			commands.push_back(command);
			i++;
			continue;
		}

		if (i + 1 < argc - 2)
		{
			command.arg = std::atoi(argv[i + 1]);
			commands.push_back(command);
			i += 2;
		}
		else
		{
			return std::nullopt;
		}
	}

	return commands;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid quantity of arguments" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.inputFileName = argv[argc - 2];
	args.outputFileName = argv[argc - 1];

	std::optional<std::vector<Command>> parsedCommands = ParseCommands(argc, argv);

	if (!parsedCommands.has_value())
	{
		return std::nullopt;
	}

	args.commands = *parsedCommands;

	return args;
}

IInputDataStreamPtr DecorateDecrypt(IInputDataStreamPtr&& stream, int const key)
{
	CDecrypt* decryptor = new CDecrypt(move(stream), key);
	return move(std::unique_ptr<CDecrypt>(decryptor));
}

IInputDataStreamPtr DecorateDecompress(IInputDataStreamPtr&& stream)
{
	CDecompress* decompressor = new CDecompress(move(stream));
	return move(std::unique_ptr<CDecompress>(decompressor));
}

IOutputDataStreamPtr DecorateCompress(IOutputDataStreamPtr&& stream)
{
	CCompress* compressor = new CCompress(move(stream));
	return move(std::unique_ptr<CCompress>(compressor));
}

IOutputDataStreamPtr DecorateEncrypt(IOutputDataStreamPtr&& stream, int const key)
{
	CEncrypt* encryptor = new CEncrypt(move(stream), key);
	return move(std::unique_ptr<CEncrypt>(encryptor));
}

void SetCommands(IInputDataStreamPtr& input, IOutputDataStreamPtr& output, std::vector<Command> const& commands)
{
	for (auto command : commands)
	{
		if (command.name == "--compress")
		{
			output = DecorateCompress(move(output));
		} 
		else if (command.name == "--encrypt")
		{
			output = DecorateEncrypt(move(output), command.arg);
		}
		else if (command.name == "--decompress")
		{
			input = DecorateDecompress(move(input));
		}
		else if (command.name == "--decrypt")
		{
			input = DecorateDecrypt(move(input), command.arg);
		}
	}
}

int main(int argc, char* argv[])
{
	std::optional<Args> args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	IInputDataStreamPtr inputFileStream(new CFileInputStream(args->inputFileName));
	IOutputDataStreamPtr outputFileStream(new CFileOutputStream(args->outputFileName));

	SetCommands(inputFileStream, outputFileStream, args->commands);

	char buf[10];
	std::streamsize size;

	while (!inputFileStream->IsEOF())
	{
		size = inputFileStream->ReadBlock(&buf, 10);

		if (size != 0)
		{
			outputFileStream->WriteBlock(&buf, size);
		}
	}

	return 0;
}
