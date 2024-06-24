#include <fstream>
#include <string>
#include <iostream>


int output_code(std::string transpiled_code, std::string destination)
{
	std::string temp_file_name = "temp_file_for_bfc_mid_compile.c";
	std::ofstream temp_file(temp_file_name);

	if (!temp_file) 
	{
		std::cerr << "Could not open the temp file for writing." << std::endl;
		return 1;
	}

	temp_file << transpiled_code;
	temp_file.close();

	std::string gcc_command = "g++ -o " + destination + " ";
	gcc_command += temp_file_name;

	std::system(gcc_command.c_str());
	std::remove(temp_file_name.c_str());

	return 0;
}
