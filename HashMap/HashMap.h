#pragma once
#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <array>
#include <vector>
#include <type_traits>
#include <variant>

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
		using table_type = typename std::array<bucket_type, 1000>;
		
		using bucket_const_iterator = typename bucket_type::const_iterator;
		using bucket_iterator = typename bucket_type::iterator;
		using table_const_iterator = typename table_type::const_iterator;
		using table_iterator = typename table_type::iterator;

		using size_type = std::size_t;
		using reference = value_type & ;
		using const_reference = const value_type&;
		

		class ConstIterator;
		class Iterator;
		using iterator = Iterator;
		using const_iterator = ConstIterator;
	private:
		table_type table;
		size_t items_count;

		size_type get_hash(size_type key_val) const
		{
			auto key = key_val;
			key = key * key;

			// Extracting required number of digits ( here, 8 ). 
			key = key / 10000;
			key = key % 1000;

			// Returning the key value. 
			return key;
		}
		bucket_const_iterator find_in_bucket(const bucket_type &bucket, const key_type &key)const
		{
			bucket_const_iterator it = bucket.begin();
			for (;  it != bucket.end();  ++it)
			{
				if ((*it).first == key)
					break;
			}
			return it;
			//return end iterator when cannot find
		}

		bucket_iterator find_in_bucket(bucket_type &bucket, const key_type &key)
		{
			bucket_iterator it = bucket.begin();
			for (; it != bucket.end(); ++it)
			{
				if ((*it).first == key)
					break;
			}
			return it;
			//return end iterator when cannot find
		}

		value_type& insert(value_type &new_pair)
		{
			size_type val = static_cast<size_type> (new_pair.first);
			size_type index = get_hash(val);
			bucket_type *vec = &table[index];
			for (auto it : *vec)
			{
				if (it.first == new_pair.first)
				{
					cout << "this key is already occupied\n";
					throw std::out_of_range("this key is already occupied\n");
				}
			}
			(*vec).push_back(new_pair);
			++items_count;
			return *(--(*vec).end());
		}

	public:
		HashMap():table(), items_count(0)
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
			items_count = list.size();
			cout << list.size() << " objects added to HashMap at position 10\n";
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
			if (items_count == 0)
				return true;
			else
				return false;
		}

		mapped_type& operator[](const key_type& key)
		{
			value_type new_pair(key, mapped_type {});
			value_type *value = &insert(new_pair);
			return (*value).second;
		}

		const mapped_type& valueOf(const key_type& key) const
		{
			size_type index = get_hash(static_cast<size_type> (key));
			bucket_type target_bucket = table[index];
			bucket_const_iterator it = find_in_bucket(target_bucket, key);
			if (it == target_bucket.cend())
				throw std::out_of_range("element with this key doesn't exist");
			else
				return (*it).second;
		}

		mapped_type& valueOf(const key_type& key)
		{
			size_type index = get_hash(static_cast<size_type> (key));
			bucket_type *target_bucket = &table[index];
			bucket_iterator it = find_in_bucket(*target_bucket, key);
			if (it == target_bucket->end())
				throw std::out_of_range("element with this key doesn't exist");
			else
				return (*it).second;
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
			return items_count;
		}

		bool operator==(const HashMap& other) const
		{
			return table == other.table;
		}

		bool operator!=(const HashMap& other) const
		{
			return !(*this == other);
		}

		//const table_type *tp, bucket_type *bt, bucket_iter_type &bi, table_iter_type &ti
		iterator begin()
		{
			table_iterator table_it = table.begin();
			while ((*table_it).size() == 0)
				++table_it;
			bucket_iterator bi = (*table_it).begin();
			iterator it(&table, table_it, bi);
			return it;
		}

		iterator end()
		{
			table_iterator table_it = --table.end();
			while ((*table_it).size() == 0)
				--table_it;
			bucket_iterator bi = (*table_it).end();
			iterator it(&table, table_it, bi);
			return it;
		}

		const_iterator cbegin()const
		{
			table_const_iterator table_it = table.cbegin();
			size_type y_offset = 0;
			while ((*table_it).size() == 0)
			{
				++table_it;
				++y_offset;
			}
			bucket_const_iterator bi = (*table_it).cbegin();
			return const_iterator(&table, table_it, bi);
			//const table_type *tp, table_const_iter_type &ti, bucket_const_iter_type &bi
		/*	
		/*	using table_const_iter_type = typename HashMap::table_const_iterator;
		/*	using table_iter_type = typename HashMap::table_iterator;	
		/*	using bucket_const_iter_type = typename HashMap::bucket_const_iterator;
		/*	using bucket_iter_type = typename HashMap::bucket_iterator;
		*/
			throw std::runtime_error("TODO");
		}

		const_iterator cend()const
		{
			/*
			table_const_iterator table_it = --table.end();
			while ((*table_it).size() == 0)
				--table_it;
			bucket_const_iterator bi = (*table_it).end();
			const table_type *t = &table;
			const_iterator it(t, table_it, bi);
			return it;
			*/
			throw std::runtime_error("TODO");
		}


		const_iterator begin()const
		{
			return cbegin();
		}

		const_iterator end()const
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

		using table_const_iter_type = typename HashMap::table_const_iterator;
		using table_iter_type = typename HashMap::table_iterator;	
		using bucket_const_iter_type = typename HashMap::bucket_const_iterator;
		using bucket_iter_type = typename HashMap::bucket_iterator;

		using reference = typename HashMap::const_reference;
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = typename HashMap::value_type;
		using pointer = const typename HashMap::value_type *;

		using table_mixed_iter = variant< table_iter_type, table_const_iter_type>;
		using bucket_mixed_iter = variant< bucket_iter_type, bucket_const_iter_type>;

		using table_it__ = typename std::iterator_traits;

	private:
	
		const table_type *table_ptr;
		table_mixed_iter table_iter;
		const bucket_type *bucket;
		bucket_mixed_iter bucket_iter;

		bucket_const_iter_type bucket_iter;
		table_const_iter_type table_iter;
		
	public:

		explicit ConstIterator()
		{}

		ConstIterator(const table_type *tp, table_iter_type &ti, bucket_iter_type &bi)
			: table_ptr(tp), table_iter(ti), bucket(&(*ti)), bucket_iter(bi) {}
