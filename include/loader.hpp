#ifndef LOADER_H
#define LOADER_H


#include <vector>
#include <string>

const char INSTRUCTION_SET[] = "-+<>[],.";

bool is_instruction(char character);

std::vector<char> load_source_program(std::string path);


#endif // LOADER_H
