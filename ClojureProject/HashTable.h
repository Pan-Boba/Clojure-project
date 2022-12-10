#pragma once

#include <iostream>
#include <string>
#include <sstream>

template <class T>
class HashTable
{
	static const int default_size = 8;
	constexpr static const double rehash_size = 0.75;

	struct Node
	{
		T value;
		bool state;
		Node(const T& value_) : value(value_), state(true) {}
	};

	Node** arr;
	int size;
	int bufferSize;
	int sizeAllNonNullptr;

	void Resize();
	void Rehash();

	static int HashFunctionHorner(const std::string& s, int table_size, const int key);
	static std::string toString(const T value);

public:
	HashTable();
	~HashTable();

	struct HashFunction1
	{
		int operator()(const T& value, int table_size) const
		{
			const std::string s = toString(value);
			return HashFunctionHorner(s, table_size, table_size - 1);
		}
	};

	struct HashFunction2
	{
		int operator()(const T& value, int table_size) const
		{
			const std::string s = toString(value);
			return HashFunctionHorner(s, table_size, table_size + 1);
		}
	};

	bool Add(const T& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	bool Remove(const T& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	bool Find(const T& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
};