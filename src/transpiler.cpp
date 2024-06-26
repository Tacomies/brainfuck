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
	int repeat_tracker = 0;
	std::string repeats;
	char instruction_type = source_code.at(*pointer);
	
	while (*pointer < end && source_code.at(*pointer) == instruction_type)
	{
		repeat_tracker++;
		(*pointer)++;
	}

	repeats = std::to_string(repeat_tracker);

	switch(instruction_type)
	{
		case POINTER_INCREMENT:
			instruction += "pointer_increment(" + repeats + ");\n";
			break;
		case POINTER_DECREMENT:
			instruction += "pointer_decrement(" + repeats + ");\n";
			break;
		case BYTE_INCREMENT:
			instruction += "data_array[data_pointer] += " + repeats + ";\n";
			break;
		case BYTE_DECREMENT:
			instruction += "data_array[data_pointer] -= " + repeats + ";\n";
			break;
	}


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
			transpiled_code += "input_byte();\n";
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

void add_boilerplate(std::string* code)
{
	// This code can be found in extra/boilerplate.c
	// I decided to use the code this way so that setting
	// env variables to locate the file during transpiling
	// wouldn't be necessary for the user
	*code += "#include <stdio.h>\n#include <stdint.h>\nuint8_t data_array[30000];uint16_t data_pointer = 0;void pointer_increment(int addition){if (data_pointer + addition > 29999){data_pointer = data_pointer - 29999 + addition - 1;return;}data_pointer += addition;}void pointer_decrement(int subtraction){if (data_pointer - subtraction < 0){data_pointer = 29999 + data_pointer + 1 - subtraction;return;}data_pointer -= subtraction;}void input_byte(){unsigned int temp;char scan_type[2] = \"\";scan_type[0] = '%';scan_type[1] = 'u';scanf(scan_type, &temp);if (temp <= 255){data_array[data_pointer] = (uint8_t)temp;return;}data_array[data_pointer] = (uint8_t)(temp % 255 - 1);}";

}

void make_main_function(std::string* code, std::string* transpiled_code)
{
	*code += "int main()\n{\n";
	*code += "for (int idx = 0; idx < 30000; idx++) {data_array[idx] = 0;}\n";
	*code += *transpiled_code;
	*code += "}";
}

std::string make_c_file(std::string transpiled_code)
{
	std::string final_code;
	add_boilerplate(&final_code);
	make_main_function(&final_code, &transpiled_code);

	return final_code;
}

std::string transpile(std::vector<char> source_code, int length)
{
	int starting_index = 0;
	std::string transpiled_code = recursive_transpile(source_code, starting_index, length);
	
	return make_c_file(transpiled_code);
}

