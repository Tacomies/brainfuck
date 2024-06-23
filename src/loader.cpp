#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const char INSTRUCTION_SET[] = "-+<>[],.";

bool is_instruction(char character)
{
	// Yes, I did hardcode the instuction count, too bad ain't it
	for (int idx = 0; idx < 8; idx++)
	{
		if (character == INSTRUCTION_SET[idx])
		{
			return true;
		}
	}

	return false;
}

std::vector<char> load_source_program(std::string path)
{
	std::ifstream source_file(path);
	std::vector<char> program;

	if (!source_file.is_open())
	{
		std::cerr << "Source file couldn't be opened" << std::endl;
		return program; 
	}
	
	char character;
	while (source_file.get(character))
	{
		if (is_instruction(character))
		{
			program.push_back(character);
		}
	}

	source_file.close();
	return program;
}

