#ifndef TRANSPILER_H
#define TRANSPILER_H

#include <vector>
#include <string>


const char LOOP_START = '[';
const char LOOP_END = ']';
const char POINTER_INCREMENT = '>';
const char POINTER_DECREMENT = '<';
const char BYTE_INCREMENT = '+';
const char BYTE_DECREMENT = '-';
const char OUTPUT_BYTE = '.';
const char INPUT_BYTE = ',';


int match_loop(std::vector<char> source_code, int pointer);

std::string build_stacking_instruction(std::vector<char> source_code, int *pointer, int end);

std::string recursive_transpile(std::vector<char> source_code, int pointer, int end);

std::string transpile(std::vector<char> source_code, int length);

#endif // TRANSPILER_H

