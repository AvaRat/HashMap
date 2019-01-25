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
	HashMap<uint32_t, string> my_map;
	 HashMap<uint64_t, string> mpo = {  {42, "Henio"}, {27, "marcel"} };
	 unordered_map<uint32_t, string> stl_map;

	 vector<size_t> vec = { 1000, 10000, 100000, 1000000 };
	 string name1 = "myHashMap";
	 string name2 = "stl's unordered_map";
	 string file_output = "C:/Users/marce/OneDrive/Dokumenty/Studia/AISDI/Project_2_try/compare_containers.csv";
//	 test_map(my_map, vec, name1);

	 compare_containers<HashMap<uint32_t, string>, unordered_map<uint32_t, string>>
		 (my_map, stl_map, name1, name2, vec, file_output);


	return 0;
}

