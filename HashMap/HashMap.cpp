// HashMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <random>
#include <chrono>

#include "HashMap.h"

using namespace aisdi;
using namespace std;

unsigned long int get_key(unsigned long int &key_val)
{

	// Taking the key from system time.  
		// returns a  8-digit seed value. 

	// Squaring the key. 
	auto key = key_val;
	key = key * key;

	// Extracting required number of digits ( here, 8 ). 
	key = key / 10000;
	key = key % 100000000;

	// Returning the key value. 
	return key;
}



int main()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long int>distribution(1, 100000000);
	uniform_int_distribution<long int>string_gen(32, 126);

	vector<unsigned long int> key_values;
	vector<unsigned long int> hash_values;
	HashMap<int, string> map = { {1, "marcel"}, {2, "Lusia"}, {3, "Atek"} };

	auto begin = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10000; ++i)
	{
		for (int i = 0; i < 50; ++i)
		{
			unsigned long int key = distribution(gen);
			auto hash_val = get_key(key);
			key_values.push_back(key);
			hash_values.push_back(hash_val);
			//		cout << "key,\t hash_value \n" << key << "\t " << hash_val << endl;
		}

		auto hash_it = hash_values.begin();
		for (auto it : key_values)
		{
			auto hash_val = get_key(it);
			if (hash_val != *hash_it++)
				cout << "different value!!!\n";
		}
		key_values.clear();
		hash_values.clear();
	}
	auto end = chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - begin;
	cout << "1000 iterations took: " << diff.count() << " [s]\n";

	return 0;
}

