/*=============================================================================
Copyright (C) 2015-2016 yumetodo

Distributed under the Boost Software License, Version 1.0.
(See http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#pragma once
#include <cstddef>
#include <type_traits>
#include <iterator>
#if 201500 <= __cplusplus || (defined(_MSVC_LANG) && 201500 <= _MSVC_LANG)
#	define CRL_CXX17_STD_ITERATPR_DEPRECATED
#endif
template<typename T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
class counter_iterator
#ifndef CRL_CXX17_STD_ITERATPR_DEPRECATED
	: std::iterator<std::random_access_iterator_tag, T>
#endif
{
private:
	T i;
#ifndef CRL_CXX17_STD_ITERATPR_DEPRECATED
	typedef std::iterator<std::random_access_iterator_tag, T> my_t;
public:
	typedef typename my_t::iterator_category iterator_category;
	typedef typename my_t::value_type value_type;
	typedef typename my_t::difference_type difference_type;
	typedef typename my_t::pointer pointer;
	typedef typename my_t::reference reference;

#else
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = T;
	using pointer = T*;
	using reference = T&;
#endif
	constexpr counter_iterator() : i() { }
	constexpr counter_iterator(T n) : i(n) { }
	counter_iterator& operator=(const counter_iterator& o) noexcept {
		i = o.i;
		return *this;
	}
	constexpr bool operator == (const counter_iterator & rhs) const noexcept { return i == rhs.i; }
	constexpr bool operator != (const counter_iterator & rhs) const noexcept { return i != rhs.i; }
	constexpr const T & operator * () const noexcept { return i; }
	T & operator * () noexcept { return i; }
	constexpr T operator[](difference_type n) const noexcept { return i + n; }
	constexpr counter_iterator operator+(difference_type n) const noexcept { return{ i + n }; }
	constexpr counter_iterator operator-(difference_type n) const noexcept { return{ i - n }; }
	constexpr bool operator<(const counter_iterator& n) const noexcept { return i < n.i; }
	constexpr bool operator<=(const counter_iterator& n) const noexcept { return i <= n.i; }
	constexpr bool operator>(const counter_iterator& n) const noexcept { return i > n.i; }
	constexpr bool operator>=(const counter_iterator& n) const noexcept { return i >= n.i; }
	counter_iterator & operator += (counter_iterator it) noexcept {
		i += it.i;
		return *this;
	}
	counter_iterator & operator -= (counter_iterator it) noexcept {
		i -= it.i;
		return *this;
	}
	counter_iterator & operator ++ () noexcept {
		++i;
		return *this;
	}
	counter_iterator operator ++ (int) noexcept {
		auto t = *this;
		++i;
		return t;
	}
	counter_iterator & operator -- () noexcept {
		--i;
		return *this;
	}
	counter_iterator operator -- (int) noexcept {
		auto t = *this;
		--i;
		return t;
	}
};
template<typename T>
constexpr counter_iterator<T> operator+(typename counter_iterator<T>::difference_type n, const counter_iterator<T>& it) noexcept { return it + n; }
template<typename T>
constexpr counter_iterator<T> operator-(typename counter_iterator<T>::difference_type n, const counter_iterator<T>& it) noexcept { return it - n; }
template<typename T>
constexpr counter_iterator<T> iterator_next(counter_iterator<T> it) noexcept { return it + 1; }
namespace std {
	template<typename T>
	constexpr counter_iterator<T> next(counter_iterator<T> it, typename counter_iterator<T>::difference_type n) noexcept {
		return it + n;
	}
}

template<typename T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
class nth_loop {
public:
	using value_type = std::remove_cv_t<T>;
	using iterator = counter_iterator<value_type>;
private:
	value_type begin_, end_;
public:
	constexpr nth_loop(T n) : begin_(0), end_(n) {}
	constexpr nth_loop(T begin, T end) : begin_(begin), end_(end) {}
	constexpr iterator begin() const noexcept {
		return{ begin_ };
	}
	constexpr iterator end() const noexcept {
		return{ end_ };
	}
};

template<typename T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
constexpr nth_loop<T> rep(T n) noexcept {
	return{ n };
}
template<typename T, std::enable_if_t<std::is_arithmetic<T>::value, std::nullptr_t> = nullptr>
constexpr nth_loop<T> rep(const T& begin, const T& end) noexcept {
	return{ begin, end };
}