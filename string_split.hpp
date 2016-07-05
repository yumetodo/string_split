#include <string>
#include <vector>
#include <type_traits>
namespace detail {
	using std::vector;
	template<typename CharType> using b_str = std::basic_string<CharType>;
	using std::is_same;
	using std::size_t;
	using std::enable_if_t;
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
		struct is_stl_string<b_str<CharType>> : std::integral_constant<bool, is_char_type<std::remove_cv_t<CharType>>::value> {};
	}
	template<typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct split_helper_index;
	template<typename CharType>
	struct split_helper_index<CharType, true, false, false> { 
		using char_type = CharType;
		CharType delim; size_t index;
	};
	template<typename CStr>
	struct split_helper_index<CStr, false, true, false> {
		using char_type = std::remove_pointer_t<CStr>;
		const char_type* delim; size_t index;
	};
	template<typename StlString>
	struct split_helper_index<StlString, false, false, true> {
		using char_type = typename StlString::value_type;
		b_str<char_type> delim; size_t index;
	};
	template<typename DelimType, typename FuncType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct split_helper_conv_func;
	template<typename CharType, typename FuncType>
	struct split_helper_conv_func<CharType, FuncType, true, false, false> {
		using char_type = CharType;
		using result_type = decltype(std::declval<FuncType>()(std::declval<std::basic_string<char_type>>()));
		static constexpr bool result_is_void = std::is_same<void, result_type>::value;
		CharType delim; FuncType f;
	};
	template<typename DelimType, typename FuncType>
	struct split_helper_conv_func<DelimType, FuncType, false, true, false> {
		using char_type = std::remove_pointer_t<DelimType>;
		using result_type = decltype(std::declval<FuncType>()(std::declval<std::basic_string<char_type>>()));
		static constexpr bool result_is_void = std::is_same<void, result_type>::value;
		const char_type* delim; FuncType f;
	};
	template<typename StlString, typename FuncType>
	struct split_helper_conv_func<StlString, FuncType, false, false, true> {
		using char_type = typename StlString::value_type;
		using result_type = decltype(std::declval<FuncType>()(std::declval<std::basic_string<char_type>>()));
		static constexpr bool result_is_void = std::is_same<void, result_type>::value;
		b_str<char_type> delim; FuncType f;
	};
	template<typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct split_helper;
	template<typename CharType>
	struct split_helper<CharType, true, false, false> {
		using char_type = CharType;
		CharType delim;
		constexpr split_helper_index<CharType, true, false, false> operator[](size_t n) const noexcept { return{ delim, n }; }
		template<typename FuncType>
		constexpr split_helper_conv_func<CharType, FuncType, true, false, false> operator >> (FuncType&& f) const { return{ delim, std::forward<FuncType>(f) }; }
	};
	template<typename CStr>
	struct split_helper<CStr, false, true, false> {
		using char_type = std::remove_pointer_t<CStr>;
		const char_type* delim;
		constexpr split_helper_index<CStr, false, true, false> operator[](size_t n) const noexcept { return{ delim, n }; }
		template<typename FuncType>
		constexpr split_helper_conv_func<CStr, FuncType, false, true, false> operator >> (FuncType&& f) const { return{ delim, std::forward<FuncType>(f) }; }
	};
	template<typename StlString>
	struct split_helper<StlString, false, false, true> {
		using char_type = typename StlString::value_type;
		b_str<char_type> delim;
		constexpr split_helper_index<StlString, false, true, false> operator[](size_t n) const noexcept { return{ std::move(delim), n }; }
		template<typename FuncType>
		constexpr split_helper_conv_func<StlString, FuncType, false, true, false> operator >> (FuncType&& f) const { return{ std::move(delim), std::forward<FuncType>(f) }; }
	};
	//区切り文字1文字, operator[]の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const b_str<CharType>& str, const split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>& info) 
		-> enable_if_t<
			is_single_char && !is_c_str && !is_stl_string && is_same<CharType, typename split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value,
			b_str<CharType>
		>
	{
		size_t pre = 0, pos = 0;
		for (size_t i = 0; i < info.index + 1; ++i) {
			pre = pos;
			pos = str.find_first_of(info.delim, pos) + 1;
		}
		return str.substr(pre, pos - pre - 1);
	}
	//区切り文字複数, operator[]の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const b_str<CharType>& str, const split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			!is_single_char && (is_c_str || is_stl_string) && is_same<CharType, typename split_helper_index<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value,
			b_str<CharType>
		>
	{
		size_t pre = 0, pos = 0;
		for (size_t i = 0; i < info.index + 1; ++i) {
			pre = pos = str.find_first_not_of(str[pos], pos);
			pos = str.find_first_of(info.delim, pos) + 1;
		}
		return str.substr(pre, pos - pre - 1);
	}
	//区切り文字1文字, has chain funcの時
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>
	>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			is_single_char && !is_c_str && !is_stl_string && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && SplitHelperConvFunc::result_is_void,
			void
		>
	{
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != b_str<CharType>::npos; current = found + 1) {
			info.f(std::basic_string<CharType>(str, current, found - current));
		}
		info.f(std::basic_string<CharType>(str, current, str.size() - current));
	}
	//区切り文字1文字, has chain convert funcの時
	template<
		typename CharType, typename DelimType, typename FuncType, 
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string> 
	>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			is_single_char && !is_c_str && !is_stl_string && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && !SplitHelperConvFunc::result_is_void,
			vector<typename SplitHelperConvFunc::result_type>
		>
	{
		vector<typename SplitHelperConvFunc::result_type> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != b_str<CharType>::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.push_back(info.f(std::basic_string<CharType>(str, current, found - current)));
		}
		re.push_back(info.f(std::basic_string<CharType>(str, current, str.size() - current)));
		return re;
	}
	//区切り文字1文字の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const b_str<CharType>& str, const split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			is_single_char && !is_c_str && !is_stl_string && is_same<CharType, typename split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, 
			vector<b_str<CharType>>
		>
	{
		vector<b_str<CharType>> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != b_str<CharType>::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		re.emplace_back(str, current, str.size() - current);
		return re;
	}
	//区切り文字複数, has chain funcの時
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>
	>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			!is_single_char && (is_c_str || is_stl_string) && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && SplitHelperConvFunc::result_is_void,
			void
		>
	{
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != b_str<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
		) {
			info.f(std::basic_string<CharType>(str, current, found - current));
		}
		info.f(std::basic_string<CharType>(str, current, str.size() - current));
	}
	//区切り文字複数, has chain convert funcの時
	template<
		typename CharType, typename DelimType, typename FuncType, 
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>
	>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			!is_single_char && (is_c_str || is_stl_string) && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && !SplitHelperConvFunc::result_is_void,
			vector<typename SplitHelperConvFunc::result_type>
		>
	{
		vector<typename SplitHelperConvFunc::result_type> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != b_str<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.push_back(info.f(std::basic_string<CharType>(str, current, found - current)));
		}
		re.push_back(info.f(std::basic_string<CharType>(str, current, str.size() - current)));
		return re;
	}
	//区切り文字複数の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (const b_str<CharType>& str, const split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			!is_single_char && (is_c_str || is_stl_string) && is_same<CharType, typename split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value, 
			vector<b_str<CharType>>
		>
	{
		vector<b_str<CharType>> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current); 
			current != b_str<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		re.emplace_back(str, current, str.size() - current);
		return re;
	}
	//区切り文字1文字, has chain funcの時
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>
	>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			is_single_char && !is_c_str && !is_stl_string && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && SplitHelperConvFunc::result_is_void,
			void
		>
	{
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != b_str<CharType>::npos; current = found + 1) {
			info.f(std::basic_string<CharType>(str, current, found - current));
		}
		str.erase(0, current);
		info.f(std::move(str));
	}
	//区切り文字1文字, has chain convert funcの時
	template<
		typename CharType, typename DelimType, typename FuncType, 
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string> 
	>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			is_single_char && !is_c_str && !is_stl_string && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && !SplitHelperConvFunc::result_is_void,
			vector<typename SplitHelperConvFunc::result_type>
		>
	{
		vector<typename SplitHelperConvFunc::result_type> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != b_str<CharType>::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.push_back(info.f(std::basic_string<CharType>(str, current, found - current)));
		}
		str.erase(0, current);
		re.push_back(info.f(std::move(str)));
		return re;
	}
	//区切り文字1文字の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (b_str<CharType>&& str, const split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			is_single_char && !is_c_str && !is_stl_string && is_same<CharType, typename split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value,
			vector<b_str<CharType>>
		>
	{
		vector<b_str<CharType>> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != b_str<CharType>::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		str.erase(0, current);
		re.emplace_back(std::move(str));
		return re;
	}
	//区切り文字複数, has chain funcの時
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>
	>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			!is_single_char && (is_c_str || is_stl_string) && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && SplitHelperConvFunc::result_is_void,
			void
		>
	{
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != b_str<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
		) {
			info.f(std::basic_string<CharType>(str, current, found - current));
		}
		str.erase(0, current);
		info.f(std::move(str));
	}
	//区切り文字複数, has chain convert funcの時
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_single_char, bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>
	>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<DelimType, FuncType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			!is_single_char && (is_c_str || is_stl_string) && is_same<CharType, typename SplitHelperConvFunc::char_type>::value && !SplitHelperConvFunc::result_is_void,
			vector<typename SplitHelperConvFunc::result_type>
		>
	{
		vector<typename SplitHelperConvFunc::result_type> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != b_str<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.push_back(info.f(std::basic_string<CharType>(str, current, found - current)));
		}
		str.erase(0, current);
		re.push_back(info.f(std::move(str)));
		return re;
	}
	//区切り文字複数の時
	template<typename CharType, typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	auto operator| (b_str<CharType>&& str, const split_helper<DelimType, is_single_char, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			!is_single_char && (is_c_str || is_stl_string) && is_same<CharType, typename split_helper<DelimType, is_single_char, is_c_str, is_stl_string>::char_type>::value,
			vector<b_str<CharType>>
		>
	{
		vector<b_str<CharType>> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			found != b_str<CharType>::npos;
			current = str.find_first_not_of(str[found], found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		str.erase(0, current);
		re.emplace_back(std::move(str));
		return re;
	}
}
template<typename CharType, std::enable_if_t<detail::type_traits::is_char_type<CharType>::value, std::nullptr_t> = nullptr>
detail::split_helper<CharType, true, false, false> split(CharType delim) noexcept { return{ delim }; }
template<typename CStr, std::enable_if_t<detail::type_traits::is_c_str<CStr>::value, std::nullptr_t> = nullptr>
detail::split_helper<CStr, false, true, false> split(CStr delim) noexcept { return{ delim }; }
template<typename StlString, std::enable_if_t<detail::type_traits::is_stl_string<StlString>::value, std::nullptr_t> = nullptr>
detail::split_helper<StlString, false, false, true> split(StlString delim) noexcept { return{ std::move(delim) }; }
