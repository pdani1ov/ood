#include <iostream>
#include <filesystem>

#include "PictureController.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Invalid arguments format" << std::endl;
		return 1;
	}

	std::string outputFileName;
	outputFileName = argv[1];

	if (std::filesystem::path(outputFileName).extension().string() != ".svg")
	{
		std::cout << "Invalid format of file" << std::endl;
		return 1;
	}

	CPictureController controller(outputFileName);
	controller.Run();
	return 0;
}
