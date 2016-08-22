#include "common_test.h"


void if_key_print(Input* input, std::string key_name)
{
	if(input->get_key(key_name))
		std::cout << key_name << std::endl;
}
