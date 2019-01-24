#pragma once
#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <array>
#include <vector>

namespace aisdi
{
	using namespace std;
	template <typename KeyType, typename ValueType>
	class HashMap
	{
	public:
		using key_type = KeyType;
		using mapped_type = ValueType;
		using value_type = std::pair<const key_type, mapped_type>;
		using bucket_type = typename std::vector<value_type>;
		using size_type = std::size_t;
		using reference = value_type & ;
		using const_reference = const value_type&;
		using table_type = typename std::array<bucket_type, 1000>;

		class ConstIterator;
		class Iterator;
		using iterator = Iterator;
		using const_iterator = ConstIterator;
	private:
		table_type table;

		size_type get_hash(size_type key_val)
		{
			auto key = key_val;
			key = key * key;

			// Extracting required number of digits ( here, 8 ). 
			key = key / 10000;
			key = key % 1000;

			// Returning the key value. 
			return key;
		}

	public:
		HashMap():table()
		{}

		HashMap(std::initializer_list<value_type> list)
		{
			for (auto i = list.begin(); i != list.end(); ++i)
			{
				value_type object = *i;
				key_type key = object.first;
				size_type index = get_hash(static_cast<size_type> (key));
				table[index].push_back(object);
			}
			cout << list.size() << " objects added to HashMap at position 10\n";
		}

		bool insert(key_type key, mapped_type value)
		{
			value_type new_pair(key, value);
			size_type index = get_hash(static_cast<size_type> (key));
			bucket_type *vec = &table[index];
			for (auto it : *vec)
			{
				if (it.first == key)
				{
					cout << "this key is already occupied\n";
					return 0;
				}
			}
			(*vec).push_back(new_pair);
			return 1;
		}

		mapped_type return_element(int key)
		{
			bucket_type vec = table[10];
			auto it = vec.begin();
			for (; it != vec.end(); ++it)
			{
				if ((*it).first == key)
					return (*it).second;
			}
			throw std::out_of_range("nie znaleziono takiego objektu");
		}

		void print()
		{
			// iterate over std::array (table)
			vector<int> v;
			int n = 0;
			for (const auto it : table)
			{
				// iterate over each vector in hash table
				for (const auto vec_it : it)
				{
					cout << vec_it.first << "\t " << vec_it.second << endl;
					++n;
				}
				if (n != 0)
					v.push_back(n);

				n = 0;
			}
			int sum = 0;
			for (const auto i : v)
				sum += i;

			cout << sum << " elements found" << endl;
			cout << "in " << v.size() << " different vectors\n";
		}

		void print_stats()
		{	// iterate over std::array (table)
			vector<int> v;
			int n = 0;
			for (const auto it : table)
			{
				// iterate over each vector in hash table
				for (const auto vec_it : it)
				{
					++n;
				}
				if (n != 0)
					v.push_back(n);

				n = 0;
			}
			int sum = 0;
			for (const auto i : v)
				sum += i;

			cout << sum << " elements found" << endl;
			cout << "in " << v.size() << " different vectors\n";
		}
		HashMap(const HashMap& other)
		{
			(void)other;
			throw std::runtime_error("TODO");
		}

		HashMap(HashMap&& other)
		{
			(void)other;
			throw std::runtime_error("TODO");
		}

		HashMap& operator=(const HashMap& other)
		{
			(void)other;
			throw std::runtime_error("TODO");
		}

		HashMap& operator=(HashMap&& other)
		{
			(void)other;
			throw std::runtime_error("TODO");
		}

		bool isEmpty() const
		{
			throw std::runtime_error("TODO");
		}

		mapped_type& operator[](const key_type& key)
		{
			throw std::runtime_error("TODO");
		}

		const mapped_type& valueOf(const key_type& key) const
		{
			(void)key;
			throw std::runtime_error("TODO");
		}

		mapped_type& valueOf(const key_type& key)
		{
			(void)key;
			throw std::runtime_error("TODO");
		}

		const_iterator find(const key_type& key) const
		{
			(void)key;
			throw std::runtime_error("TODO");
		}

		iterator find(const key_type& key)
		{
			(void)key;
			throw std::runtime_error("TODO");
		}

		void remove(const key_type& key)
		{
			(void)key;
			throw std::runtime_error("TODO");
		}

		void remove(const const_iterator& it)
		{
			(void)it;
			throw std::runtime_error("TODO");
		}

		size_type getSize() const
		{
			throw std::runtime_error("TODO");
		}

