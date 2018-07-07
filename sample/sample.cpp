/*=============================================================================
  Copyright (C) 2016 yumetodo

  Distributed under the Boost Software License, Version 1.0.
  (See http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "../include/string_split.hpp"
#include <iostream>
int to_int(const std::string& s) { return std::stoi(s); }
int main()
{
	std::string s = "arikitari na world!";
	const auto s_1 = s | split(' ')[1];
	if ("na" != s_1) return 1;
	std::string s2 = "123,421,113";

	//lamda or class contain operator()
	const auto n1 = s2 | split(',') >> [](const std::string& s) {
		return std::stoi(s);
	};

	//std::stoi's prototype is int(const std::string&, std::size_t*, int), not int(const std::string&).
	//const auto n2 = s2 | split(',') >> std::stoi;

	//function-pointer
	const auto n2 = s2 | split(',') >> to_int;
	if (n1 != n2) return 2;
	s2 | split(',') >> [](std::string&& s) {
		std::cout << s << std::endl;
	};

#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	std::string_view sw = "arikitari na sekai";
	const auto r = sw | split(' ') >> back();
#endif
	return 0;
}