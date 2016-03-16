namespace detail {
	namespace type_traits {
		//
		// is_char_type
		//
		template<typename T> struct is_char_type : public std::false_type {};
		template<typename T> struct is_char_type<T const> : public type_traits::is_char_type<T> {};
		template<typename T> struct is_char_type<T volatile> : public type_traits::is_char_type<T> {};
		template<typename T> struct is_char_type<T const volatile> : public type_traits::is_char_type<T> {};
		template<> struct is_char_type<char> : public std::true_type {};
		template<> struct is_char_type<wchar_t> : public std::true_type	{};
		template<> struct is_char_type<char16_t> : public std::true_type {};
		template<> struct is_char_type<char32_t> : public std::true_type {};
		//
		// is_c_str
		//
		template<typename T>
		struct is_c_str : std::integral_constant<bool, std::is_pointer<T>::value && is_char_type<std::remove_pointer_t<T>>::value> {};
		//
		// is_stl_string
		//
		template<typename T>
		struct is_stl_string : std::conditional_t<std::is_reference<T>::value, is_stl_string<std::remove_reference_t<T>>, std::false_type> {};
		template<typename T> struct is_stl_string<T const> : is_stl_string<T> {};
		template<typename T> struct is_stl_string<T volatile> : is_stl_string<T> {};
		template<typename T> struct is_stl_string<T const volatile> : is_stl_string<T> {};
		template<typename CharType>
		struct is_stl_string<std::basic_string<CharType>> : std::integral_constant<bool, is_char_type<std::remove_cv_t<CharType>>::value> {};
	}
	template<typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct Split_helper_index;
	template<typename CharType>
	struct Split_helper_index<CharType, true, false, false> { 
		using char_type = CharType;
		CharType delim; std::size_t index;
	};
	template<typename CStr>
	struct Split_helper_index<CStr, false, true, false> {
		using char_type = std::remove_pointer_t<CStr>;
		const char_type* delim; std::size_t index;
	};
	template<typename StlString>
	struct Split_helper_index<StlString, false, false, true> {
		using char_type = typename StlString::value_type;
		std::basic_string<char_type> delim; std::size_t index;
	};
	template<typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct Split_helper;
	template<typename CharType>
	struct Split_helper<CharType, true, false, false> {
		using char_type = CharType;
		CharType delim;
		constexpr Split_helper_index<CharType, true, false, false> operator[](std::size_t n) const noexcept { return{ delim, n }; }
		constexpr Split_helper_index<CharType, true, false, false> operator[](CsvParseLevel n) const noexcept { return this->operator[](static_cast<std::size_t>(n)); }
	};
	template<typename CStr>
	struct Split_helper<CStr, false, true, false> {
		using char_type = std::remove_pointer_t<CStr>;
		const char_type* delim;
		constexpr Split_helper_index<CStr, false, true, false> operator[](std::size_t n) const noexcept { return{ delim, n }; }
		constexpr Split_helper_index<CStr, false, true, false> operator[](CsvParseLevel n) const noexcept { return this->operator[](static_cast<std::size_t>(n)); }
	};
	template<typename StlString>
	struct Split_helper<StlString, false, false, true> {
		using char_type = typename StlString::value_type;
		std::basic_string<char_type> delim;
		constexpr Split_helper_index<StlString, false, true, false> operator[](std::size_t n) const noexcept { return{ std::move(delim), n }; }
		constexpr Split_helper_index<StlString, false, true, false> operator[](CsvParseLevel n) const noexcept { return this->operator[](static_cast<std::size_t>(n)); }
	};
	//区切り文字1文字の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const std::basic_string<CharType>& str, const Split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>& info) 
		-> std::enable_if_t<is_single_char && !is_c_str && !is_stl_string && std::is_same<CharType, typename Split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, std::basic_string<CharType>>
	{
		std::size_t pre = 0, pos = 0;
		for (size_t i = 0; i < info.index + 1; ++i) {
			pre = pos;
			pos = str.find_first_of(info.delim, pos) + 1;
		}
		return str.substr(pre, pos - pre - 1);
	}
	//区切り文字複数の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const std::basic_string<CharType>& str, const Split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> std::enable_if_t<!is_single_char && (is_c_str || is_stl_string) && std::is_same<CharType, typename Split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, std::basic_string<CharType>>
	{
		std::size_t pre = 0, pos = 0;
		for (size_t i = 0; i < info.index + 1; ++i) {
			pre = pos = str.find_first_not_of(str[pos], pos);
			pos = str.find_first_of(info.delim, pos) + 1;
		}
		return str.substr(pre, pos - pre - 1);
	}
	//区切り文字1文字の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const std::basic_string<CharType>& str, const Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> std::enable_if_t<is_single_char && !is_c_str && !is_stl_string && std::is_same<CharType, typename Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, vector<std::basic_string<CharType>>>
	{
		vector<std::basic_string<CharType>> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != std::basic_string<CharType>::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<std::size_t>::max() / 2 < re.size()) ? std::numeric_limits<std::size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		re.emplace_back(str, current, str.size() - current);
		return re;
	}
	//区切り文字複数の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const std::basic_string<CharType>& str, const Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> std::enable_if_t<!is_single_char && (is_c_str || is_stl_string) && std::is_same<CharType, typename Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, vector<std::basic_string<CharType>>>
	{
		vector<std::basic_string<CharType>> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current); 
			current != basic_string<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<std::size_t>::max() / 2 < re.size()) ? std::numeric_limits<std::size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		re.emplace_back(str, current, str.size() - current);
		return re;
	}
	//区切り文字1文字の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (std::basic_string<CharType>&& str, const Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> std::enable_if_t<is_single_char && !is_c_str && !is_stl_string && std::is_same<CharType, typename Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, vector<std::basic_string<CharType>>>
	{
		vector<std::basic_string<CharType>> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != std::basic_string<CharType>::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<std::size_t>::max() / 2 < re.size()) ? std::numeric_limits<std::size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		str.erase(0, current);
		re.emplace_back(std::move(str));
		return re;
	}
	//区切り文字複数の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (std::basic_string<CharType>&& str, const Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> std::enable_if_t<!is_single_char && (is_c_str || is_stl_string) && std::is_same<CharType, typename Split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, vector<std::basic_string<CharType>>>
	{
		vector<std::basic_string<CharType>> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			found != std::basic_string<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
			) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<std::size_t>::max() / 2 < re.size()) ? std::numeric_limits<std::size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		str.erase(0, current);
		re.emplace_back(std::move(str));
		return re;
	}
}
template<typename CharType, std::enable_if_t<detail::type_traits::is_char_type<CharType>::value, std::nullptr_t> = nullptr>
detail::Split_helper<CharType, true, false, false> Split(CharType delim) noexcept { return{ delim }; }
template<typename CStr, std::enable_if_t<detail::type_traits::is_c_str<CStr>::value, std::nullptr_t> = nullptr>
detail::Split_helper<CStr, false, true, false> Split(CStr delim) noexcept { return{ delim }; }
template<typename StlString, std::enable_if_t<detail::type_traits::is_stl_string<StlString>::value, std::nullptr_t> = nullptr>
detail::Split_helper<StlString, false, false, true> Split(StlString delim) noexcept { return{ std::move(delim }; }
