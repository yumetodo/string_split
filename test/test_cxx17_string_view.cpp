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
IUTEST_TYPED_TEST(StringViewSplit, SplitBySingeChar)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s1 = constant::arikitari_na_world<char_type>();
	const std::basic_string_view<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(constant::space<char_type>());
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	if constexpr(!std::is_same_v<char_type, char>) {
		const std::basic_string_view<char_type> s2 = constant::arikitarina_sekai<char_type>();
		const std::basic_string_view<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(constant::space<char_type>());
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
}
IUTEST_TYPED_TEST(StringViewSplit, SplitByCStr)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s1 = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(constant::space_underscore<char_type>());
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	if constexpr(!std::is_same_v<char_type, char>) {
		const std::basic_string_view<char_type> s2 = constant::arikitarina_sekai_wspace<char_type>();
		const std::basic_string_view<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(constant::wspace<char_type>());
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
}
IUTEST_TYPED_TEST(StringViewSplit, SplitByStlStr)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s1 = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(std::basic_string<char_type>(constant::space_underscore<char_type>()));
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	if constexpr(!std::is_same_v<char_type, char>) {
		const std::basic_string_view<char_type> s2 = constant::arikitarina_sekai_wspace<char_type>();
		const std::basic_string_view<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(std::basic_string<char_type>(constant::wspace<char_type>()));
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
}
IUTEST_TYPED_TEST(StringViewSplit, SplitByStlStrView)
{
	using char_type = TypeParam;
	const std::basic_string_view<char_type> s1 = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> re1_1[] = { constant::arikitari<char_type>(), constant::na<char_type>(), constant::world<char_type>() };
	const auto re1_2 = s1 | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>()));
	IUTEST_ASSERT_TRUE(std::equal(std::begin(re1_1), std::end(re1_1), re1_2.begin(), re1_2.end()));
	if constexpr(!std::is_same_v<char_type, char>) {
		const std::basic_string_view<char_type> s2 = constant::arikitarina_sekai_wspace<char_type>();
		const std::basic_string_view<char_type> re2_1[] = { constant::arikitarina<char_type>(), constant::sekai<char_type>() };
		const auto re2_2 = s2 | split(std::basic_string<char_type>(constant::wspace<char_type>()));
		IUTEST_ASSERT_TRUE(std::equal(std::begin(re2_1), std::end(re2_1), re2_2.begin(), re2_2.end()));
	}
}
IUTEST_TYPED_TEST(StringViewSplit, chain_func_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world<char_type>();
	const std::basic_string_view<char_type> sv = s;
	std::vector<std::size_t> s_hash;
	std::vector<std::size_t> sv_hash;
	s_hash.reserve(3);
	sv_hash.reserve(3);
	s | split(constant::space<char_type>()) >> [&s_hash](const std::basic_string<char_type>& part) {
		s_hash.emplace_back(std::hash<std::basic_string<char_type>>()(part));
	};
	sv | split(constant::space<char_type>()) >> [&sv_hash](const std::basic_string_view<char_type>& part) {
		sv_hash.emplace_back(std::hash<std::basic_string_view<char_type>>()(part));
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
IUTEST_TYPED_TEST(StringViewSplit, chain_func_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> sv = s;
	std::vector<std::size_t> s_hash;
	std::vector<std::size_t> sv_hash;
	s_hash.reserve(3);
	sv_hash.reserve(3);
	s | split(constant::space_underscore<char_type>()) >> [&s_hash](const std::basic_string<char_type>& part) {
		s_hash.emplace_back(std::hash<std::basic_string<char_type>>()(part));
	};
	sv | split(constant::space_underscore<char_type>()) >> [&sv_hash](const std::basic_string_view<char_type>& part) {
		sv_hash.emplace_back(std::hash<std::basic_string_view<char_type>>()(part));
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
IUTEST_TYPED_TEST(StringViewSplit, chain_func_by_single_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> sv = s;
	std::vector<std::size_t> s_hash;
	std::vector<std::size_t> sv_hash;
	s_hash.reserve(3);
	sv_hash.reserve(3);
	s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> [&s_hash](const std::basic_string<char_type>& part) {
		s_hash.emplace_back(std::hash<std::basic_string<char_type>>()(part));
	};
	sv | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> [&sv_hash](const std::basic_string_view<char_type>& part) {
		sv_hash.emplace_back(std::hash<std::basic_string_view<char_type>>()(part));
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
IUTEST_TYPED_TEST(StringViewSplit, chain_func_by_single_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> sv = s;
	std::vector<std::size_t> s_hash;
	std::vector<std::size_t> sv_hash;
	s_hash.reserve(3);
	sv_hash.reserve(3);
	s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> [&s_hash](const std::basic_string<char_type>& part) {
		s_hash.emplace_back(std::hash<std::basic_string<char_type>>()(part));
	};
	sv | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> [&sv_hash](const std::basic_string_view<char_type>& part) {
		sv_hash.emplace_back(std::hash<std::basic_string_view<char_type>>()(part));
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
IUTEST_TYPED_TEST(StringViewSplit, chain_conv_func_by_single_char)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world<char_type>();
	const std::basic_string_view<char_type> sv = s;
	auto s_hash = s | split(constant::space<char_type>()) >> [](const std::basic_string<char_type>& part) {
		return std::hash<std::basic_string<char_type>>()(part);
	};
	auto sv_hash = sv | split(constant::space<char_type>()) >> [](const std::basic_string_view<char_type>& part) {
		return std::hash<std::basic_string_view<char_type>>()(part);
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
IUTEST_TYPED_TEST(StringViewSplit, chain_conv_func_by_c_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> sv = s;
	auto s_hash = s | split(constant::space_underscore<char_type>()) >> [](const std::basic_string<char_type>& part) {
		return std::hash<std::basic_string<char_type>>()(part);
	};
	auto sv_hash = sv | split(constant::space_underscore<char_type>()) >> [](const std::basic_string_view<char_type>& part) {
		return std::hash<std::basic_string_view<char_type>>()(part);
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
IUTEST_TYPED_TEST(StringViewSplit, chain_conv_func_by_stl_str)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> sv = s;
	auto s_hash = s | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> [](const std::basic_string<char_type>& part) {
		return std::hash<std::basic_string<char_type>>()(part);
	};
	auto sv_hash = sv | split(std::basic_string<char_type>(constant::space_underscore<char_type>())) >> [](const std::basic_string_view<char_type>& part) {
		return std::hash<std::basic_string_view<char_type>>()(part);
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
IUTEST_TYPED_TEST(StringViewSplit, chain_conv_func_by_stl_str_view)
{
	using char_type = TypeParam;
	const std::basic_string<char_type> s = constant::arikitari_na_world_underscore<char_type>();
	const std::basic_string_view<char_type> sv = s;
	auto s_hash = s | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> [](const std::basic_string<char_type>& part) {
		return std::hash<std::basic_string<char_type>>()(part);
	};
	auto sv_hash = sv | split(std::basic_string_view<char_type>(constant::space_underscore<char_type>())) >> [](const std::basic_string_view<char_type>& part) {
		return std::hash<std::basic_string_view<char_type>>()(part);
	};
	//These hashes equal the hashes of corresponding std::basic_string classes:
	//If S is one of the standard basic_string types, SV is the corresponding string view type,
	//and s is an object of type S, then std::hash<S>()(s) == std::hash<SV>()(SV(s)). 
	IUTEST_ASSERT_TRUE(std::equal(s_hash.begin(), s_hash.end(), sv_hash.begin(), sv_hash.end()));
}
