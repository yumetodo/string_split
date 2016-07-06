# string split like chain method
[![Run Status](https://api.shippable.com/projects/577cc6213be4f4faa56be97c/badge?branch=master)](https://app.shippable.com/projects/577cc6213be4f4faa56be97c)
[![Build Status](https://travis-ci.org/yumetodo/string_split.svg?branch=master)](https://travis-ci.org/yumetodo/string_split)

This is a **C++ header only** library to split string.

# Usage

just include ``include/string_split.hpp``.

```cpp
#include "../include/string_split.hpp"
#include <iostream>
int main()
{
    std::string s = "arikitari na world!";
    const auto s_1 = s | split(' ')[1];//"na"
    std::string s2 = "123,421,113";
    const auto s_2 = s2 | split(',') >> [](const std::string& s) {
        return std::stoi(s);
    };//[123,421,113]
    s2 | split(',') >> [](std::string&& s) {
        std::cout << s << std::endl;
    };
    /*stdout:
    123
    421
    113
    */
    return 0;
}
```

Temporary ``std::vector<std::string>`` **will not be created** becase the priority of ``operator[]/operator>>`` is higher than ``operator|``

# Compiler require
C++11 support is required(need C++14 support is required to compile testcase).

However, we support Visual Studio 2015 update2 or later.