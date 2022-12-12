#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace pdsLib
{
	template <class T>
	class HashTable
	{
	private:
		/*element of HashTable*/
		struct Element
		{
			T data;
			bool state; // if the state flag value is false, then the array element has been deleted (deleted)
			Element(const T& data) : data(data), state(true) {}
		};

		/*return natural number for hash*/
		static int HashFunctionHorner(const std::string& s, int tableSize, const int key);

		/*return string from T*/
		static std::string toString(const T& data);

		/*resize HashTable*/
		void Resize();

		/*remove deleted elements from HashTable*/
		void Rehash();

		/*vector of elements*/
		std::vector<std::shared_ptr<Element>> vecSpElement;

		/*how many elements we have in the vector now (taking into account deleted)*/
		int sizeAllNonNullptr;

		/*the size of the vector itself, how much memory is allocated for storing our table*/
		int bufferSize;

		/*the number of elements we currently have in the vector (excluding deleted)*/
		int size;

		/*initial size of our table*/
		static const int defaultSize = 2;

		/*coefficient at which the table will grow*/
		constexpr static const double rehashSize = 0.75;

	public:
		/*constructor*/
		HashTable();

		/*constructor used to copy elements*/
		HashTable(const std::vector<std::shared_ptr<Element>>& vecSpElement);

		/*copy-constructor*/
		HashTable(const HashTable& hashTable);

		/*double hash method: 
		two hash functions that return coprime natural numbers*/
		struct HashFunction1;
		struct HashFunction2;

		/*return new HashTable with added element*/
		HashTable Add(const T& data, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
		
		/*return new HashTable with removed element*/
		HashTable Remove(const T& data, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());

		/*find element in HashTable*/
		bool Find(const T& data, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());
		
		/*is empty flag*/
		bool IsEmpty();

		/*get num of elements in HashTable*/
		int Count();

		/*print all elements from HashTable*/
		void Print();
	};
}