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
	HashMap<int, string> my_map = { {19088889, "marcel"}, {182900122, "Henio"}, {197652, "Lusia"} };
	const unordered_map<int, string> stl_map;

	/*
	HashMap<int, string> m = { {19088889, "marcel"}, {182900122, "Henio"}, {197652, "Lusia"} };
	HashMap<int, string> x;
	x[1424] = string{};
	m.print();
	cout << endl;
	m = x;
	m.print();
	cout << endl;
	x.print();
	*/
	
//	m2.print();


	

/*
	cout << "bucket count: " << stl_map.bucket_count() << endl;
	cout << "max bucket count: " << stl_map.max_bucket_count() << endl;
	cout << "load factor: " << stl_map.load_factor() << endl;
	*/
	return 0;
}

