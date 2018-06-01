#include "../include/string_split.hpp"
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
#include "../iutest/include/iutest.hpp"
#include "constant.hpp"
#include <iostream>
#include <array>
#include <algorithm>
template<typename T>
struct StringViewSplit : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(StringViewSplit, ::iutest::Types<char, wchar_t, char16_t, char32_t>);
IUTEST_TYPED_TEST(StringViewSplit, chain_front_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	constexpr auto delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim) >> front());
}
#endif
