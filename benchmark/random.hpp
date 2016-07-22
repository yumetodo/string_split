/*=============================================================================
Copyright (C) 2016 yumetodo

Distributed under the Boost Software License, Version 1.0.
(See http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif
#if defined(_WIN32) || defined(_WIN64)
#	define MY_ARC_FOR_WINDWOS 1
#	include <Windows.h>
#elif defined(linux)
#	include <fstream>
#endif // defined(_WIN32) || defined(_WIN64)
#include <vector>
#include <random>
#include <stdlib.h> //rand_s, malloc
#include <algorithm>//std::generate
#include <ctime>//clock(), time()
#include <functional>//std::ref in gcc
#include <memory>
#include <cstdint>
#include <chrono>
#include <type_traits>
#include <climits>
namespace detail {
	template<typename T>
	struct vector_push_back_helper {
		T value;
	};
	template<typename value_type, typename T, bool T_is_larger>
	struct vector_push_back_pointer_operator_impl {
		void operator()(std::vector<value_type>& v, vector_push_back_helper<T> info) {
			v.push_back((value_type)(info.value));
		}
	};
	template<typename value_type, typename T>
	struct vector_push_back_pointer_operator_impl<value_type, T, true> {
		void operator()(std::vector<value_type>& v, vector_push_back_helper<T> info) {
			constexpr size_t size_time = sizeof(T) / sizeof(value_type);
			constexpr size_t rshft_num = sizeof(value_type) * CHAR_BIT;
			v.reserve(v.size() + size_time);
			for (size_t i = 0; i < size_time; ++i) {
				if(auto tmp = static_cast<value_type>(((std::uintmax_t)(info.value)) >> (rshft_num * i))) v.push_back(tmp);
			}
		}
	};
	template<typename value_type, typename T, std::enable_if_t<std::is_arithmetic<T>::value || std::is_pointer<T>::value, std::nullptr_t> = nullptr>
	void operator| (std::vector<value_type>& v, vector_push_back_helper<T> info) {
		vector_push_back_pointer_operator_impl<value_type, T, (sizeof(value_type) < sizeof(T))> ()(v, info);
	}
}
template<typename T, std::enable_if_t<std::is_arithmetic<T>::value || std::is_pointer<T>::value, std::nullptr_t> = nullptr>
constexpr detail::vector_push_back_helper<T> push_back(T pointer) { return{ std::forward<T>(pointer) }; }
using seed_v_t = std::vector<unsigned int>;
seed_v_t create_seed_v() {
	const auto begin_time = std::chrono::high_resolution_clock::now();
	std::random_device rnd;// ランダムデバイス
	seed_v_t sed_v(9);// 初期化用ベクター
	std::generate(sed_v.begin(), sed_v.end(), std::ref(rnd));// ベクタの初期化
#if defined(MY_ARC_FOR_WINDWOS)
	POINT point;
	GetCursorPos(&point);
	sed_v.push_back(point.x);
	sed_v.push_back(point.y);
#elif defined(linux)
	{
		std::ifstream file("/dev/random", std::ios::binary);
		if (file.is_open()) {
			unsigned int tmp;
			file.read(reinterpret_cast<char*>(&tmp), sizeof(unsigned int));
			file.close();
			sed_v.push_back(tmp);
		}
	}
	{
		std::ifstream file("/dev/urandom", std::ios::binary);
		if (file.is_open()) {
			unsigned int tmp[5];
			file.read(reinterpret_cast<char*>(tmp), sizeof(tmp));
			file.close();
			sed_v.reserve(sed_v.size() + sizeof(tmp) / sizeof(*tmp));
			for(auto&& t : tmp) sed_v.push_back(t);
		}
	}
#endif
	sed_v | push_back(clock());//clock関数の結果もベクターに追加
	sed_v | push_back(time(nullptr));//time関数の結果もベクターに追加
	//ヒープ領域のアドレスもベクターに追加
	auto heap = std::make_unique<char>();
	sed_v | push_back(heap.get());
	sed_v | push_back(&heap);
	const auto end_time = std::chrono::high_resolution_clock::now();
	sed_v | push_back((end_time - begin_time).count());
	return sed_v;
}
std::mt19937 make_random_generator() {
	const auto sed_v = create_seed_v();
	std::seed_seq seq(sed_v.begin(), sed_v.end());
	return std::mt19937(seq);
}