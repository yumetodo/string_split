/*=============================================================================
  Copyright (C) 2016-2018 yumetodo

  Distributed under the Boost Software License, Version 1.0.
  (See http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#pragma once
#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <limits>
#include <stdexcept>
#if defined(_MSC_VER)
#	if _MSC_VER >= 1910 && _MSVC_LANG >= 201703
#		define STRING_SPLIT_HAS_CXX17_STRING_VIEW 1
#	endif
#elif defined(__clang__)
#	if __clang_major__ >= 4 && __cplusplus >= 201703
#		define STRING_SPLIT_HAS_CXX17_STRING_VIEW 1
#	endif
#elif defined(__GNUC__)
#	if (__GNUC__ > 7 || (__GNUC__ == 7 && __GNUC_MINOR__ >= 1)) && __cplusplus >= 201703
#		define STRING_SPLIT_HAS_CXX17_STRING_VIEW 1
#	endif
#endif

#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
#	include <string_view>
#endif

//Windows.hなどからくる min max マクロがdefineされるのを防ぐ

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
namespace detail {
	using std::vector;
	template<typename CharType> using b_str = std::basic_string<CharType>;
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<typename CharType> using b_str_view = std::basic_string_view<CharType>;
#endif
	using std::is_same;
	using std::size_t;
	using std::is_void;
	template<bool con, typename T>
	using enable_if_t = typename std::enable_if<con, T>::type;
	template<bool con, typename T1, typename T2>
	using conditional_t = typename std::conditional<con, T1, T2>::type;
	template<typename T>
	using remove_pointer_t = typename std::remove_pointer<T>::type;
	template<typename T>
	using remove_reference_t = typename std::remove_reference<T>::type;
	template<typename T>
	using remove_cv_t = typename std::remove_cv<T>::type;
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
		struct is_c_str : std::integral_constant<bool, std::is_pointer<T>::value && is_char_type<remove_pointer_t<T>>::value> {};
		//
		// is_stl_string
		//
		template<typename T>
		struct is_stl_string : conditional_t<std::is_reference<T>::value, is_stl_string<remove_reference_t<T>>, std::false_type> {};
		template<typename T> struct is_stl_string<T const> : is_stl_string<T> {};
		template<typename T> struct is_stl_string<T volatile> : is_stl_string<T> {};
		template<typename T> struct is_stl_string<T const volatile> : is_stl_string<T> {};
		template<typename CharType>
		struct is_stl_string<b_str<CharType>> : std::integral_constant<bool, is_char_type<remove_cv_t<CharType>>::value> {};

		namespace detail {
			template <class T>
			struct is_reference_wrapper : std::false_type {};
			template <class U>
			struct is_reference_wrapper<std::reference_wrapper<U>> : std::true_type {};

			template<class T>
			struct invoke_impl {
				template<class F, class... Args>
				static auto call(F&& f, Args&&... args)
					-> decltype(std::forward<F>(f)(std::forward<Args>(args)...));
			};

			template<class B, class MT>
			struct invoke_impl<MT B::*> {
				template<class T, class Td = typename std::decay<T>::type,
					class = typename std::enable_if<std::is_base_of<B, Td>::value>::type
				>
					static auto get(T&& t)->T&&;

				template<class T, class Td = typename std::decay<T>::type,
					class = typename std::enable_if<is_reference_wrapper<Td>::value>::type
				>
					static auto get(T&& t) -> decltype(t.get());

				template<class T, class Td = typename std::decay<T>::type,
					class = typename std::enable_if<!std::is_base_of<B, Td>::value>::type,
					class = typename std::enable_if<!is_reference_wrapper<Td>::value>::type
				>
					static auto get(T&& t) -> decltype(*std::forward<T>(t));

				template<class T, class... Args, class MT1,
					class = typename std::enable_if<std::is_function<MT1>::value>::type
				>
					static auto call(MT1 B::*pmf, T&& t, Args&&... args)
					-> decltype((invoke_impl::get(std::forward<T>(t)).*pmf)(std::forward<Args>(args)...));

				template<class T>
				static auto call(MT B::*pmd, T&& t)
					-> decltype(invoke_impl::get(std::forward<T>(t)).*pmd);
			};

			template<class F, class... Args, class Fd = typename std::decay<F>::type>
			auto INVOKE(F&& f, Args&&... args)
				-> decltype(invoke_impl<Fd>::call(std::forward<F>(f), std::forward<Args>(args)...));

		} // namespace detail

		// Conforming C++14 implementation (is also a valid C++11 implementation):
		namespace detail {
			template <typename AlwaysVoid, typename, typename...>
			struct invoke_result { };
			template <typename F, typename...Args>
			struct invoke_result<decltype(void(detail::INVOKE(std::declval<F>(), std::declval<Args>()...))),
				F, Args...> {
				using type = decltype(detail::INVOKE(std::declval<F>(), std::declval<Args>()...));
			};
		} // namespace detail

		template <class F, class... ArgTypes>
		struct invoke_result : detail::invoke_result<void, F, ArgTypes...> {};
		template< class F, class... ArgTypes>
		using invoke_result_t = typename invoke_result<F, ArgTypes...>::type;

		template<class...> struct conjunction : std::true_type { };
		template<class B1> struct conjunction<B1> : B1 { };
		template<class B1, class... Bn>
		struct conjunction<B1, Bn...>
			: conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};

		template<class...> struct disjunction : std::false_type { };
		template<class B1> struct disjunction<B1> : B1 { };
		template<class B1, class... Bn>
		struct disjunction<B1, Bn...>
			: conditional_t<bool(B1::value), B1, disjunction<Bn...>> { };

		template <bool B>
		using bool_constant = std::integral_constant<bool, B>;

		template<class B>
		struct negation : bool_constant<!bool(B::value)> { };
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
		//
		// is_stl_string_view
		//
		template<typename T>
		struct is_stl_string_view : conditional_t<std::is_reference<T>::value, is_stl_string_view<remove_reference_t<T>>, std::false_type> {};
		template<typename T> struct is_stl_string_view<T const> : is_stl_string_view<T> {};
		template<typename T> struct is_stl_string_view<T volatile> : is_stl_string_view<T> {};
		template<typename T> struct is_stl_string_view<T const volatile> : is_stl_string_view<T> {};
		template<typename CharType>
		struct is_stl_string_view<b_str_view<CharType>> : std::integral_constant<bool, is_char_type<remove_cv_t<CharType>>::value> {};
		template<typename T> constexpr bool is_stl_string_view_v = is_stl_string_view<T>::value;
		//
		// is_stl_string_or_stl_string_view
		//
		template<typename T> struct is_stl_string_or_stl_string_view : std::disjunction<
			type_traits::is_stl_string<T>,
			type_traits::is_stl_string_view<T>
		> {};
		//
		// contract_str_type
		//
		template<typename StrType, typename CharType> struct contract_str_type : std::conjunction<
			type_traits::is_stl_string_or_stl_string_view<StrType>,
			is_same<CharType, typename StrType::value_type>
		> {};
		template<typename StrType, typename CharType> constexpr bool contract_str_type_v = contract_str_type<StrType, CharType>::value;
#endif
	}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	using std::conjunction_v;
#endif
	using type_traits::invoke_result_t;
	struct subroutine_base {};
	template<typename T> struct is_subroutine : std::is_base_of<subroutine_base, T> {};
	struct get_front : subroutine_base {};
	struct get_back : subroutine_base {};
	struct split_at_first_back : subroutine_base {};
	struct split_at_first : subroutine_base {
		constexpr get_front front() const { return{}; }
		constexpr split_at_first_back back() const { return{}; }
	};
	struct split_at_last_front : subroutine_base {};
	struct split_at_last : subroutine_base {
		constexpr split_at_last_front front() const { return{}; }
		constexpr get_back back() const { return{}; }
	};
	template<typename Subroutine, typename DelimType, typename CharType>
	struct split_helper_subroutine {
		using char_type = CharType;
		DelimType delim;
	};
	template<typename DelimType, typename CharType>
	struct split_helper_get_back {
		using char_type = CharType;
		DelimType delim;
	};
	template<typename DelimType, typename CharType>
	struct split_helper_split_at_first_back {
		using char_type = CharType;
		DelimType delim;
	};
	template<typename DelimType, typename CharType>
	struct split_helper_split_at_first {
		using char_type = CharType;
		DelimType delim;
	};
	template<typename DelimType, typename CharType>
	struct split_helper_split_at_last_front {
		using char_type = CharType;
		DelimType delim;
	};
	template<typename DelimType, typename CharType>
	struct split_helper_split_at_last {
		using char_type = CharType;
		DelimType delim;
	};
	template<typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct split_helper_index;
	template<typename CharType>
	struct split_helper_index<CharType, true, false, false> {
		using char_type = CharType;
		CharType delim; size_t index;
	};
	template<typename CharType>
	struct split_helper_get_front : split_helper_index<CharType, true, false, false> {
		constexpr split_helper_get_front(CharType d) : split_helper_index<CharType, true, false, false>({d, 0}) {}
	};
	template<typename CStr>
	struct split_helper_index<CStr, false, true, false> {
		using char_type = remove_cv_t<remove_pointer_t<CStr>>;
		const char_type* delim; size_t index;
	};
	template<typename StlString>
	struct split_helper_index<StlString, false, false, true> {
		using char_type = typename StlString::value_type;
		b_str<char_type> delim; size_t index;
	};
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<typename StlStringView>
	struct split_helper_index<StlStringView, false, false, false> {
		using char_type = typename StlStringView::value_type;
		b_str_view<char_type> delim; size_t index;
	};
#endif
	template<typename DelimType, typename FuncType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct split_helper_conv_func;
	template<typename CharType, typename FuncType>
	struct split_helper_conv_func<CharType, FuncType, true, false, false> {
		using char_type = CharType;
		CharType delim; FuncType f;
	};
	template<typename CStr, typename FuncType>
	struct split_helper_conv_func<CStr, FuncType, false, true, false> {
		using char_type = remove_cv_t<remove_pointer_t<CStr>>;
		const char_type* delim; FuncType f;
	};
	template<typename StlString, typename FuncType>
	struct split_helper_conv_func<StlString, FuncType, false, false, true> {
		using char_type = typename StlString::value_type;
		b_str<char_type> delim; FuncType f;
	};
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<typename StlStringView, typename FuncType>
	struct split_helper_conv_func<StlStringView, FuncType, false, false, false> {
		using char_type = typename StlStringView::value_type;
		b_str_view<char_type> delim; FuncType f;
	};
#endif
	template<typename DelimType, bool is_single_char, bool is_c_str, bool is_stl_string>
	struct split_helper;
	template<typename CharType>
	struct split_helper<CharType, true, false, false> {
		using char_type = CharType;
		CharType delim;
		constexpr split_helper_index<CharType, true, false, false> operator[](size_t n) const noexcept { return{ delim, n }; }
		template<typename FuncType, enable_if_t<!is_subroutine<FuncType>::value, std::nullptr_t> = nullptr>
		constexpr split_helper_conv_func<CharType, FuncType, true, false, false> operator>> (FuncType&& f) const { return{ delim, std::forward<FuncType>(f) }; }
		constexpr split_helper_get_front<CharType> operator>>(get_front) const noexcept { return{ delim }; }
		template<typename Subroutine, enable_if_t<is_subroutine<Subroutine>::value, std::nullptr_t> = nullptr>
		constexpr split_helper_subroutine<Subroutine, CharType, CharType> operator>> (Subroutine) const noexcept { return{ delim }; }
	};
	template<typename CStr>
	struct split_helper<CStr, false, true, false> {
		using char_type = remove_cv_t<remove_pointer_t<CStr>>;
		const char_type* delim;
		constexpr split_helper_index<CStr, false, true, false> operator[](size_t n) const noexcept { return{ delim, n }; }
		template<typename FuncType, enable_if_t<!is_subroutine<FuncType>::value, std::nullptr_t> = nullptr>
		constexpr split_helper_conv_func<CStr, FuncType, false, true, false> operator >> (FuncType&& f) const { return{ delim, std::forward<FuncType>(f) }; }
		constexpr split_helper_index<CStr, false, true, false> operator>>(get_front) const noexcept { return{ delim, 0 }; }
		template<typename Subroutine, enable_if_t<is_subroutine<Subroutine>::value, std::nullptr_t> = nullptr>
		constexpr split_helper_subroutine<Subroutine, CStr, char_type> operator>> (Subroutine) const noexcept { return{ delim }; }
	};
	template<typename StlString>
	struct split_helper<StlString, false, false, true> {
		using char_type = typename StlString::value_type;
		b_str<char_type> delim;
		split_helper_index<StlString, false, false, true> operator[](size_t n) const noexcept { return{ std::move(delim), n }; }
		template<typename FuncType, enable_if_t<!is_subroutine<FuncType>::value, std::nullptr_t> = nullptr>
		split_helper_conv_func<StlString, FuncType, false, false, true> operator >> (FuncType&& f) const { return{ std::move(delim), std::forward<FuncType>(f) }; }
		split_helper_index<StlString, false, false, true> operator>>(get_front) const noexcept { return{ std::move(delim), 0 }; }
		template<typename Subroutine, enable_if_t<is_subroutine<Subroutine>::value, std::nullptr_t> = nullptr>
		split_helper_subroutine<Subroutine, StlString, char_type> operator>> (Subroutine) const noexcept { return{ std::move(delim) }; }
	};
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<typename StlStringView>
	struct split_helper<StlStringView, false, false, false> {
		using char_type = typename StlStringView::value_type;
		b_str_view<char_type> delim;
		split_helper_index<StlStringView, false, false, false> operator[](size_t n) const noexcept { return{ std::move(delim), n }; }
		template<typename FuncType, enable_if_t<!is_subroutine<FuncType>::value, std::nullptr_t> = nullptr>
		split_helper_conv_func<StlStringView, FuncType, false, false, false> operator >> (FuncType&& f) const { return{ std::move(delim), std::forward<FuncType>(f) }; }
		split_helper_index<StlStringView, false, false, false> operator>>(get_front) const noexcept { return{ std::move(delim), 0 }; }
		template<typename Subroutine, enable_if_t<is_subroutine<Subroutine>::value, std::nullptr_t> = nullptr>
		split_helper_subroutine<Subroutine, StlStringView, char_type> operator>> (Subroutine) const noexcept { return{ std::move(delim) }; }
	};
	namespace type_traits {
		//
		//contract_str_type_and_delim_type_without_single_char
		//
		//is_c_str: true  && is_stl_string: true => impossible!!!
		//is_c_str: true  && is_stl_string: false => const T*
		//is_c_str: false && is_stl_string: true  => std::basic_string
		//is_c_str: false && is_stl_string: false => std::basic_string_view
		template<typename StrType, typename DelimType, bool is_c_str, bool is_stl_string>
		struct contract_str_type_and_delim_type_without_single_char : conjunction<
			contract_str_type<StrType, typename split_helper<DelimType, false, is_c_str, is_stl_string>::char_type>,
			bool_constant<!(is_c_str && is_stl_string)>
		>
		{};
		template<typename StrType, typename DelimType, bool is_c_str, bool is_stl_string>
		constexpr bool contract_str_type_and_delim_type_without_single_char_v = contract_str_type_and_delim_type_without_single_char<StrType, DelimType, is_c_str, is_stl_string>::value;
	}
#endif
	namespace type_traits {
		template<typename CharType, typename DelimType, bool is_c_str, bool is_stl_string>
		struct contract_delim_type_without_single_char : conjunction<
			is_same<CharType, typename split_helper<DelimType, false, is_c_str, is_stl_string>::char_type>,
			bool_constant<(is_c_str || is_stl_string)>
		>
		{};
	}
	//back()の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, typename CharType,
		enable_if_t<type_traits::contract_str_type_v<StrType, CharType>, std::nullptr_t> = nullptr
	>
	StrType operator| (const StrType& str, const split_helper_subroutine<get_back, DelimType, CharType>& info) noexcept(type_traits::is_stl_string_view_v<StrType>)
	{
#else
	template<typename CharType, typename DelimType>
	b_str<CharType> operator| (const b_str<CharType>& str, const split_helper_subroutine<get_back, DelimType, CharType>& info)
	{
		using StrType = b_str<CharType>;
#endif
		const auto pos = str.find_first_of(info.delim);
		return (StrType::npos == pos) ? str : str.substr(str.find_last_of(info.delim) + 1);
	}
	//at_first().back()の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, typename CharType,
		enable_if_t<type_traits::contract_str_type_v<StrType, CharType>, std::nullptr_t> = nullptr
	>
	StrType operator| (const StrType& str, const split_helper_subroutine<split_at_first_back, DelimType, CharType>& info) noexcept(type_traits::is_stl_string_view_v<StrType>)
	{
#else
	template<typename CharType, typename DelimType>
	b_str<CharType> operator| (const b_str<CharType>& str, const split_helper_subroutine<split_at_first_back, DelimType, CharType>& info)
	{
		using StrType = b_str<CharType>;
#endif
		const auto pos = str.find_first_of(info.delim);
		if (StrType::npos == pos) return {};
		return str.substr(str.find_first_not_of(info.delim, pos));
	}
	//at_first()の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, typename CharType,
		enable_if_t<type_traits::contract_str_type_v<StrType, CharType>, std::nullptr_t> = nullptr
	>
	std::array<StrType, 2> operator| (const StrType& str, const split_helper_subroutine<split_at_first, DelimType, CharType>& info) noexcept(type_traits::is_stl_string_view_v<StrType>)
	{
#else
	template<typename CharType, typename DelimType>
	std::array<b_str<CharType>, 2> operator| (const b_str<CharType>& str, const split_helper_subroutine<split_at_first, DelimType, CharType>& info)
	{
		using StrType = b_str<CharType>;
#endif
		const auto pos = str.find_first_of(info.delim);
		if (StrType::npos == pos) return{ { str, {} } };
		return{ {str.substr(0, pos), str.substr(str.find_first_not_of(info.delim, pos))} };
	}
	//at_last().front()の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, typename CharType,
		enable_if_t<type_traits::contract_str_type_v<StrType, CharType>, std::nullptr_t> = nullptr
	>
	StrType operator| (const StrType& str, const split_helper_subroutine<split_at_last_front, DelimType, CharType>& info) noexcept(type_traits::is_stl_string_view_v<StrType>)
	{
#else
	template<typename CharType, typename DelimType>
	b_str<CharType> operator| (const b_str<CharType>& str, const split_helper_subroutine<split_at_last_front, DelimType, CharType>& info)
	{
		using StrType = b_str<CharType>;
#endif
		const auto pos = str.find_last_of(info.delim);
		if (StrType::npos == pos) return {};
		return str.substr(0, str.find_last_not_of(info.delim, pos) + 1);
	}
	//at_last()の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, typename CharType,
		enable_if_t<type_traits::contract_str_type_v<StrType, CharType>, std::nullptr_t> = nullptr
	>
	std::array<StrType, 2> operator| (const StrType& str, const split_helper_subroutine<split_at_last, DelimType, CharType>& info) noexcept(type_traits::is_stl_string_view_v<StrType>)
	{
#else
	template<typename CharType, typename DelimType>
	std::array<b_str<CharType>, 2> operator| (const b_str<CharType>& str, const split_helper_subroutine<split_at_last, DelimType, CharType>& info)
	{
		using StrType = b_str<CharType>;
#endif
		const auto pos = str.find_last_of(info.delim);
		if (StrType::npos == pos) return{ { {}, str } };
		return { { str.substr(0, str.find_last_not_of(info.delim, pos) + 1), str.substr(pos + 1) } };
	}
	//区切り文字1文字, operator[] or front()の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename CharType,
		enable_if_t<type_traits::contract_str_type_v<StrType, CharType>, std::nullptr_t> = nullptr
	>
	StrType operator| (const StrType& str, const split_helper_index<CharType, true, false, false>& info)
	{
#else
	template<typename CharType>
	b_str<CharType> operator| (const b_str<CharType>& str, const split_helper_index<CharType, true, false, false>& info)
	{
		using StrType = b_str<CharType>;
#endif
		size_t pre = 0, pos = 0, i;
		for (i = 0; i < info.index + 1; ++i) {
			pre = pos;
			pos = str.find_first_of(info.delim, pos);
			if (StrType::npos == pos) break;
			++pos;
		}
		if(i < info.index) throw std::out_of_range("index(" + std::to_string(info.index) + ") is too big.");
		return str.substr(pre, pos - pre - 1);
	}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	//区切り文字1文字, front()の時
	template<typename CharType>
	b_str_view<CharType> operator| (const b_str_view<CharType>& str, const split_helper_get_front<CharType>& info) noexcept
	{
		return str.substr(0, str.find_first_of(info.delim));
	}
#endif
	//区切り文字複数, operator[] or front()の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, bool is_c_str, bool is_stl_string,
		enable_if_t<type_traits::contract_str_type_and_delim_type_without_single_char_v<StrType, DelimType, is_c_str, is_stl_string>, std::nullptr_t> = nullptr
	>
	auto operator| (const StrType& str, const split_helper_index<DelimType, false, is_c_str, is_stl_string>& info) -> StrType
	{
#else
	template<typename CharType, typename DelimType, bool is_c_str, bool is_stl_string>
	auto operator| (const b_str<CharType>& str, const split_helper_index<DelimType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>::value,
			b_str<CharType>
		>
	{
		using StrType = b_str<CharType>;
#endif
		size_t pre = 0, pos = 0, i;
		for (i = 0; i < info.index + 1; ++i) {
			if(pos) pre = pos = str.find_first_not_of(info.delim, pos);
			pos = str.find_first_of(info.delim, pos);
			if (StrType::npos == pos) break;
		}
		if (i < info.index) throw std::out_of_range("index(" + std::to_string(info.index) + ") is too big.");
		return str.substr(pre, pos - pre);
	}
	//区切り文字1文字, has chain funcの時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename CharType, typename FuncType,
		enable_if_t<conjunction_v<
			type_traits::contract_str_type<StrType, CharType>,
			is_void<invoke_result_t<FuncType, StrType>>
		>, std::nullptr_t> = nullptr
	>
	void operator| (const StrType& str, const split_helper_conv_func<CharType, FuncType, true, false, false>& info)
	{
#else
	template<typename CharType, typename FuncType>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<CharType, FuncType, true, false, false>& info)
		-> enable_if_t<
			is_void<invoke_result_t<FuncType, b_str<CharType>>>::value,
			void
		>
	{
		using StrType = b_str<CharType>;
#endif
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != StrType::npos; current = found + 1) {
			info.f(str.substr(current, found - current));
		}
		info.f(str.substr(current, str.size() - current));
	}
	//区切り文字1文字, has chain convert funcの時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename CharType, typename FuncType,
		enable_if_t<conjunction_v<
			type_traits::contract_str_type<StrType, CharType>,
			type_traits::negation<is_void<invoke_result_t<FuncType, StrType>>>
		>, std::nullptr_t> = nullptr
	>
	auto operator| (const StrType& str, const split_helper_conv_func<CharType, FuncType, true, false, false>& info)
		-> vector<invoke_result_t<FuncType, StrType>>
	{
#else
	template<typename CharType, typename FuncType>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<CharType, FuncType, true, false, false>& info)
		-> enable_if_t<
			!is_void<invoke_result_t<FuncType, b_str<CharType>>>::value,
			vector<invoke_result_t<FuncType, b_str<CharType>>>
		>
	{
		using StrType = b_str<CharType>;
#endif
		vector<invoke_result_t<FuncType, StrType>> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != StrType::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.emplace_back(info.f(str.substr(current, found - current)));
		}
		re.emplace_back(info.f(str.substr(current, str.size() - current)));
		return re;
	}
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<typename CharType>
	void vector_emplace_make_substr(vector<b_str_view<CharType>>& re, const b_str_view<CharType>& str, size_t pos, size_t n)
	{
		re.emplace_back(str.substr(pos, n));
	}
#endif
	template<typename CharType>
	void vector_emplace_make_substr(vector<b_str<CharType>>& re, const b_str<CharType>& str, size_t pos, size_t n)
	{
		re.emplace_back(str, pos, n);
	}
	//区切り文字1文字の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename CharType,
		enable_if_t<type_traits::contract_str_type_v<StrType, CharType>, std::nullptr_t> = nullptr
	>
	vector<StrType> operator| (const StrType& str, const split_helper<CharType, true, false, false>& info)
	{
#else
	template<typename CharType>
	vector<b_str<CharType>> operator| (const b_str<CharType>& str, const split_helper<CharType, true, false, false>& info)
	{
		using StrType = b_str<CharType>;
#endif
		vector<StrType> re;
		size_t current = 0;
		for (size_t found; (found = str.find_first_of(info.delim, current)) != StrType::npos; current = found + 1) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			vector_emplace_make_substr(re, str, current, found - current);
		}
		vector_emplace_make_substr(re, str, current, str.size() - current);
		return re;
	}
	//区切り文字複数, has chain funcの時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, typename FuncType,
		bool is_c_str, bool is_stl_string,
		enable_if_t<conjunction_v<
			type_traits::contract_str_type_and_delim_type_without_single_char<StrType, DelimType, is_c_str, is_stl_string>,
			is_void<invoke_result_t<FuncType, StrType>>
		>, std::nullptr_t> = nullptr
	>
	void operator| (const StrType& str, const split_helper_conv_func<DelimType, FuncType, false, is_c_str, is_stl_string>& info)
	{
#else
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_c_str, bool is_stl_string
	>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<DelimType, FuncType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			type_traits::conjunction<
				type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>,
				is_void<invoke_result_t<FuncType, b_str<CharType>>>
			>::value,
			void
		>
	{
		using StrType = b_str<CharType>;
#endif
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != StrType::npos && found != StrType::npos;
			current = str.find_first_not_of(info.delim, found + 1), found = str.find_first_of(info.delim, current)
		) {
			info.f(str.substr(current, found - current));
		}
		info.f(str.substr(current, str.size() - current));
	}
	//区切り文字複数, has chain convert funcの時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, typename FuncType,
		bool is_c_str, bool is_stl_string,
		enable_if_t<conjunction_v<
			type_traits::contract_str_type_and_delim_type_without_single_char<StrType, DelimType, is_c_str, is_stl_string>,
			type_traits::negation<is_void<invoke_result_t<FuncType, StrType>>>
		>, std::nullptr_t> = nullptr
	>
	auto operator| (const StrType& str, const split_helper_conv_func<DelimType, FuncType, false, is_c_str, is_stl_string>& info)
		-> vector<invoke_result_t<FuncType, StrType>>
	{
#else
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_c_str, bool is_stl_string
	>
	auto operator| (const b_str<CharType>& str, const split_helper_conv_func<DelimType, FuncType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			type_traits::conjunction<
				type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>,
				type_traits::negation<is_void<invoke_result_t<FuncType, b_str<CharType>>>>
			>::value,
			vector<invoke_result_t<FuncType, b_str<CharType>>>
		>
	{
		using StrType = b_str<CharType>;
#endif
		vector<invoke_result_t<FuncType, StrType>> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != StrType::npos && found != StrType::npos;
			current = str.find_first_not_of(info.delim, found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.emplace_back(info.f(str.substr(current, found - current)));
		}
		re.emplace_back(info.f(str.substr(current, str.size() - current)));
		return re;
	}
	//区切り文字複数の時
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
	template<
		typename StrType, typename DelimType, bool is_c_str, bool is_stl_string,
		enable_if_t<type_traits::contract_str_type_and_delim_type_without_single_char_v<StrType, DelimType, is_c_str, is_stl_string>, std::nullptr_t> = nullptr
	>
	auto operator| (const StrType& str, const split_helper<DelimType, false, is_c_str, is_stl_string>& info) -> vector<StrType>
	{
#else
	template<typename CharType, typename DelimType, bool is_c_str, bool is_stl_string>
	auto operator| (const b_str<CharType>& str, const split_helper<DelimType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>::value,
			vector<b_str<CharType>>
		>
	{
		using StrType = b_str<CharType>;
#endif
		vector<StrType> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != StrType::npos && found != StrType::npos;
			current = str.find_first_not_of(info.delim, found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			vector_emplace_make_substr(re, str, current, found - current);
		}
		vector_emplace_make_substr(re, str, current, str.size() - current);
		return re;
	}
	//back()の時
	template<typename CharType, typename DelimType>
	b_str<CharType> operator| (b_str<CharType>&& str, const split_helper_subroutine<get_back, DelimType, CharType>& info)
	{
		const auto pos = str.find_first_of(info.delim);
		if (b_str<CharType>::npos != pos) str.erase(0, str.find_last_of(info.delim) + 1);
		return std::move(str);
	}
	//at_first().back()の時
	template<typename CharType, typename DelimType>
	b_str<CharType> operator| (b_str<CharType>&& str, const split_helper_subroutine<split_at_first_back, DelimType, CharType>& info)
	{
		const std::size_t pos = str.find_first_of(info.delim);
		if (b_str<CharType>::npos == pos) return {};
		str.erase(0, str.find_first_not_of(info.delim, pos));
		return std::move(str);
	}
	//at_first()の時
	template<typename CharType, typename DelimType>
	std::array<b_str<CharType>, 2> operator| (b_str<CharType>&& str, const split_helper_subroutine<split_at_first, DelimType, CharType>& info)
	{
		const std::size_t pos = str.find_first_of(info.delim);
		if (b_str<CharType>::npos == pos) return{ { std::move(str),{} } };
		std::array<b_str<CharType>, 2> re;
		re[1] = str.substr(str.find_first_not_of(info.delim, pos));
		str.erase(pos);
		re[0] = std::move(str);
		return re;
	}
	//at_last().front()の時
	template<typename CharType, typename DelimType>
	b_str<CharType> operator| (b_str<CharType>&& str, const split_helper_subroutine<split_at_last_front, DelimType, CharType>& info)
	{
		const std::size_t pos = str.find_last_of(info.delim);
		if (b_str<CharType>::npos == pos) return {};
		str.erase(str.find_last_not_of(info.delim, pos) + 1);
		return std::move(str);
	}
	//at_last()の時
	template<typename CharType, typename DelimType>
	std::array<b_str<CharType>, 2> operator| (b_str<CharType>&& str, const split_helper_subroutine<split_at_last, DelimType, CharType>& info)
	{
		const std::size_t pos = str.find_last_of(info.delim);
		if (b_str<CharType>::npos == pos) return{ { {}, std::move(str) } };
		std::array<b_str<CharType>, 2> re;
		re[1] = str.substr(pos + 1);
		str.erase(str.find_last_not_of(info.delim, pos) + 1);
		re[0] = std::move(str);
		return re;
	}
	//区切り文字1文字, operator[]の時
	template<typename CharType>
	b_str<CharType> operator| (b_str<CharType>&& str, const split_helper_index<CharType, true, false, false>& info)
	{
		size_t pre = 0, pos = 0, i;
		for (i = 0; i < info.index + 1; ++i) {
			pre = pos;
			pos = str.find_first_of(info.delim, pos);
			if (b_str<CharType>::npos == pos) break;
			++pos;
		}
		if (i < info.index) throw std::out_of_range("index(" + std::to_string(info.index) + ") is too big.");
		--pos;
		if(pos <= str.size()) str.erase(pos);
		str.erase(0, pre);
		return std::move(str);
	}
	//区切り文字複数, operator[]の時
	template<typename CharType, typename DelimType, bool is_c_str, bool is_stl_string>
	auto operator| (b_str<CharType>&& str, const split_helper_index<DelimType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
		type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>::value,
		b_str<CharType>
		>
	{
		size_t pre = 0, pos = 0, i;
		for (i = 0; i < info.index + 1; ++i) {
			if (pos) pre = pos = str.find_first_not_of(info.delim, pos);
			pos = str.find_first_of(info.delim, pos);
			if (b_str<CharType>::npos == pos) break;
		}
		if (i < info.index) throw std::out_of_range("index(" + std::to_string(info.index) + ") is too big.");
		if (pos <= str.size()) str.erase(pos);
		str.erase(0, pre);
		return std::move(str);
	}
	//区切り文字1文字, has chain funcの時
	template<typename CharType, typename FuncType>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<CharType, FuncType, true, false, false>& info)
		-> enable_if_t<
			is_void<invoke_result_t<FuncType, b_str<CharType>>>::value,
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
		typename CharType, typename FuncType,
		typename SplitHelperConvFunc = split_helper_conv_func<CharType, FuncType, true, false, false>
	>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<CharType, FuncType, true, false, false>& info)
		-> enable_if_t<
			!is_void<invoke_result_t<FuncType, b_str<CharType>>>::value,
			vector<invoke_result_t<FuncType, b_str<CharType>>>
		>
	{
		vector<invoke_result_t<FuncType, b_str<CharType>>> re;
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
	template<typename CharType>
	vector<b_str<CharType>> operator| (b_str<CharType>&& str, const split_helper<CharType, true, false, false>& info)
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
		bool is_c_str, bool is_stl_string
	>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<DelimType, FuncType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			type_traits::conjunction<
				type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>,
				is_void<invoke_result_t<FuncType, b_str<CharType>>>
			>::value,
			void
		>
	{
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != b_str<CharType>::npos && found != b_str<CharType>::npos;
			current = str.find_first_not_of(info.delim, found + 1), found = str.find_first_of(info.delim, current)
		) {
			info.f(std::basic_string<CharType>(str, current, found - current));
		}
		str.erase(0, current);
		info.f(std::move(str));
	}
	//区切り文字複数, has chain convert funcの時
	template<
		typename CharType, typename DelimType, typename FuncType,
		bool is_c_str, bool is_stl_string,
		typename SplitHelperConvFunc = split_helper_conv_func<DelimType, FuncType, false, is_c_str, is_stl_string>
	>
	auto operator| (b_str<CharType>&& str, const split_helper_conv_func<DelimType, FuncType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			type_traits::conjunction<
				type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>,
				type_traits::negation<is_void<invoke_result_t<FuncType, b_str<CharType>>>>
			>::value,
			vector<invoke_result_t<FuncType, b_str<CharType>>>
		>
	{
		vector<invoke_result_t<FuncType, b_str<CharType>>> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != b_str<CharType>::npos && found != b_str<CharType>::npos;
			current = str.find_first_not_of(info.delim, found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.push_back(info.f(std::basic_string<CharType>(str, current, found - current)));
		}
		str.erase(0, current);
		re.push_back(info.f(std::move(str)));
		return re;
	}
	//区切り文字複数の時
	template<typename CharType, typename DelimType, bool is_c_str, bool is_stl_string>
	auto operator| (b_str<CharType>&& str, const split_helper<DelimType, false, is_c_str, is_stl_string>& info)
		-> enable_if_t<
			type_traits::contract_delim_type_without_single_char<CharType, DelimType, is_c_str, is_stl_string>::value,
			vector<b_str<CharType>>
		>
	{
		vector<b_str<CharType>> re;
		size_t current = 0;
		for (
			size_t found = str.find_first_of(info.delim, current);
			current != b_str<CharType>::npos && found != b_str<CharType>::npos;
			current = str.find_first_not_of(info.delim, found + 1), found = str.find_first_of(info.delim, current)
		) {
			if (re.capacity() < re.size() + 1) re.reserve((std::numeric_limits<size_t>::max() / 2 < re.size()) ? std::numeric_limits<size_t>::max() : re.size() * 2);
			re.emplace_back(str, current, found - current);
		}
		str.erase(0, current);
		re.emplace_back(std::move(str));
		return re;
	}
}
template<typename CharType, typename std::enable_if<detail::type_traits::is_char_type<CharType>::value, std::nullptr_t>::type = nullptr>
constexpr detail::split_helper<CharType, true, false, false> split(CharType delim) noexcept { return{ delim }; }
template<typename CStr, typename std::enable_if<detail::type_traits::is_c_str<CStr>::value, std::nullptr_t>::type = nullptr>
constexpr detail::split_helper<CStr, false, true, false> split(CStr delim) noexcept { return{ delim }; }
template<typename StlString, typename std::enable_if<detail::type_traits::is_stl_string<StlString>::value, std::nullptr_t>::type = nullptr>
detail::split_helper<StlString, false, false, true> split(StlString delim) noexcept { return{ std::move(delim) }; }
#ifdef STRING_SPLIT_HAS_CXX17_STRING_VIEW
template<typename StlStringView, typename std::enable_if<detail::type_traits::is_stl_string_view<StlStringView>::value, std::nullptr_t>::type = nullptr>
detail::split_helper<StlStringView, false, false, false> split(StlStringView delim) noexcept { return{ delim }; }
#endif
constexpr detail::get_front front() noexcept { return{}; }
constexpr detail::get_back back() noexcept { return{}; }
constexpr detail::split_at_first at_first() noexcept { return{}; }
constexpr detail::split_at_last at_last() noexcept { return{}; }
