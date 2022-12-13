#include "HashTable.h"

using namespace pdsLib;

/*return string from T*/
template <class T>
std::string HashTable<T>::toString(const T& data)
{
	std::ostringstream oss;
	oss << data;
	return oss.str();
}

/*return natural number for hash*/
template <class T>
int HashTable<T>::HashFunctionHorner(const std::string& s, const int tableSize, const int key)
{
	int hashResult = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		hashResult = (key * hashResult + s[i]) % tableSize;
	}
	hashResult = (hashResult * 2 + 1) % tableSize;
	return hashResult;
}

/*double hash method:
two hash functions that return coprime natural numbers*/
template <class T>
struct HashTable<T>::HashFunction1
{
	int operator()(const T& data, const int tableSize) const
	{
		const std::string s = toString(data);
		return HashFunctionHorner(s, tableSize, tableSize + 1);
	}
};

template <class T>
struct HashTable<T>::HashFunction2
{
	int operator()(const T& data, const int tableSize) const
	{
		const std::string s = toString(data);
		return HashFunctionHorner(s, tableSize, tableSize - 1);
	}
};

/*constructor*/
template <class T>
HashTable<T>::HashTable<T>() {}

/*constructor used to add elements*/;
template <class T>
HashTable<T>::HashTable(std::shared_ptr<Element> element, HashTable const& caller)
{
	vecElement = std::move(caller.vecElement);
	vecElement.emplace_back(element);

	// rehash
	for (std::shared_ptr<Element> element : vecElement)
		Hash(element);

}

/*constructor used to remove elements*/
template <class T>
HashTable<T>::HashTable(int index, HashTable const& caller)
{
	vecElement = std::move(caller.vecElement);
	vecElement.erase(vecElement.begin() + index);

	// rehash
	for (std::shared_ptr<Element> element : vecElement)
		Hash(element);

}

/*is empty flag*/
template <class T>
bool HashTable<T>::IsEmpty() const
{
	// 0 = false, else - true
	if (Count() == 0)
		return true;
	else
		return false;
}

/*get num of elements in HashTable*/
template <class T>
int HashTable<T>::Count() const
{
	return vecElement.size();
}

/*change keys*/
template <class T>
void HashTable<T>::Hash(std::shared_ptr<Element> element, const HashFunction1& hash1, const HashFunction2& hash2)
{
	T data = element->data;
	int tableSize = 2 * Count();

	int h1 = hash1(data, tableSize);
	int h2 = hash2(data, tableSize);

	for (std::shared_ptr<Element> el : vecElement)
	{
		if (el->key == h1)
			h1 = (h1 + h2) % tableSize;
	}

	element->key = h1;
}

/*return new HashTable with added element*/
template <class T>
HashTable<T> HashTable<T>::Add(const T& data) const
{
	try
	{
		if (!IsEmpty() && Find(data))
			throw std::invalid_argument("This element is already present in the table");

		return HashTable(std::make_shared<Element>(data), *this);
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
		return *this;
	}
}

/*return new HashTable with removed element*/
template <class T>
HashTable<T> HashTable<T>::Remove(const T& data) const
{
	try
	{
		if (!IsEmpty() && !Find(data))
			throw std::invalid_argument("This element is not present in the table");

		std::shared_ptr<Element> element = std::make_shared<Element>(data);
		int index = 0;

		for (int i = 0; i < Count(); ++i)
		{
			if (vecElement.at(i)->data == data)
			{
				index = i;
			}
		}

		return HashTable(index, *this);
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
		return *this;
	}
}

template <class T>
bool HashTable<T>::Find(const T& data) const
{
	try
	{
		if (IsEmpty())
			throw std::invalid_argument("Empty hash table");

		for (const std::shared_ptr<Element>& element : vecElement)
		{
			if (element->data == data)
			{
				return true;
			}
		}

		return false;
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

/*print all elements from HashTable*/
template <class T>
void HashTable<T>::PrintAll() const
{
	std::cout << "\nSize: " << Count() << std::endl;

	for (const std::shared_ptr<Element>& element : vecElement)
	{
		if (element)
			std::cout << toString(element->data) << " ";
	}
	std::cout << std::endl;
}
