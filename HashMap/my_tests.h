#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <utility>
#include <unordered_map>
#include <variant>
#include <any>

#include "HashMap.h"

using namespace std;
using namespace aisdi;
//using Type = std::variant <unordered_map<int, string>, HashMap<int, string>>;


template<class T>
void test_map(T &map)
{
	using key_type = typename T::key_type;
	using value_type = typename T::mapped_type;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<size_t>distribution(1, 100000000);
	uniform_int_distribution<size_t>string_gen(32, 126);

	vector<pair<key_type, value_type>> input;
	vector<pair<key_type, value_type>> output;

	auto begin = chrono::high_resolution_clock::now();

	if constexpr (std::is_same<T, HashMap<int, string>>::value)
	{
		for (int i = 0; i < 5000; ++i)
		{
			size_t key = distribution(gen);
			string name = "name__";
			name = name + to_string(i);
			input.push_back(make_pair(key, name));
			map.insert(key, name);
			//	cout << "key,\t string \n" << key << "\t " << name << endl;
		}
		map.print_stats();
	}
	else
	{
		for (int i = 0; i < 5000; ++i)
		{
			size_t key = distribution(gen);
			string name = "name__";
			name = name + to_string(i);
			input.push_back(make_pair(key, name));
			map[key] = name;
			//	cout << "key,\t string \n" << key << "\t " << name << endl;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - begin;
	cout << "operation took: " << diff.count() << " [s]\n";

}