/*
		ConstIterator(const table_type *tp, table_const_iter_type &ti, bucket_const_iter_type &bi)
			: table_ptr(tp), bucket()
		{
			table_iter = ti;
			bucket_iter = bi;
			bucket = const_cast<bucket_type *>(&(*ti));
		}
*/
		ConstIterator(const table_type *tp, table_const_iter_type &ti, bucket_const_iter_type &bi)
			: table_ptr(tp), bucket(&(*ti)), bucket_c_iter(bi), table_c_iter(ti) {}

		ConstIterator(const table_type *tp, bucket_type *bt ) 
			: table_ptr(tp), bucket(bt)
		{
			/*
			table_iterator ti = (*tp).begin();
			for (size_type i = 0; i < table_offset; ++i)
				++ti;
			bucket_iter_type bi = (*ti).begin();
			for (size_type i = 0; i < bucket_offset; ++i)
				++bi;

			table_iter = ti;
			bucket_iter = bi;
			*/
		}


		ConstIterator(const ConstIterator& other)
		{
			bucket_iter = other.bucket_iter;
			table_iter = other.table_iter;
			bucket = other.bucket;
			table_ptr = other.table_ptr;
		}

		ConstIterator& operator++()
		{
			bucket_const_iter_type bucket_it;
			table_const_iter_type table_it;
			if (bucket_iter.index() == 0)
			{
				bucket_it = get<0>(bucket_iter);
				table_it = get<0>(table_iter);
			}
			else
			{
				bucket_it = get<1>(bucket_iter);
				table_it = get<1>(table_iter);
			}

			if (bucket_c_iter != --(bucket->end()))
				++bucket_c_iter;
			else
			{
				while (table_it != (*table_ptr).end())
				{
					bucket = &(*(++table_it));
					if (bucket->size() != 0)
					{
						bucket_c_iter = bucket->begin();
						break;
					}
				}
			// table_iter == table.end();
			// and it means that we cannot dereference this iterator
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
		//	if constexpr (holds_alternative<table_const_iter_type>(table_iter)
			bucket_const_iter_type bucket_it;
			table_const_iter_type table_it;
			if (bucket_iter.index() == 0)
			{
				bucket_it = get<0>(bucket_iter);
				table_it = get<0>(table_iter);
			}
			else
			{
				bucket_it = get<1>(bucket_iter);
				table_it = get<1>(table_iter);
			}

			if (bucket_it != bucket->begin())
				--bucket_it;
			else
			{
				while (table_it != table_ptr->begin())
				{
					bucket = (&(*(--table_it)));
					if (bucket->size() != 0)
					{
						bucket_it = --(bucket->end());
						break;
					}
				}
			}
			return *this;
		}

		ConstIterator operator--(int)
		{
			auto old = *this;
			--(*this);
			return old;
		}

		reference operator*() const
		{
			if(holds_alternative<bucket_const_iter_type>(bucket_iter))
				return *(get<1>(bucket_iter));
			else
				return *(get<0>(bucket_iter));
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
		using table_iter_type = typename HashMap::table_iterator;
		using bucket_iter_type = typename HashMap::bucket_iterator;
		using reference = typename HashMap::reference;
		using pointer = typename HashMap::value_type*;

		explicit Iterator()
		{}
		
		Iterator(const table_type *tp, table_iter_type &ti, bucket_iter_type &bt)
			: ConstIterator(tp, ti, bt) {}

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


