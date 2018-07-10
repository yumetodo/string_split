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
IUTEST_TYPED_TEST(StringViewSplit, chain_front_by_singe_char)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::cpp_basic_istream<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> front();
	IUTEST_ASSERT_EQ(std::basic_string_view<char_type>(constant::cpp_basic_istream_part<char_type>()), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_front_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	constexpr auto delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim) >> front());
}
IUTEST_TYPED_TEST(StringViewSplit, chain_front_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim) >> front());
}
IUTEST_TYPED_TEST(StringViewSplit, chain_front_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim) >> front());
}
IUTEST_TYPED_TEST(StringViewSplit, chain_back_by_singe_char)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> back();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_back_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	constexpr auto delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim) >> back());
}
IUTEST_TYPED_TEST(StringViewSplit, chain_back_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim) >> back());
}
IUTEST_TYPED_TEST(StringViewSplit, chain_back_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim) >> back());
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_front)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::cpp_type_data2<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> at_first().front();
	IUTEST_ASSERT_EQ(constant::cpp_dxle_sound_c<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_back_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::cpp_type_data2<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::cpp_LoadSoundMem<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_back_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_back_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_back_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_first().back();
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::cpp_type_data2<char_type>();
	const auto re = s | split(constant::space<char_type>()) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::cpp_dxle_sound_c<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::cpp_LoadSoundMem<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_first_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_first();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::na_world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_front_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::cpp_type_data1<char_type>();
	const auto re = s | split(constant::colon<char_type>()) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::cpp_basic_istream<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_front_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_front_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_front_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_last().front();
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_back)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::cpp_type_data1<char_type>();
	const auto re = s | split(constant::colon<char_type>()) >> at_last().back();
	IUTEST_ASSERT_EQ(constant::ignore<char_type>(), re);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::cpp_type_data1<char_type>();
	const auto re = s | split(constant::colon<char_type>()) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::cpp_basic_istream<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::ignore<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(constant::space_underscore<char_type>()) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, chain_at_last_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const auto re = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> at_last();
	IUTEST_ASSERT(2u == re.size());
	IUTEST_ASSERT_EQ(constant::arikitari_na<char_type>(), re[0]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), re[1]);
}
IUTEST_TYPED_TEST(StringViewSplit, ExtractBySingeChar)
{
	using char_type = TypeParam;
	constexpr char_type space = constant::space<char_type>();
	const std::basic_string_view<char_type> s = constant::arikitari_na_world<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(space)[0]);
	IUTEST_ASSERT_EQ(constant::na<char_type>(), s | split(space)[1]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(space)[2]);
	IUTEST_EXPECT_THROW(s | split(space)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(space)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(space)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(space)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TYPED_TEST(StringViewSplit, ExtractByCStr)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	constexpr auto delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim)[0]);
	IUTEST_ASSERT_EQ(constant::na<char_type>(), s | split(delim)[1]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim)[2]);
	IUTEST_EXPECT_THROW(s | split(delim)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TYPED_TEST(StringViewSplit, ExtractByStlStr)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string<char_type> delim = constant::space_underscore<char_type>();
	IUTEST_ASSERT_EQ(constant::arikitari<char_type>(), s | split(delim)[0]);
	IUTEST_ASSERT_EQ(constant::na<char_type>(), s | split(delim)[1]);
	IUTEST_ASSERT_EQ(constant::world<char_type>(), s | split(delim)[2]);
	IUTEST_EXPECT_THROW(s | split(delim)[3], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[5], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[3250], std::out_of_range);
	IUTEST_EXPECT_THROW(s | split(delim)[std::numeric_limits<std::size_t>::max()], std::out_of_range);
}
IUTEST_TYPED_TEST(StringViewSplit, ExtractByStlStrView)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s = constant::arikitari_na_world_underscore<char_type>();
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
