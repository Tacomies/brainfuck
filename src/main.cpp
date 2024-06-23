#include <iostream>
#include <vector>
#include <string>
#include "../include/loader.hpp"
#include "../include/transpiler.hpp"


void help()
{
	std::cout << "BFC v1.0.0\nUsage: \"bfc <path to source file> <path to destination>\"\n";
}

int main(int argc, char** argv)
{
	std::string source_path;
	
	std::cout << argc;

	if (argc == 0)
	{
		help();
		return 0;
	}

	if (argc != 3)
	{
		std::cerr << "Too many or missing arguments\nFor more information:\n -h or no arguments" << std::endl;
		return 1;
	}

	source_path = argv[1];
	std::string destination = argv[2];

	std::vector<char> source_program = load_source_program(source_path);
	std::string transpiled_code = transpile(source_program, source_program.size());

	if (transpiled_code.length() <= 0)
	{
		std::cerr << "Source file empty or was failed to read" << std::endl;
		return 1;
	}

	std::string gcc_command;
	
	gcc_command += "echo '";
	gcc_command += transpiled_code;
	gcc_command += "'";
	gcc_command += "| gcc -xc -o ";
	gcc_command += destination + " - ";
	
	std::system(gcc_command.c_str());

	return 0;
}

