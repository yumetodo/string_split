﻿/*=============================================================================
  Copyright (C) 2016 yumetodo

  Distributed under the Boost Software License, Version 1.0.
  (See http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include "../include/string_split.hpp"
#include "../iutest/include/iutest.hpp"
#include "constant.hpp"
#include <iostream>
#include <array>
#include <algorithm>
template<typename T>
struct StringSplitLvalue : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(StringSplitLvalue, ::iutest::Types<char, wchar_t, char16_t, char32_t>);
IUTEST_TYPED_TEST(StringSplitLvalue, chain_front_by_singe_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::cpp_basic_istream<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> front();
	IUTEST_ASSERT_EQ(constant::cpp_basic_istream_part<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_front_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	constexpr auto delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim) >> front());
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_front_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim) >> front());
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, chain_front_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim) >> front());
}
#endif
IUTEST_TYPED_TEST(StringSplitLvalue, chain_back_by_singe_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> back();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_back_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	constexpr auto delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim) >> back());
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_back_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim) >> back());
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, chain_back_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim) >> back());
}
#endif
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_front)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::cpp_type_data2<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> at_first().front();
	IUTEST_ASSERT_EQ(constant::cpp_dxle_sound_c<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_back_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::cpp_type_data2<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::cpp_LoadSoundMem<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_back_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_back_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re);
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_back_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re);
}
#endif
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::cpp_type_data2<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::cpp_dxle_sound_c<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::cpp_LoadSoundMem<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re[1]);
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_first_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re[1]);
}
#endif
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_front_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::cpp_type_data1<char_type>();
	const auto re = s | split(constant::colon<char_type>()) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::cpp_basic_istream<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_front_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_front_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re);
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_front_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re);
}
#endif
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_back)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::cpp_type_data1<char_type>();
	const auto re = s | split(constant::colon<char_type>()) >> at_last().back();
	IUTEST_ASSERT_EQ(constant::ignore<char_type>(), re);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::cpp_type_data1<char_type>();
	const auto re = s | split(constant::colon<char_type>()) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::cpp_basic_istream<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::ignore<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re[1]);
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, chain_at_last_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re[1]);
}
#endif
IUTEST_TYPED_TEST(StringSplitLvalue, ExtractBySingeChar)
{
	using char_type = TypeParam;
	constexpr char_type space = constant::space<char_type>();
	const std::basic_string<char_type> s = constant::arikitari_na_world<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(space)[0]);
	IUTEST_ASSERT_EQ(constant::na<char_type>(), s | split(space)[1]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(space)[2]);
	IUTEST_EXPECT_THROW(s | split(space)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(space)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(space)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(space)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TYPED_TEST(StringSplitLvalue, ExtractByCStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	constexpr auto delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim)[0]);
	IUTEST_ASSERT_EQ(constant::na<char_type>(), s | split(delim)[1]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim)[2]);
	IUTEST_EXPECT_THROW(s | split(delim)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TYPED_TEST(StringSplitLvalue, ExtractByStlStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim)[0]);
	IUTEST_ASSERT_EQ(constant::na<char_type>(), s | split(delim)[1]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim)[2]);
	IUTEST_EXPECT_THROW(s | split(delim)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, ExtractByStlStrView)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim)[0]);
	IUTEST_ASSERT_EQ(constant::na<char_type>(), s | split(delim)[1]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim)[2]);
	IUTEST_EXPECT_THROW(s | split(delim)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
#endif
namespace StringSplitLvalue_SplitBySingeChar {
	template<typename CharType, std::enable_if_t<!std::is_same<CharType, char>::value, std::nullptr_t> = nullptr>
	void without_char()
	{
		using char_type = CharType;
		const std::basic_string<char_type> s2 = constant::arikitarina_sekai<char_type>();
		const std::basic_string<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(constant::space<char_type>());
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
	template<typename CharType, std::enable_if_t<std::is_same<CharType, char>::value, std::nullptr_t> = nullptr>
	void without_char(){}
}
IUTEST_TYPED_TEST(StringSplitLvalue, SplitBySingeChar)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s1 = constant::arikitari_na_world<char_type>();
	const std::basic_string<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(constant::space<char_type>());
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	StringSplitLvalue_SplitBySingeChar::without_char<char_type>();
}
namespace StringSplitLvalue_SplitByCStr {
	template<typename CharType, std::enable_if_t<!std::is_same<CharType, char>::value, std::nullptr_t> = nullptr>
	void without_char()
	{
		using char_type = CharType;
		const std::basic_string<char_type> s2 = constant::arikitarina_sekai_wspace<char_type>();
		const std::basic_string<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(constant::wspace<char_type>());
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
	template<typename CharType, std::enable_if_t<std::is_same<CharType, char>::value, std::nullptr_t> = nullptr>
	void without_char() {}
}
IUTEST_TYPED_TEST(StringSplitLvalue, SplitByCStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s1 = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(constant::space_underscore<char_type>());
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	StringSplitLvalue_SplitByCStr::without_char<char_type>();
}
namespace StringSplitLvalue_SplitByStlStr {
	template<typename CharType, std::enable_if_t<!std::is_same<CharType, char>::value, std::nullptr_t> = nullptr>
	void without_char()
	{
		using char_type = CharType;
		const std::basic_string<char_type> s2 = constant::arikitarina_sekai_wspace<char_type>();
		const std::basic_string<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(std::basic_string<char_type>(constant::wspace<char_type>()));
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
	template<typename CharType, std::enable_if_t<std::is_same<CharType, char>::value, std::nullptr_t> = nullptr>
	void without_char() {}
}
IUTEST_TYPED_TEST(StringSplitLvalue, SplitByStlStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s1 = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(std::basic_string<char_type>(constant::space_underscore<char_type>()));
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	StringSplitLvalue_SplitByStlStr::without_char<char_type>();
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalue, SplitByStlStrView)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s1 = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>()));
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	if constexpr(!std::is_same_v<char_type, char>) {
		const std::basic_string<char_type> s2 = constant::arikitarina_sekai_wspace<char_type>();
		const std::basic_string<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(std::basic_string<char_type>(constant::wspace<char_type>()));
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
}
#endif
template<typename T>
struct StringSplitLvalueCovertToInt : public ::iutest::Test {};
IUTEST_TYPED_TEST_CASE(StringSplitLvalueCovertToInt, ::iutest::Types<char, wchar_t>);
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, BySingeChar)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(constant::comma<char_type>()) >> [](const std::basic_string<char_type>& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, ByCStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113_with_space<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(constant::space_comma<char_type>()) >> [](const std::basic_string<char_type>& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, ByStlStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113_with_space<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(std::basic_string<char_type>(constant::space_comma<char_type>())) >> [](const std::basic_string<char_type>& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, ByStlStrView)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113_with_space<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	const auto re2 = s | split(std::basic_string_view<char_type>(constant::space_comma<char_type>())) >> [](const std::basic_string<char_type>& s) {
		return std::stoi(s);
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
#endif
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, NoReturnBySingeChar)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(constant::comma<char_type>()) >> [&re2](const std::basic_string<char_type>& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, NoReturnByCStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113_with_space<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(constant::space_comma<char_type>()) >> [&re2](const std::basic_string<char_type>& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, NoReturnByStlStr)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113_with_space<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(std::basic_string<char_type>(constant::space_comma<char_type>())) >> [&re2](const std::basic_string<char_type>& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
IUTEST_TYPED_TEST(StringSplitLvalueCovertToInt, NoReturnByStlStrView)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::csv_data_123_421_113_with_space<char_type>();
	constexpr std::array<int, 3> re1{ { 123, 421, 113 } };
	std::vector<int> re2;
	re2.reserve(3);
	s | split(std::basic_string_view<char_type>(constant::space_comma<char_type>())) >> [&re2](const std::basic_string<char_type>& s) {
		return re2.push_back(std::stoi(s));
	};
	IUTEST_ASSERT_TRUE(std::equal(re1.begin(), re1.end(), re2.begin(), re2.end()));
}
#endif
