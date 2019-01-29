// HashMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <utility>

#include <unordered_map>
#include <map>

#include "HashMap.h"
#include "my_tests.h"

using namespace aisdi;
using namespace std;



struct test_struct {
	string name;
	size_t age;
	double number;
};


int main()
{
	 HashMap<uint32_t, string> my_map;
	 unordered_map<uint32_t, string> stl_hashMap;

	 vector<size_t> n_elems = { 1000, 10000, 100000,  1000000, 10000000};
	 string name1 = "std::map";
	 string name2 = "std::unordered_map";
	 string file_output = "C:/Users/marce/OneDrive/Dokumenty/Studia/AISDI/Project_2_try/compare_containers.csv";
//	 test_map(stl_map, n_elems);
	 map<uint32_t, string> stl_map;

//	 vector<

	 compare_containers<map<uint32_t, string>, unordered_map<uint32_t, string>>
		 (stl_map, stl_hashMap, name1, name2, n_elems, file_output);


	return 0;
}

