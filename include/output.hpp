#ifndef OUTPUT_H
#define OUTPUT_H


#include <fstream>
#include <string>

void output_unix(std::string transpiled_code, std::string destination);

void output_windows(std::string transpiled_code, std::string destination);

void output_code(std::string transpiled_code, std::string destination);

#endif // OUTPUT_H
