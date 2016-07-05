#include "../string_split.hpp"
#include <iostream>
int main() 
{
	std::string s = "arikitari na world!";
	const auto s_1 = s | split(' ')[1];
	if ("na" != s_1) return 1;
	std::string s2 = "123,421,113";
	const auto s_2 = s2 | split(',') >> [](const std::string& s) {
		return std::stoi(s);
	};
	s2 | split(',') >> [](const std::string& s) {
		std::cout << s << std::endl;
	};
	return 0;
}