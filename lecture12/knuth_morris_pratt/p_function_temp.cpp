#include "p_function_temp.h"



void p_function_temp(const std::string& s, std::vector < int >& p_out) {
	p_out.resize(s.length());

	p_out[0] = 0;
	for (std::size_t i = 1; i < s.length(); ++i) {
		std::size_t p_index = p_out[i - 1];
		while (true) {
			if (s[i] == s[p_index]) {
				p_out[i] = p_index + 1;
				break;
			}
			if (!p_index) {
				p_out[i] = 0;
				break;
			}
			p_index = p_out[p_index - 1];
		}
	}
}

void p_function_temp_adapted(const char* s, int* p_out, int length)
{
	std::string string(s, length);
	std::vector < int > p_vector;
	
	p_function_temp(string, p_vector);

	for (std::size_t i = 0; i < p_vector.size(); ++i) {
		p_out[i] = p_vector[i];
	}
}
