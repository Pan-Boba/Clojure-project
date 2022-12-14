#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace pdsLib
{
	/*persistent hash table*/
	template <class T>
	class HashTable
	{
	private:
		/*element of HashTable*/
		struct Element
		{
			T data;
			int key;
			Element(const T& _data, const int _key=0) : data(_data), key(_key) {}
		};

		/*return string from T*/
		static std::string toString(const T&);

		/*return natural number for hash*/
		static int HashFunctionHorner(const std::string&, const int, const int key);

		/*vector of elements*/
		std::vector<std::shared_ptr<Element>> vecElement;

		/*vector of elements*/
		int size;

		/*vector allocated memory (used for hashing)*/
		int bufferSize;

	public:
		/*double hash method:
		two hash functions that return coprime natural numbers*/
		struct HashFunction1;
		struct HashFunction2;

		/*default constructor*/
		HashTable();

		/*constructor used to add elements*/
		HashTable(std::shared_ptr<Element>, HashTable const&);

		/*constructor used to remove elements*/
		HashTable(const T&, HashTable const&, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());

		/*get num of elements in HashTable*/
		int Count() const;

		/*return new HashTable with added element*/
		HashTable Add(const T&) const;
		
		/*return new HashTable with removed element*/
		HashTable Remove(const T&) const;

		/*find element in HashTable*/
		bool Find(const T&, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2()) const;
		
		/*print all elements from HashTable*/
		void PrintAll() const;
	private:
		/*Insert element at current vector hash table*/
		void Insert(const T&, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	};
}