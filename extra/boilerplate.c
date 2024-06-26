// THIS FILE CAN BE FOUND AS A STRING IN TRANSPILER.CPP / void add_boilerplate()
// It's just way easier to make changes like this, you do not need this file to compile

#include <stdio.h>
#include <stdint.h>


uint8_t data_array[30000];
uint16_t data_pointer = 0;

void pointer_increment(int addition)
{	
	if (data_pointer + addition > 29999)
	{
		data_pointer = data_pointer - 29999 + addition - 1;
		return;
	}

	data_pointer += addition;

}

void pointer_decrement(int subtraction)
{
	if (data_pointer - subtraction < 0)
	{
		data_pointer = 29999 + data_pointer + 1 - subtraction;
		return;
	}

	data_pointer -= subtraction;
}

void input_byte()
{
	unsigned int temp;
	char scan_type[2] = "";
	scan_type[0] = '%';
	scan_type[1] = 'u';
	scanf(scan_type, &temp);
	
	if (temp <= 255)
	{
		data_array[data_pointer] = (uint8_t)temp;
		return;
	}

	data_array[data_pointer] = (uint8_t)(temp % 255 - 1);
}


