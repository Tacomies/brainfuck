#include <fstream>
#include <string>
#include <iostream>

void output_unix(std::string transpiled_code, std::string destination)
{
    std::string gcc_command;
	
	gcc_command += "echo '";
	gcc_command += transpiled_code;
	gcc_command += "'";
	gcc_command += " | gcc -xc -o ";
	gcc_command += destination + " - ";
	
	std::system(gcc_command.c_str());
}

void output_windows(std::string transpiled_code, std::string destination)
{
    std::ofstream temp_file("temporary.c");
    if (!temp_file) 
    {
        std::cerr << "Could not open the temp file for writing." << std::endl;
        return; // No error codes
    }

    temp_file << transpiled_code;
    temp_file.close();

    std::string gcc_command = "g++ -o " + destination;
    gcc_command += " temporary.c";

    std::system(gcc_command.c_str());
    std::remove("temporary.c");
}

void output_code(std::string transpiled_code, std::string destination)
{
    #ifdef _WIN32
        output_windows(transpiled_code, destination);
        return;
    #endif // _WIN32

    output_unix(transpiled_code, destination);
}