#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace pdsLib
{
	/*persistent hash table*/
	template <class T, class TKey>
	class HashTable
	{
	private:
		/*element of HashTable*/
		struct Element
		{
			T data;
			TKey key;
			int hashKey;
			
			Element(const T& _data, const TKey& _key, const int _hashKey=0) : data(_data), key(_key), hashKey(_hashKey) {}
		};

		/*return string from T*/
		static std::string toString(const T&);

		/*return string from TKey*/
		static std::string toString(const TKey&);

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
		HashTable(const TKey&, HashTable const&, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());

		/*get num of elements in HashTable*/
		int Count() const;

		/*get element data of HashTable by key*/
		T Get(const TKey&, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2()) const;

		/*set element data of HashTable by key*/
		HashTable Set(const T&, const TKey&) const;

		/*return new HashTable with added element*/
		HashTable Add(const T&, const TKey&) const;
		
		/*return new HashTable with removed element*/
		HashTable Remove(const TKey&) const;

		/*find element in HashTable*/
		bool Find(const TKey&, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2()) const;

		/*print all elements from HashTable*/
		void PrintAll() const;
	private:
		/*Insert element at current vector hash table*/
		void Insert(const T&, const TKey&, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
	};
}