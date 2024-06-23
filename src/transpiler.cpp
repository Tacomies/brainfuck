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

int match_loop(std::vector<char> source_code, int pointer)
{
	int brackets = 1;
	
	while (brackets != 0)
	{
		pointer++;

		if (source_code.at(pointer) == LOOP_START)
		{
			brackets++;
		}
		else if (source_code.at(pointer) == LOOP_END)
		{
			brackets--;
		}
	}
	
	return pointer;
}

std::string build_stacking_instruction(std::vector<char> source_code, int *pointer, int end)
{
	std::string instruction;
	int repeats = 0;
	char instruction_type = source_code.at(*pointer);
	
	while (*pointer < end && source_code.at(*pointer) == instruction_type)
	{
		repeats++;
		(*pointer)++;
	}
	
	switch(instruction_type)
	{
		case POINTER_INCREMENT:
			instruction += "data_pointer += ";
			break;
		case POINTER_DECREMENT:
			instruction += "data_pointer -= ";
			break;
		case BYTE_INCREMENT:
			instruction += "data_array[data_pointer] += ";
			break;
		case BYTE_DECREMENT:
			instruction += "data_array[data_pointer] -= ";
			break;
	}

	instruction += std::to_string(repeats) + ";\n";

	return instruction;
}

std::string recursive_transpile(std::vector<char> source_code, int pointer, int end)
{
	std::string transpiled_code;

	while (pointer < end)
	{
		if (source_code.at(pointer) == LOOP_START)
		{
			int loop_end_index = match_loop(source_code, pointer);

			transpiled_code += "while (data_array[data_pointer] != 0)\n{\n";
			transpiled_code += recursive_transpile(source_code, pointer + 1, loop_end_index);
			transpiled_code += "if (data_array[data_pointer] == 0) {break;}}\n";

			pointer = loop_end_index + 1;
			continue;
		}
		
		if (source_code.at(pointer) == INPUT_BYTE)
		{
			transpiled_code += "scanf(\"%\" SCNd8, &data_array[data_pointer]);\n";
			pointer++;
			continue;
		}
	
		if (source_code.at(pointer) == OUTPUT_BYTE)
		{
			transpiled_code += "printf(\"%c\", data_array[data_pointer]);\n";
			pointer++;
			continue;
		}

		transpiled_code += build_stacking_instruction(source_code, &pointer, end);
	}
	
	return transpiled_code;
}

std::string include_boilerplate(std::string transpiled_code)
{
	std::string final_code;

	final_code += "#include <stdio.h>\n#include <stdint.h>\n";
	final_code += "uint8_t data_array[30000];\nuint8_t data_pointer = 0;\n";
	final_code += "int main()\n{\n";
	final_code += "for (int idx = 0; idx < 30000; idx++) {data_array[idx] = 0;}\n";
	final_code += transpiled_code;
	final_code += "}";

	return final_code;
}

std::string transpile(std::vector<char> source_code, int length)
{
	int starting_index = 0;
	std::string transpiled_code = recursive_transpile(source_code, starting_index, length);
	
	return include_boilerplate(transpiled_code);
}

