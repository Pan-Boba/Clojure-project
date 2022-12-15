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

/*default constructor*/
template <class T>
HashTable<T>::HashTable()
{
	size = 0;
	bufferSize = 4;
	vecElement.resize(bufferSize);
}

/*constructor used to add elements*/
template <class T>
HashTable<T>::HashTable(std::shared_ptr<Element> element, HashTable const& caller)
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

	Insert(element->data);
}

/*constructor used to remove elements*/
template <class T>
HashTable<T>::HashTable(const T& data, HashTable const& caller, const HashFunction1& hash1, const HashFunction2& hash2)
{
	bufferSize = caller.bufferSize;
	size = caller.size;

	int h1 = hash1(data, bufferSize);
	int h2 = hash2(data, bufferSize);

	vecElement = std::move(caller.vecElement);

	for (int i = 0; i < bufferSize; ++i)
	{
		if (vecElement.at(h1) && vecElement.at(h1)->data == data)
		{
			--size;
			vecElement.at(h1) = nullptr;

			break;
		}
		h1 = (h1 + h2) % bufferSize;
	}
}

/*Insert element at current vector hash table (used in add constr)*/
template <class T>
void HashTable<T>::Insert(const T& data, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(data, bufferSize);
	int h2 = hash2(data, bufferSize);

	for (int i = 0; vecElement.at(h1) && i < bufferSize; ++i)
	{
		h1 = (h1 + h2) % bufferSize;
	}

	vecElement.at(h1) = std::make_shared<Element>(data, h1);
	++size;
}

/*get num of elements in HashTable*/
template <class T>
int HashTable<T>::Count() const
{
	return size;
}

/*return new HashTable with added element*/
template <class T>
HashTable<T> HashTable<T>::Add(const T& data) const
{
	try
	{
		if (Find(data))
			throw std::invalid_argument("This element is already present in the table: ");

		return HashTable(std::make_shared<Element>(data), *this);
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << toString(data) << std::endl;
		return *this;
	}
}

/*return new HashTable with removed element*/
template <class T>
HashTable<T> HashTable<T>::Remove(const T& data) const
{
	try
	{
		if (!Find(data))
			throw std::invalid_argument("This element is not present in the table: ");

		return HashTable(data, *this);
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << toString(data) << std::endl;
		return *this;
	}
}

/*find element in HashTable*/
template <class T>
bool HashTable<T>::Find(const T& data, const HashFunction1& hash1, const HashFunction2& hash2) const
{
	int h1 = hash1(data, bufferSize);
	int h2 = hash2(data, bufferSize);

	for (int i = 0; i < bufferSize; ++i)
	{
		if (vecElement.at(h1) && vecElement.at(h1)->data == data)
		{
			return true;

		}
		h1 = (h1 + h2) % bufferSize;
	}
	return false;
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
