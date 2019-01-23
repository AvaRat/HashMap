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
		using vector_ = std::vector<value_type>;
		using size_type = std::size_t;
		using reference = value_type & ;
		using const_reference = const value_type&;

		class ConstIterator;
		class Iterator;
		using iterator = Iterator;
		using const_iterator = ConstIterator;
	private:
		std::array<vector_, 1000> table;

		bool insert(value_type &elem)
		{
			std::cout << "insert\n";
		}


	public:
		HashMap():table()
		{}

		HashMap(std::initializer_list<value_type> list)
		{
			for (auto i = list.begin(); i != list.end(); ++i)
			{
				table[10].push_back(*i);
			}
			cout << list.size() << " objects added to HashMap at position 10\n";
		}

		mapped_type return_element(int key)
		{
			vector_ vec = table[10];
			auto it = vec.begin();
			for (; it != vec.end(); ++it)
			{
				if ((*it).first == key)
					return (*it).second;
			}
			throw std::out_of_range("nie znaleziono takiego objektu");
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
			(void)key;
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

		iterator begin()
		{
			throw std::runtime_error("TODO");
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
		using reference = typename HashMap::const_reference;
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = typename HashMap::value_type;
		using pointer = const typename HashMap::value_type*;

		explicit ConstIterator()
		{}

		ConstIterator(const ConstIterator& other)
		{
			(void)other;
			throw std::runtime_error("TODO");
		}

		ConstIterator& operator++()
		{
			throw std::runtime_error("TODO");
		}

		ConstIterator operator++(int)
		{
			throw std::runtime_error("TODO");
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
			return &this->operator*();
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
		using reference = typename HashMap::reference;
		using pointer = typename HashMap::value_type*;

		explicit Iterator()
		{}

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


