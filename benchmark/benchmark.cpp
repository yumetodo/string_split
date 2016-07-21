#include "../include/string_split.hpp"
#include "random.hpp"
#include "constant_range_loop.hpp"
#include <iostream>
#include <sstream>
#include <chrono>
//http://qiita.com/iseki-masaya/items/70b4ee6e0877d12dafa8
//copyright : iseki-masaya
std::vector<std::string> split_sstream(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}
//http://qiita.com/iseki-masaya/items/70b4ee6e0877d12dafa8
//copyright : iseki-masaya
std::vector<std::string> split_foreach(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::string item;
	for (char ch : s) {
		if (ch == delim) {
			if (!item.empty())
				elems.push_back(item);
			item.clear();
		}
		else {
			item += ch;
		}
	}
	if (!item.empty())
		elems.push_back(item);
	return elems;
}
//http://qiita.com/sh-o/items/7618599056210d13126e
//copyright : sh-o
std::vector<std::string> split_find(const std::string &s, char delim) {
	std::vector<std::string> re;
	std::size_t ss_point;
	std::string str = s;
	// 部分文字列がヒットし無くなるまで無限ループ
	while (true) {
		ss_point = str.find(delim);
		// 部分文字列が見つからなかった場合
		if (ss_point == -1) {
			break;
		}
		// 部分文字列が見つかった場合
		else {
			re.push_back(str.substr(0, ss_point));
			str = str.substr(ss_point + 1, str.size() - ss_point - 1);
		}
	}
	// 分割後の最後 or 分割文字列が見つからなかった時の処理
	re.push_back(str.substr(0, str.size()));
	return re;
}
//http://wayback.archive.org/web/20110614004133/http://shnya.jp/blog/?p=195
//copyright : shnya
std::vector<std::string> split_find_first_of(const std::string &str, char delim) {
	std::vector<std::string> res;
	size_t current = 0, found;
	while ((found = str.find_first_of(delim, current)) != std::string::npos) {
		res.push_back(std::string(str, current, found - current));
		current = found + 1;
	}
	res.push_back(std::string(str, current, str.size() - current));
	return res;
}
std::vector<std::string> split_our_library(const std::string &str, char delim) {
	return str | split(delim);
}
using split_func_t = std::vector<std::string>(*)(const std::string&, char);
static auto rnd = make_random_generator();
std::string generate_random_string(std::size_t len, std::size_t split_num, char delim) {
	static const char pool[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::vector<std::size_t> delem_pos(split_num);
	std::generate(delem_pos.begin(), delem_pos.end(), [len]() {
		static std::uniform_int_distribution<std::size_t> dist(0, len);
		return dist(rnd);
	});
	std::sort(delem_pos.begin(), delem_pos.end());
	std::string re(len, ' ');
	for (auto&& p : delem_pos) re[p] = delim;
	static std::uniform_int_distribution<std::size_t> dist(0, sizeof(pool) / sizeof(*pool));
	for (auto&& c : re) if (delim != c) c = pool[dist(rnd)];
	return re;
}
void benchmark_split_only(split_func_t split_f, const char* func_name, const std::string& s, char delim, std::size_t cnt) {
	namespace ch = std::chrono;
	const auto t_start = ch::high_resolution_clock::now();
	for (auto&& i : rep(cnt - 1)) {
		split_f(s, delim);
	}
	const auto re = split_f(s, delim);
	const auto t_stop = ch::high_resolution_clock::now();
	std::cout
		<< func_name
		<< ": "
		<< ch::duration_cast<ch::milliseconds>(t_stop - t_start).count()
		<< "[ms] ("
		<< ch::duration_cast<ch::nanoseconds>(t_stop - t_start).count()
		<< "[ns]) : string.length:"
		<< s.length()
		<< " split count:"
		<< re.size()
		<< " roop count:"
		<< cnt
		<< std::endl;
}
void benchmark_split_extract(split_func_t split_f, const char* func_name, const std::string& s, char delim, std::size_t cnt, std::size_t extract_i) {
	namespace ch = std::chrono;
	const auto t_start = ch::high_resolution_clock::now();
	std::string re;
	if (split_our_library == split_f) {
		for (auto&& i : rep(cnt - 1)) {
			s | split(delim)[extract_i];
		}
		re = s | split(delim)[extract_i];
	}
	else {
		for (auto&& i : rep(cnt - 1)) {
			split_f(s, delim)[extract_i];
		}
		re = split_f(s, delim)[extract_i];
	}
	const auto t_stop = ch::high_resolution_clock::now();
	std::cout
		<< func_name
		<< ": "
		<< ch::duration_cast<ch::milliseconds>(t_stop - t_start).count()
		<< "[ms] ("
		<< ch::duration_cast<ch::nanoseconds>(t_stop - t_start).count()
		<< "[ns]) : string.length:"
		<< s.length()
		<< " extract result:"
		<< re
		<< " roop count:"
		<< cnt
		<< std::endl;
}
int main() {
	std::pair<const char*, split_func_t> split_f[] = {
		{ "split_sstream" , split_sstream },
		{ "split_foreach", split_foreach },
		{ "split_find", split_find },
		{ "split_find_first_of", split_find_first_of },
		{ "split_our_library", split_our_library }
	};
	const auto s = generate_random_string(1000, 20, ',');
	for (auto&& f : split_f) benchmark_split_only(f.second, f.first, s, ',', 20000);
	std::cout << std::endl;
	for (auto&& f : split_f) benchmark_split_extract(f.second, f.first, "123,224,42,1,73,2541", ',', 400000, 4);
	return 0;
}