		bool operator==(const HashMap& other) const
		{
			(void)other;
			throw std::runtime_error("TODO");
		}

		bool operator!=(const HashMap& other) const
		{
			return !(*this == other);
		}

		//const table_type *tp, bucket_type *bt, bucket_iter_type &bi, table_iter_type &ti
		iterator begin()
		{
			auto table_it = table.begin();
			while ((*table_it).size() == 0)
				++table_it;
			iterator begin(this, table_it);
			return begin;
		}

		iterator end()
		{
			throw std::runtime_error("TODO");
		}

		const_iterator cbegin() const
		{
			throw std::runtime_error("TODO");
		}

		const_iterator cend() const
		{
			throw std::runtime_error("TODO");
		}

		const_iterator begin() const
		{
			return cbegin();
		}

		const_iterator end() const
		{
			return cend();
		}
	};

	template <typename KeyType, typename ValueType>
	class HashMap<KeyType, ValueType>::ConstIterator
	{
	public:
		using table_type = typename HashMap::table_type;
		using bucket_type = typename HashMap::bucket_type;
		using table_iter_type = typename HashMap::table_type::iterator;
		using bucket_iter_type = typename HashMap::bucket_type::iterator;
		using reference = typename HashMap::const_reference;
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = typename HashMap::value_type;
		using pointer = const typename HashMap::value_type *;

	private:
		table_type *table_ptr;
		table_iter_type table_iter;
		bucket_type *bucket;
		bucket_iter_type bucket_iter;	

	public:

		explicit ConstIterator()
		{}

		ConstIterator(const table_type *tp, table_iter_type &ti)
			: table_ptr(tp), table_iter(ti), bucket(*ti), bucket_iter((*ti)->begin()) {}


		ConstIterator(const ConstIterator& other)
		{
			bucket_iter = other.bucket_iter;
			table_iter = other.table_iter;
		}

		ConstIterator& operator++()
		{
			if (bucket_iter != --bucket->end())
				++bucket_iter;
			else
			{
				while (table_iter != (*table_ptr).end())
				{
					bucket = &(*table_iter);
					if (bucket->size() != 0)
					{
						bucket_iter = bucket->begin();
						break;
					}
					++table_iter;	//next vector;
				}
			// table_iter == table.end();
			}
			return *this;
		}

		ConstIterator operator++(int)
		{
			auto old = *this;
			++(*this);
			return old;
		}

		ConstIterator& operator--()
		{
			throw std::runtime_error("TODO");
		}

		ConstIterator operator--(int)
		{
			throw std::runtime_error("TODO");
		}

		reference operator*() const
		{
			throw std::runtime_error("TODO");
		}

		pointer operator->() const
		{
			//return const_cast<reference>(ConstIterator::operator*());
			return (&this->operator*());
		}

		bool operator==(const ConstIterator& other) const
		{
			(void)other;
			throw std::runtime_error("TODO");
		}

		bool operator!=(const ConstIterator& other) const
		{
			return !(*this == other);
		}
	};

	template <typename KeyType, typename ValueType>
	class HashMap<KeyType, ValueType>::Iterator : public HashMap<KeyType, ValueType>::ConstIterator
	{
	public:
		using table_type = typename HashMap::table_type;
		using bucket_type = typename HashMap::bucket_type;
		using table_iter_type = typename HashMap::table_type::iterator;
		using bucket_iter_type = typename HashMap::bucket_type::iterator;
		using reference = typename HashMap::reference;
		using pointer = typename HashMap::value_type*;

		explicit Iterator()
		{}
		
		Iterator(const table_type *tp, table_iter_type &ti)
			: ConstIterator(tp, ti) {}

		Iterator(const ConstIterator& other)
			: ConstIterator(other)
		{}

		Iterator& operator++()
		{
			ConstIterator::operator++();
			return *this;
		}

		Iterator operator++(int)
		{
			auto result = *this;
			ConstIterator::operator++();
			return result;
		}

		Iterator& operator--()
		{
			ConstIterator::operator--();
			return *this;
		}

		Iterator operator--(int)
		{
			auto result = *this;
			ConstIterator::operator--();
			return result;
		}

		pointer operator->() const
		{
			return &this->operator*();
		}

		reference operator*() const
		{
			// ugly cast, yet reduces code duplication.
			return const_cast<reference>(ConstIterator::operator*());
		}
	};

}

#endif /* AISDI_MAPS_HASHMAP_H */


