/*=============================================================================
  Copyright (C) 2016 yumetodo

  Distributed under the Boost Software License, Version 1.0.
  (See http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "../include/string_split.hpp"
#include "../iutest/include/iutest.hpp"
#include <iostream>
#include <array>
#include <algorithm>
IUTEST_TEST(ExtractLvalueBySingeCharTest, type_char) {
	std::string s = "arikitari na world!";
	IUTEST_ASSERT_EQ("arikitari", s | split(' ')[0]);
	IUTEST_ASSERT_EQ("na", s | split(' ')[1]);
	IUTEST_ASSERT_EQ("world!", s | split(' ')[2]);
	IUTEST_EXPECT_THROW(s | split(' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueBySingeCharTest, type_wchar_t) {
	std::wstring s = L"arikitari na world!";
	IUTEST_ASSERT_EQ(L"arikitari", s | split(L' ')[0]);
	IUTEST_ASSERT_EQ(L"na", s | split(L' ')[1]);
	IUTEST_ASSERT_EQ(L"world!", s | split(L' ')[2]);
	IUTEST_EXPECT_THROW(s | split(L' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(L' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(L' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(L' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueBySingeCharTest, type_char16_t) {
	std::u16string s = u"arikitari na world!";
	IUTEST_ASSERT_EQ(u"arikitari", s | split(u' ')[0]);
	IUTEST_ASSERT_EQ(u"na", s | split(u' ')[1]);
	IUTEST_ASSERT_EQ(u"world!", s | split(u' ')[2]);
	IUTEST_EXPECT_THROW(s | split(u' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(u' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(u' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(u' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueBySingeCharTest, type_char32_t) {
	std::u32string s = U"arikitari na world!";
	IUTEST_ASSERT_EQ(U"arikitari", s | split(U' ')[0]);
	IUTEST_ASSERT_EQ(U"na", s | split(U' ')[1]);
	IUTEST_ASSERT_EQ(U"world!", s | split(U' ')[2]);
	IUTEST_EXPECT_THROW(s | split(U' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(U' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(U' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(U' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByCStrTest, type_char) {
	std::string s = "arikitari na_world!";
	const char* delem = "_ ";
	IUTEST_ASSERT_EQ("arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ("na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ("world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByCStrTest, type_wchar_t) {
	std::wstring s = L"arikitari na_world!";
	const wchar_t* delem = L"_ ";
	IUTEST_ASSERT_EQ(L"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(L"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(L"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByCStrTest, type_char16_t) {
	std::u16string s = u"arikitari na_world!";
	const char16_t* delem = u"_ ";
	IUTEST_ASSERT_EQ(u"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(u"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(u"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByCStrTest, type_char32_t) {
	std::u32string s = U"arikitari na_world!";
	const char32_t* delem = U"_ ";
	IUTEST_ASSERT_EQ(U"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(U"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(U"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByStlStrTest, type_char) {
	using namespace std::literals;
	std::string s = "arikitari na_world!";
	const auto delem = "_ "s;
	static_assert(std::is_same<std::string::value_type, char>::value, "err");
	IUTEST_ASSERT_EQ("arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ("na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ("world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	std::wstring s = L"arikitari na_world!";
	const auto delem = L"_ "s;
	IUTEST_ASSERT_EQ(L"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(L"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(L"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByStlStrTest, type_char16_t) {
	using namespace std::literals;
	std::u16string s = u"arikitari na_world!";
	const auto delem = u"_ "s;
	IUTEST_ASSERT_EQ(u"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(u"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(u"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractLvalueByStlStrTest, type_char32_t) {
	using namespace std::literals;
	std::u32string s = U"arikitari na_world!";
	const auto delem = U"_ "s;
	IUTEST_ASSERT_EQ(U"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(U"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(U"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(SplitLvalueBySingeCharTest, type_char) {
	using namespace std::literals;
	const std::string s1 = "arikitari na world!";
	const auto re1_1 = { "arikitari"s, "na"s, "world!"s };
	const auto re1_2 = s1 | split(' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
}
IUTEST_TEST(SplitLvalueBySingeCharTest, type_wchar_t) {
	using namespace std::literals;
	const std::wstring s1 = L"arikitari na world!";
	const auto re1_1 = { L"arikitari"s, L"na"s, L"world!"s };
	const auto re1_2 = s1 | split(L' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::wstring s2 = L"ありきたりな 世界";
	const auto re2_1 = { L"ありきたりな"s, L"世界"s };
	const auto re2_2 = s2 | split(L' ');
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueBySingeCharTest, type_char16_t) {
	using namespace std::literals;
	const std::u16string s1 = u"arikitari na world!";
	const auto re1_1 = { u"arikitari"s, u"na"s, u"world!"s };
	const auto re1_2 = s1 | split(u' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::u16string s2 = u"ありきたりな 世界";
	const auto re2_1 = { u"ありきたりな"s, u"世界"s };
	const auto re2_2 = s2 | split(u' ');
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueBySingeCharTest, type_char32_t) {
	using namespace std::literals;
	const std::u32string s1 = U"arikitari na world!";
	const auto re1_1 = { U"arikitari"s, U"na"s, U"world!"s };
	const auto re1_2 = s1 | split(U' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::u32string s2 = U"ありきたりな 世界";
	const auto re2_1 = { U"ありきたりな"s, U"世界"s };
	const auto re2_2 = s2 | split(U' ');
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueByCStrTest, type_char) {
	using namespace std::literals;
	const std::string s1 = "arikitari_na world!";
	const auto re1_1 = { "arikitari"s, "na"s, "world!"s };
	const auto re1_2 = s1 | split(" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
}
IUTEST_TEST(SplitLvalueByCStrTest, type_wchar_t) {
	using namespace std::literals;
	const std::wstring s1 = L"arikitari_na world!";
	const auto re1_1 = { L"arikitari"s, L"na"s, L"world!"s };
	const auto re1_2 = s1 | split(L" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::wstring s2 = L"ありきたりな　世界";
	const auto re2_1 = { L"ありきたりな"s, L"世界"s };
	const auto re2_2 = s2 | split(L"　");
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueByCStrTest, type_char16_t) {
	using namespace std::literals;
	const std::u16string s1 = u"arikitari_na world!";
	const auto re1_1 = { u"arikitari"s, u"na"s, u"world!"s };
	const auto re1_2 = s1 | split(u" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::u16string s2 = u"ありきたりな　世界";
	const auto re2_1 = { u"ありきたりな"s, u"世界"s };
	const auto re2_2 = s2 | split(u"　");
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueByCStrTest, type_char32_t) {
	using namespace std::literals;
	const std::u32string s1 = U"arikitari_na world!";
	const auto re1_1 = { U"arikitari"s, U"na"s, U"world!"s };
	const auto re1_2 = s1 | split(U" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::u32string s2 = U"ありきたりな　世界";
	const auto re2_1 = { U"ありきたりな"s, U"世界"s };
	const auto re2_2 = s2 | split(U"　");
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueByStlStrTest, type_char) {
	using namespace std::literals;
	const std::string s1 = "arikitari_na world!";
	const auto re1_1 = { "arikitari"s, "na"s, "world!"s };
	const auto re1_2 = s1 | split(" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
}
IUTEST_TEST(SplitLvalueByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	const std::wstring s1 = L"arikitari_na world!";
	const auto re1_1 = { L"arikitari"s, L"na"s, L"world!"s };
	const auto re1_2 = s1 | split(L" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::wstring s2 = L"ありきたりな　世界";
	const auto re2_1 = { L"ありきたりな"s, L"世界"s };
	const auto re2_2 = s2 | split(L"　"s);
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueByStlStrTest, type_char16_t) {
	using namespace std::literals;
	const std::u16string s1 = u"arikitari_na world!";
	const auto re1_1 = { u"arikitari"s, u"na"s, u"world!"s };
	const auto re1_2 = s1 | split(u" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::u16string s2 = u"ありきたりな　世界";
	const auto re2_1 = { u"ありきたりな"s, u"世界"s };
	const auto re2_2 = s2 | split(u"　"s);
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueByStlStrTest, type_char32_t) {
	using namespace std::literals;
	const std::u32string s1 = U"arikitari_na world!";
	const auto re1_1 = { U"arikitari"s, U"na"s, U"world!"s };
	const auto re1_2 = s1 | split(U" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const std::u32string s2 = U"ありきたりな　世界";
	const auto re2_1 = { U"ありきたりな"s, U"世界"s };
	const auto re2_2 = s2 | split(U"　"s);
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntBySingeCharTest, type_char) {
	const std::string s = "123,421,113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(',') >> [](const std::string& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntBySingeCharTest, type_wchar_t) {
	const std::wstring s = L"123,421,113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(L',') >> [](const std::wstring& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntByCStrTest, type_char) {
	const std::string s = "123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(", ") >> [](const std::string& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntByCStrTest, type_wchar_t) {
	const std::wstring s = L"123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(L", ") >> [](const std::wstring& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntByStlStrTest, type_char) {
	using namespace std::literals;
	const std::string s = "123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(", "s) >> [](const std::string& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	const std::wstring s = L"123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(L", "s) >> [](const std::wstring& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntNoReturnBySingeCharTest, type_char) {
	const std::string s = "123,421,113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(',') >> [&re2](const std::string& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntNoReturnBySingeCharTest, type_wchar_t) {
	const std::wstring s = L"123,421,113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(L',') >> [&re2](const std::wstring& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntNoReturnByCStrTest, type_char) {
	const std::string s = "123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(", ") >> [&re2](const std::string& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntNoReturnByCStrTest, type_wchar_t) {
	const std::wstring s = L"123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(L", ") >> [&re2](const std::wstring& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntNoReturnByStlStrTest, type_char) {
	using namespace std::literals;
	const std::string s = "123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(", "s) >> [&re2](const std::string& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitLvalueCovertToIntNoReturnByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	const std::wstring s = L"123, 421, 113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(L", "s) >> [&re2](const std::wstring& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(ExtractRvalueBySingeCharTest, type_char) {
	using namespace std::literals;
	IUTEST_ASSERT_EQ("arikitari", "arikitari na world!"s | split(' ')[0]);
	IUTEST_ASSERT_EQ("na", "arikitari na world!"s | split(' ')[1]);
	IUTEST_ASSERT_EQ("world!", "arikitari na world!"s | split(' ')[2]);
	IUTEST_EXPECT_THROW("arikitari na world!"s | split(' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na world!"s | split(' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na world!"s | split(' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na world!"s | split(' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueBySingeCharTest, type_wchar_t) {
	using namespace std::literals;
	IUTEST_ASSERT_EQ(L"arikitari", L"arikitari na world!"s | split(L' ')[0]);
	IUTEST_ASSERT_EQ(L"na", L"arikitari na world!"s | split(L' ')[1]);
	IUTEST_ASSERT_EQ(L"world!", L"arikitari na world!"s | split(L' ')[2]);
	IUTEST_EXPECT_THROW(L"arikitari na world!"s | split(L' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na world!"s | split(L' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na world!"s | split(L' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na world!"s | split(L' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueBySingeCharTest, type_char16_t) {
	using namespace std::literals;
	IUTEST_ASSERT_EQ(u"arikitari", u"arikitari na world!"s | split(u' ')[0]);
	IUTEST_ASSERT_EQ(u"na", u"arikitari na world!"s | split(u' ')[1]);
	IUTEST_ASSERT_EQ(u"world!", u"arikitari na world!"s | split(u' ')[2]);
	IUTEST_EXPECT_THROW(u"arikitari na world!"s | split(u' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na world!"s | split(u' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na world!"s | split(u' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na world!"s | split(u' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueBySingeCharTest, type_char32_t) {
	using namespace std::literals;
	IUTEST_ASSERT_EQ(U"arikitari", U"arikitari na world!"s | split(U' ')[0]);
	IUTEST_ASSERT_EQ(U"na", U"arikitari na world!"s | split(U' ')[1]);
	IUTEST_ASSERT_EQ(U"world!", U"arikitari na world!"s | split(U' ')[2]);
	IUTEST_EXPECT_THROW(U"arikitari na world!"s | split(U' ')[3], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na world!"s | split(U' ')[5], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na world!"s | split(U' ')[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na world!"s | split(U' ')[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByCStrTest, type_char) {
	using namespace std::literals;
	const char* delem = "_ ";
	IUTEST_ASSERT_EQ("arikitari", "arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ("na", "arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ("world!", "arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByCStrTest, type_wchar_t) {
	using namespace std::literals;
	const wchar_t* delem = L"_ ";
	IUTEST_ASSERT_EQ(L"arikitari", L"arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ(L"na", L"arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ(L"world!", L"arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByCStrTest, type_char16_t) {
	using namespace std::literals;
	const char16_t* delem = u"_ ";
	IUTEST_ASSERT_EQ(u"arikitari", u"arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ(u"na", u"arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ(u"world!", u"arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByCStrTest, type_char32_t) {
	using namespace std::literals;
	const char32_t* delem = U"_ ";
	IUTEST_ASSERT_EQ(U"arikitari", U"arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ(U"na", U"arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ(U"world!", U"arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByStlStrTest, type_char) {
	using namespace std::literals;
	const auto delem = "_ "s;
	IUTEST_ASSERT_EQ("arikitari", "arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ("na", "arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ("world!", "arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW("arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	const auto delem = L"_ "s;
	IUTEST_ASSERT_EQ(L"arikitari", L"arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ(L"na", L"arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ(L"world!", L"arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(L"arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByStlStrTest, type_char16_t) {
	using namespace std::literals;
	const auto delem = u"_ "s;
	IUTEST_ASSERT_EQ(u"arikitari", u"arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ(u"na", u"arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ(u"world!", u"arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(u"arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(ExtractRvalueByStlStrTest, type_char32_t) {
	using namespace std::literals;
	const auto delem = U"_ "s;
	IUTEST_ASSERT_EQ(U"arikitari", U"arikitari na_world!"s | split(delem)[0]);
	IUTEST_ASSERT_EQ(U"na", U"arikitari na_world!"s | split(delem)[1]);
	IUTEST_ASSERT_EQ(U"world!", U"arikitari na_world!"s | split(delem)[2]);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(U"arikitari na_world!"s | split(delem)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TEST(SplitRvalueBySingeCharTest, type_char) {
	using namespace std::literals;
	const auto re1_1 = { "arikitari"s, "na"s, "world!"s };
	const auto re1_2 = "arikitari na world!"s | split(' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
}
IUTEST_TEST(SplitRvalueBySingeCharTest, type_wchar_t) {
	using namespace std::literals;
	const auto re1_1 = { L"arikitari"s, L"na"s, L"world!"s };
	const auto re1_2 = L"arikitari na world!"s | split(L' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { L"ありきたりな"s, L"世界"s };
	const auto re2_2 = L"ありきたりな 世界"s | split(L' ');
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueBySingeCharTest, type_char16_t) {
	using namespace std::literals;
	const auto re1_1 = { u"arikitari"s, u"na"s, u"world!"s };
	const auto re1_2 = u"arikitari na world!"s | split(u' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { u"ありきたりな"s, u"世界"s };
	const auto re2_2 = u"ありきたりな 世界"s | split(u' ');
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueBySingeCharTest, type_char32_t) {
	using namespace std::literals;
	const auto re1_1 = { U"arikitari"s, U"na"s, U"world!"s };
	const auto re1_2 = U"arikitari na world!"s | split(U' ');
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { U"ありきたりな"s, U"世界"s };
	const auto re2_2 = U"ありきたりな 世界"s | split(U' ');
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueByCStrTest, type_char) {
	using namespace std::literals;
	const auto re1_1 = { "arikitari"s, "na"s, "world!"s };
	const auto re1_2 = "arikitari_na world!"s | split(" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
}
IUTEST_TEST(SplitRvalueByCStrTest, type_wchar_t) {
	using namespace std::literals;
	const auto re1_1 = { L"arikitari"s, L"na"s, L"world!"s };
	const auto re1_2 = L"arikitari_na world!"s | split(L" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { L"ありきたりな"s, L"世界"s };
	const auto re2_2 = L"ありきたりな　世界"s | split(L"　");
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueByCStrTest, type_char16_t) {
	using namespace std::literals;
	const auto re1_1 = { u"arikitari"s, u"na"s, u"world!"s };
	const auto re1_2 = u"arikitari_na world!"s | split(u" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { u"ありきたりな"s, u"世界"s };
	const auto re2_2 = u"ありきたりな　世界"s | split(u"　");
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueByCStrTest, type_char32_t) {
	using namespace std::literals;
	const auto re1_1 = { U"arikitari"s, U"na"s, U"world!"s };
	const auto re1_2 = U"arikitari_na world!"s | split(U" _");
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { U"ありきたりな"s, U"世界"s };
	const auto re2_2 = U"ありきたりな　世界"s | split(U"　");
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueByStlStrTest, type_char) {
	using namespace std::literals;
	const auto re1_1 = { "arikitari"s, "na"s, "world!"s };
	const auto re1_2 = "arikitari_na world!"s | split(" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
}
IUTEST_TEST(SplitRvalueByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	const auto re1_1 = { L"arikitari"s, L"na"s, L"world!"s };
	const auto re1_2 = L"arikitari_na world!"s | split(L" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { L"ありきたりな"s, L"世界"s };
	const auto re2_2 = L"ありきたりな　世界"s | split(L"　"s);
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueByStlStrTest, type_char16_t) {
	using namespace std::literals;
	const auto re1_1 = { u"arikitari"s, u"na"s, u"world!"s };
	const auto re1_2 = u"arikitari_na world!"s | split(u" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { u"ありきたりな"s, u"世界"s };
	const auto re2_2 = u"ありきたりな　世界"s | split(u"　"s);
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueByStlStrTest, type_char32_t) {
	using namespace std::literals;
	const auto re1_1 = { U"arikitari"s, U"na"s, U"world!"s };
	const auto re1_2 = U"arikitari_na world!"s | split(U" _"s);
	IUTEST_ASSERT_TRUE(std::equal(re1_1.begin(), re1_1.end(), re1_2.begin(), re1_2.end()));
	const auto re2_1 = { U"ありきたりな"s, U"世界"s };
	const auto re2_2 = U"ありきたりな　世界"s | split(U"　"s);
	IUTEST_ASSERT_TRUE(std::equal(re2_1.begin(), re2_1.end(), re2_2.begin(), re2_2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntBySingeCharTest, type_char) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = "123,421,113"s | split(',') >> [](const std::string& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntBySingeCharTest, type_wchar_t) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = L"123,421,113"s | split(L',') >> [](const std::wstring& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntByCStrTest, type_char) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = "123, 421, 113"s | split(", ") >> [](const std::string& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntByCStrTest, type_wchar_t) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = L"123, 421, 113"s | split(L", ") >> [](const std::wstring& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntByStlStrTest, type_char) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = "123, 421, 113"s | split(", "s) >> [](const std::string& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = L"123, 421, 113"s | split(L", "s) >> [](const std::wstring& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntNoReturnBySingeCharTest, type_char) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	"123,421,113"s | split(',') >> [&re2](const std::string& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntNoReturnBySingeCharTest, type_wchar_t) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	L"123,421,113"s | split(L',') >> [&re2](const std::wstring& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntNoReturnByCStrTest, type_char) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	"123, 421, 113"s | split(", ") >> [&re2](const std::string& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntNoReturnByCStrTest, type_wchar_t) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	L"123, 421, 113"s | split(L", ") >> [&re2](const std::wstring& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntNoReturnByStlStrTest, type_char) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	"123, 421, 113"s | split(", "s) >> [&re2](const std::string& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitRvalueCovertToIntNoReturnByStlStrTest, type_wchar_t) {
	using namespace std::literals;
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	L"123, 421, 113"s | split(L", "s) >> [&re2](const std::wstring& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}

int main(int argc, char** argv)
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}