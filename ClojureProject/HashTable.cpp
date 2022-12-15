#include "HashTable.h"

using namespace pdsLib;

/*return string from T*/
template <class T, class TKey>
std::string HashTable<T, TKey>::toString(const T& data)
{
	std::ostringstream oss;
	oss << data;
	return oss.str();
}

/*return string from TKey*/
template <class T, class TKey>
std::string HashTable<T, TKey>::toString(const TKey& key)
{
	std::ostringstream oss;
	oss << key;
	return oss.str();
}

/*return natural number for hash*/
template <class T, class TKey>
int HashTable<T, TKey>::HashFunctionHorner(const std::string& s, const int tableSize, const int key)
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
template <class T, class TKey>
struct HashTable<T, TKey>::HashFunction1
{
	int operator()(const TKey& key, const int tableSize) const
	{
		const std::string s = toString(key);
		return HashFunctionHorner(s, tableSize, tableSize + 1);
	}
};

template <class T, class TKey>
struct HashTable<T, TKey>::HashFunction2
{
	int operator()(const TKey& key, const int tableSize) const
	{
		const std::string s = toString(key);
		return HashFunctionHorner(s, tableSize, tableSize - 1);
	}
};

/*default constructor*/
template <class T, class TKey>
HashTable<T, TKey>::HashTable()
{
	size = 0;
	bufferSize = 4;
	vecElement.resize(bufferSize);
}

/*constructor used to add elements*/
template <class T, class TKey>
HashTable<T, TKey>::HashTable(std::shared_ptr<Element> element, HashTable const& caller)
{
	size = caller.size;
	bufferSize = caller.bufferSize;
	vecElement = std::move(caller.vecElement);

	// resize
	if (size + 1 > (int) 0.75 * bufferSize)
	{
		bufferSize *= 2;
		vecElement.resize(bufferSize);
	}

	Insert(element->data, element->key);
}

/*constructor used to remove elements*/
template <class T, class TKey>
HashTable<T, TKey>::HashTable(const TKey& key, HashTable const& caller, const HashFunction1& hash1, const HashFunction2& hash2)
{
	bufferSize = caller.bufferSize;
	size = caller.size;

	int h1 = hash1(key, bufferSize);
	int h2 = hash2(key, bufferSize);

	vecElement = std::move(caller.vecElement);

	for (int i = 0; i < bufferSize; ++i)
	{
		if (vecElement.at(h1) && vecElement.at(h1)->key == key)
		{
			--size;
			vecElement.at(h1) = nullptr;

			break;
		}
		h1 = (h1 + h2) % bufferSize;
	}
}

/*Insert element at current vector hash table (used in add constr)*/
template <class T, class TKey>
void HashTable<T, TKey>::Insert(const T& data, const TKey& key, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(key, bufferSize);
	int h2 = hash2(key, bufferSize);

	for (int i = 0; vecElement.at(h1) && i < bufferSize; ++i)
	{
		h1 = (h1 + h2) % bufferSize;
	}

	vecElement.at(h1) = std::make_shared<Element>(data, key, h1);
	++size;
}

/*get num of elements in HashTable*/
template <class T, class TKey>
int HashTable<T, TKey>::Count() const
{
	return size;
}

/*return new HashTable with added element*/
template <class T, class TKey>
HashTable<T, TKey> HashTable<T, TKey>::Add(const T& data, const TKey& key) const
{
	try
	{
		if (Find(key))
			throw std::invalid_argument("\nThis key is already present in the table: ");

		return HashTable(std::make_shared<Element>(data, key), *this);
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << toString(key) << std::endl;
		return *this;
	}
}

/*return new HashTable with removed element*/
template <class T, class TKey>
HashTable<T, TKey> HashTable<T, TKey>::Remove(const TKey& key) const
{
	try
	{
		if (!Find(key))
			throw std::invalid_argument("\nThis key is not present in the table: ");

		return HashTable(key, *this);
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << toString(key) << std::endl;
		return *this;
	}
}

/*find element in HashTable*/
template <class T, class TKey>
bool HashTable<T, TKey>::Find(const TKey& key, const HashFunction1& hash1, const HashFunction2& hash2) const
{
	int h1 = hash1(key, bufferSize);
	int h2 = hash2(key, bufferSize);

	for (int i = 0; i < bufferSize; ++i)
	{
		if (vecElement.at(h1) && vecElement.at(h1)->key == key)
		{
			return true;

		}
		h1 = (h1 + h2) % bufferSize;
	}
	return false;
}

/*get element data of HashTable by key*/
template <class T, class TKey>
T HashTable<T, TKey>::Get(const TKey& key, const HashFunction1& hash1, const HashFunction2& hash2) const
{
	try
	{
		if (!Find(key))
			throw std::invalid_argument("\nThis key is not present in the table: ");

		int h1 = hash1(key, bufferSize);
		int h2 = hash2(key, bufferSize);

		for (int i = 0; i < bufferSize; ++i)
		{
			if (vecElement.at(h1) && vecElement.at(h1)->key == key)
			{
				break;
			}
			h1 = (h1 + h2) % bufferSize;
		}

		return vecElement.at(h1)->data;
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << toString(key) << std::endl;

		return NULL;
	}
}

/*set element data of HashTable by key*/
template <class T, class TKey>
HashTable<T, TKey> HashTable<T, TKey>::Set(const T& data, const TKey& key) const
{
	try
	{
		if (!Find(key))
			throw std::invalid_argument("\nThis key is not present in the table: ");

		return this->Remove(key).Add(data, key);
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << toString(key) << std::endl;

		return *this;
	}
}

/*print all elements from HashTable*/
template <class T, class TKey>
void HashTable<T, TKey>::PrintAll() const
{
	try
	{
		std::cout << "\nSize: " << Count() << std::endl;

		for (const std::shared_ptr<Element>& element : vecElement)
		{
			if (element)
				std::cout << "Key: " << toString(element->key) << "; Data: " << toString(element->data) << " | ";
		}
		std::cout << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
