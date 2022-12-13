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
			int key;
			Element(const T& _data, const int _key=0) : data(_data), key(_key) {}
		};

		/*return string from T*/
		static std::string toString(const T&);

		/*return natural number for hash*/
		static int HashFunctionHorner(const std::string&, const int, const int key);

		/*vector of elements*/
		std::vector<std::shared_ptr<Element>> vecElement;

	public:
		/*double hash method:
		two hash functions that return coprime natural numbers*/
		struct HashFunction1;
		struct HashFunction2;

		/*constructor*/
		HashTable();

		/*constructor used to add elements*/;
		HashTable(std::shared_ptr<Element>, HashTable const&);

		/*constructor used to remove elements*/
		HashTable(int, HashTable const&);

		/*is empty flag*/
		bool IsEmpty() const;

		/*get num of elements in HashTable*/
		int Count() const;

		/*change keys*/
		void Hash(std::shared_ptr<Element> element, const HashFunction1& hash1 = HashFunction1(), const HashFunction2& hash2 = HashFunction2());

		/*return new HashTable with added element*/
		HashTable Add(const T&) const;
		
		/*return new HashTable with removed element*/
		HashTable Remove(const T&) const;

		/*find element in HashTable*/
		bool Find(const T&) const;
		
		/*print all elements from HashTable*/
		void PrintAll() const;
	};
}