// HashMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <utility>
#include <unordered_map>

#include "HashMap.h"
#include "my_tests.h"

using namespace aisdi;
using namespace std;



int main()
{
	HashMap<int, string> my_map;
	unordered_map<int, string> stl_map;
	test_map(my_map);
	test_map(stl_map);
	

/*
	cout << "bucket count: " << stl_map.bucket_count() << endl;
	cout << "max bucket count: " << stl_map.max_bucket_count() << endl;
	cout << "load factor: " << stl_map.load_factor() << endl;
	*/
	return 0;
}

