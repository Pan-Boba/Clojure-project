#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template <class T>
class HashTable
{
	static const int defaultSize = 2;
	constexpr static const double rehashSize = 0.75;

	struct Node
	{
		T value;
		bool state;
		Node(const T& value) : value(value), state(true) {}
	};

	std::vector<std::shared_ptr<Node>> vecSpNodes;

	static int HashFunctionHorner(const std::string& s, int tableSize, const int key);
	static std::string toString(const T& value);

	void Resize();
	void Rehash();

	int sizeAllNonNullptr;
	int bufferSize;
	int size;

public:
	HashTable();
	HashTable(const std::vector<std::shared_ptr<Node>>& vecSpNodes);
	HashTable(const HashTable& hashTable);
	~HashTable() {}

	struct HashFunction1;
	struct HashFunction2;

	HashTable Add(const T& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	HashTable Remove(const T& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	
	bool Find(const T& value, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	bool IsEmpty();
	int Count();
	void Print();
	
};