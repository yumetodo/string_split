#include "../include/string_split.hpp"
#include <iostream>
int to_int(const std::string& s) { return std::stoi(s); }
int main()
{
	std::string s = "arikitari na world!";
	const auto s_1 = s | split(' ')[1];
	if ("na" != s_1) return 1;
	std::string s2 = "123,421,113";
	const auto n1 = s2 | split(',') >> [](const std::string& s) {
		return std::stoi(s);
	};//lamda or class contain operator()
	//const auto n2 = s2 | split(',') >> std::stoi;//std::stoi's prototype is int(const std::string&, std::size_t*, int), not int(const std::string&).
	const auto n2 = s2 | split(',') >> to_int;//function-pointer
	if (n1 != n2) return 2;
	s2 | split(',') >> [](std::string&& s) {
		std::cout << s << std::endl;
	};
	return 0;
}