#ifndef STRING_SPLIT_TEST_CONSTANT_HPP_
#define STRING_SPLIT_TEST_CONSTANT_HPP_
namespace constant {
#define STRING_SPLIT_TEST_CONSTANT_REGISTER_CHAR(identifier, no_prefix_char_literal) \
	template<typename CharType> inline constexpr CharType identifier(); \
	template<> inline constexpr char identifier<char>() { return no_prefix_char_literal; } \
	template<> inline constexpr wchar_t identifier<wchar_t>() { return L ## no_prefix_char_literal; } \
	template<> inline constexpr char16_t identifier<char16_t>() { return u ## no_prefix_char_literal; } \
	template<> inline constexpr char32_t identifier<char32_t>() { return U ## no_prefix_char_literal; }
#define STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(identifier, no_prefix_string_literal) \
	template<typename CharType> inline constexpr const CharType* identifier(); \
	template<> inline constexpr const char* identifier<char>() { return no_prefix_string_literal; } \
	template<> inline constexpr const wchar_t* identifier<wchar_t>() { return L ## no_prefix_string_literal; } \
	template<> inline constexpr const char16_t* identifier<char16_t>() { return u ## no_prefix_string_literal; } \
	template<> inline constexpr const char32_t* identifier<char32_t>() { return U ## no_prefix_string_literal; }
#define STRING_SPLIT_TEST_CONSTANT_REGISTER_USTRING(identifier, no_prefix_string_literal) \
	template<typename CharType> inline constexpr const CharType* identifier(); \
	template<> inline constexpr const wchar_t* identifier<wchar_t>() { return L ## no_prefix_string_literal; } \
	template<> inline constexpr const char16_t* identifier<char16_t>() { return u ## no_prefix_string_literal; } \
	template<> inline constexpr const char32_t* identifier<char32_t>() { return U ## no_prefix_string_literal; }

#ifdef __GNUC__
#	pragma GCC diagnostic push
#	pragma GCC diagnostic ignored "-Wpedantic"
#endif
	STRING_SPLIT_TEST_CONSTANT_REGISTER_CHAR(space, ' ');
	STRING_SPLIT_TEST_CONSTANT_REGISTER_CHAR(comma, ',');
	STRING_SPLIT_TEST_CONSTANT_REGISTER_CHAR(colon, ':');
	STRING_SPLIT_TEST_CONSTANT_REGISTER_USTRING(wspace, "　");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(space_underscore, "_ ");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(space_comma, ", ");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(arikitari_na_world, "arikitari na world!");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(arikitari_na_world_underscore, "arikitari na_world!");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(arikitari_na, "arikitari na");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(na_world, "na_world!");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(arikitari, "arikitari");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(na, "na");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(world, "world!");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_USTRING(arikitarina_sekai, "ありきたりな 世界");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_USTRING(arikitarina_sekai_wspace, "ありきたりな　世界");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_USTRING(arikitarina, "ありきたりな");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_USTRING(sekai, "世界");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(csv_data_123_421_113, "123,421,113");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(csv_data_123_421_113_with_space, "123, 421, 113");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(cpp_type_data1, "std::basic_istream<char, std::char_traits<char> >::ignore");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(cpp_type_data2, "dxle::sound_c LoadSoundMem");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(cpp_basic_istream, "std::basic_istream<char, std::char_traits<char> >");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(cpp_basic_istream_part, "std::basic_istream<char,");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(cpp_dxle_sound_c, "dxle::sound_c");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(cpp_LoadSoundMem, "LoadSoundMem");
	STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING(ignore, "ignore");
#ifdef __GNUC__
#	pragma GCC diagnostic pop
#endif

#undef STRING_SPLIT_TEST_CONSTANT_REGISTER_CHAR
#undef STRING_SPLIT_TEST_CONSTANT_REGISTER_STRING
#undef STRING_SPLIT_TEST_CONSTANT_REGISTER_USTRING
}
#endif
