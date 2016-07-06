#ifdef __WANDBOX__
#include "string_split.hpp"
#else
#include "../include/string_split.hpp"
#endif
#include "../iutest/include/iutest.hpp"
#include <iostream>
#include <array>
#include <algorithm>
IUTEST_TEST(ExtractBySingeCharTest, type_char) {
	std::string s = "arikitari na world!";
	IUTEST_ASSERT_EQ("arikitari", s | split(' ')[0]);
	IUTEST_ASSERT_EQ("na", s | split(' ')[1]);
	IUTEST_ASSERT_EQ("world!", s | split(' ')[2]);
	IUTEST_EXPECT_THROW(s | split(' ')[3], std::out_of_range);
}
IUTEST_TEST(ExtractBySingeCharTest, type_wchar_t) {
	std::wstring s = L"arikitari na world!";
	IUTEST_ASSERT_EQ(L"arikitari", s | split(L' ')[0]);
	IUTEST_ASSERT_EQ(L"na", s | split(L' ')[1]);
	IUTEST_ASSERT_EQ(L"world!", s | split(L' ')[2]);
	IUTEST_EXPECT_THROW(s | split(L' ')[3], std::out_of_range);
}
IUTEST_TEST(ExtractBySingeCharTest, type_char16_t) {
	std::u16string s = u"arikitari na world!";
	IUTEST_ASSERT_EQ(u"arikitari", s | split(u' ')[0]);
	IUTEST_ASSERT_EQ(u"na", s | split(u' ')[1]);
	IUTEST_ASSERT_EQ(u"world!", s | split(u' ')[2]);
	IUTEST_EXPECT_THROW(s | split(u' ')[3], std::out_of_range);
}
IUTEST_TEST(ExtractBySingeCharTest, type_char32_t) {
	std::u32string s = U"arikitari na world!";
	IUTEST_ASSERT_EQ(U"arikitari", s | split(U' ')[0]);
	IUTEST_ASSERT_EQ(U"na", s | split(U' ')[1]);
	IUTEST_ASSERT_EQ(U"world!", s | split(U' ')[2]);
	IUTEST_EXPECT_THROW(s | split(U' ')[3], std::out_of_range);
}
IUTEST_TEST(ExtractByCStrTest, type_char) {
	std::string s = "arikitari na_world!";
	const char* delem = "_ ";
	IUTEST_ASSERT_EQ("arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ("na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ("world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
}
IUTEST_TEST(ExtractByCStrTest, type_wchar_t) {
	std::wstring s = L"arikitari na_world!";
	const wchar_t* delem = L"_ ";
	IUTEST_ASSERT_EQ(L"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(L"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(L"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
}
IUTEST_TEST(ExtractByCStrTest, type_char16_t) {
	std::u16string s = u"arikitari na_world!";
	const char16_t* delem = u"_ ";
	IUTEST_ASSERT_EQ(u"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(u"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(u"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
}
IUTEST_TEST(ExtractByCStrTest, type_char32_t) {
	std::u32string s = U"arikitari na_world!";
	const char32_t* delem = U"_ ";
	IUTEST_ASSERT_EQ(U"arikitari", s | split(delem)[0]);
	IUTEST_ASSERT_EQ(U"na", s | split(delem)[1]);
	IUTEST_ASSERT_EQ(U"world!", s | split(delem)[2]);
	IUTEST_EXPECT_THROW(s | split(delem)[3], std::out_of_range);
}

IUTEST_TEST(SplitBySingeCharTest, type_char) {
	const std::string s = "arikitari na world!";
	const std::vector<std::string> re1 = { "arikitari", "na", "world!" };
	const auto re2 = s | split(' ');
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitBySingeCharTest, type_wchar_t) {
	const std::wstring s = L"arikitari na world!";
	const std::vector<std::wstring> re1 = { L"arikitari", L"na", L"world!" };
	const auto re2 = s | split(L' ');
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitBySingeCharTest, type_char16_t) {
	const std::u16string s = u"arikitari na world!";
	const std::vector<std::u16string> re1 = { u"arikitari", u"na", u"world!" };
	const auto re2 = s | split(u' ');
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitBySingeCharTest, type_char32_t) {
	const std::u32string s = U"arikitari na world!";
	const std::vector<std::u32string> re1 = { U"arikitari", U"na", U"world!" };
	const auto re2 = s | split(U' ');
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitCovertToIntBySingeCharTest, type_char) {
	const std::string s = "123,421,113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(',') >> [](const std::string& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TEST(SplitCovertToIntBySingeCharTest, type_wchar_t) {
	const std::wstring s = L"123,421,113";
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(L',') >> [](const std::wstring& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}

int main(int argc, char** argv)
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}