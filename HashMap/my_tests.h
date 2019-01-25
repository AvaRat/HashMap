#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <utility>
#include <unordered_map>
#include <fstream>


#include "HashMap.h"

using namespace std;
using namespace aisdi;
//using Type = std::variant <unordered_map<int, string>, HashMap<int, string>>;


template<class T>
vector<float> &test_map(T &map, vector<size_t> &n_items_vec, string &container_name)
{
	using key_type = typename T::key_type;
	using value_type = typename T::mapped_type;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<size_t>distribution(1, 100000000);
	uniform_int_distribution<size_t>string_gen(32, 126);

	vector<pair<key_type, value_type>> input;
	vector<pair<key_type, value_type>> output;
	for (auto n_items = n_items_vec.begin(); n_items != n_items_vec.end(); ++n_items)
	{
		auto begin = chrono::high_resolution_clock::now();
		for (size_t i = 0; i < *n_items; ++i)
		{
			size_t key = distribution(gen);
			string name = "name__";
			name = name + to_string(i);
			input.push_back(make_pair(key, name));
			map[key] = name;
		}
		auto end = chrono::high_resolution_clock::now();
		cout << "load_factor: " << map.load_factor() << endl;
		cout << "bucket_count: " << map.bucket_count() << endl;

		
		std::chrono::duration<float, nano> diff = end - begin;
		cout << "adding " << *n_items << " items took: " << diff.count() << " [ns]\n";
		
		cout << endl;
		vector<float> times;

		for (int i = 0; i < 100; ++i)
		{

			auto begin = chrono::high_resolution_clock::now();

			auto tmp_key = distribution(gen);
			map.find(tmp_key);

			auto end = chrono::high_resolution_clock::now();
			chrono::duration<float, nano> diff = end - begin;
			times.push_back(diff.count());
		}
		float avg_time;
		float sum = 0;
		for (auto it : times)
		{
			sum += it;
		}
		avg_time = sum / times.size();
		cout << "finding elem took: " << std::fixed << avg_time << " [ns]  (on avg from 100 find calls)\n";
		cout << endl << endl;
		map.clear();
		return times;
	}
}

void write_vector(vector<float> &times, ofstream *of)
{

}


template<class C1, class C2>
void compare_containers(C1 &cont_1, C2 &cont_2, string &cont_1_name, string &cont_2_name, vector<size_t> &n_elems_vec, string &filename)
{
	ofstream file(filename, ios::out|ios::trunc);
	if (!file)
	{
		cout << "cant open\n";
		return;
	}
		file << A << "," << B << "," << C << std::endl;
	

	// close the output file
	cout << "closing file" << endl;
	file.close();
}