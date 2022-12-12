#include "HashTable.h"

using namespace pdsLib;

/*constructor*/
template <class T>
HashTable<T>::HashTable<T>()
{
	bufferSize = defaultSize;
	vecSpElement.resize(defaultSize);
	sizeAllNonNullptr = 0;
	size = 0;
}

/*constructor used to copy elements*/
template <class T>
HashTable<T>::HashTable<T>(const std::vector<std::shared_ptr<Element>>& vecSpElement)
{
	for (std::shared_ptr<Element> element : vecSpElement)
	{
		this = this->Add(element);
	}
}

/*copy-constructor*/
template <class T>
HashTable<T>::HashTable<T>(const HashTable& hashTable)
{
	bufferSize = hashTable.bufferSize;
	sizeAllNonNullptr = hashTable.sizeAllNonNullptr;
	size = hashTable.size;
	
	for (const auto& element : hashTable.vecSpElement)
	{
		vecSpElement.push_back(element);
	}
}

/*double hash method:
two hash functions that return coprime natural numbers*/
template <class T>
struct HashTable<T>::HashFunction1
{
	int operator()(const T& data, int tableSize) const
	{
		const std::string s = toString(data);
		return HashFunctionHorner(s, tableSize, tableSize - 1);
	}
};

template <class T>
struct HashTable<T>::HashFunction2
{
	int operator()(const T& data, int tableSize) const
	{
		const std::string s = toString(data);
		return HashFunctionHorner(s, tableSize, tableSize + 1);
	}
};

/*return natural number for hash*/
template <class T>
int HashTable<T>::HashFunctionHorner(const std::string& s, int tableSize, const int key)
{
	int hashResult = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		hashResult = (key * hashResult + s[i]) % tableSize;
	}
	hashResult = (hashResult * 2 + 1) % tableSize;
	return hashResult;
}

/*return string from T*/
template <class T>
std::string HashTable<T>::toString(const T& data)
{
	std::ostringstream oss;
	oss << data;
	return oss.str();
}

/*resize HashTable*/
template <class T>
void HashTable<T>::Resize()
{
	sizeAllNonNullptr = 0;
	int prevBufferSize = bufferSize;
	bufferSize *= 2;
	size = 0;

	std::vector<std::shared_ptr<Element>> vecSpElementTemp;
	vecSpElementTemp.resize(bufferSize);
	std::swap(vecSpElement, vecSpElementTemp);

	for (int i = 0; i < prevBufferSize; ++i)
	{
		if (vecSpElementTemp.at(i) && vecSpElementTemp.at(i)->state)
		{
			Add(vecSpElementTemp.at(i)->data);
		}
	}

	vecSpElementTemp.clear();
	vecSpElementTemp.reserve(0);
}

/*remove deleted elements from HashTable*/
template <class T>
void HashTable<T>::Rehash()
{
	sizeAllNonNullptr = 0;
	size = 0;
	std::vector<std::shared_ptr<Element>> vecSpElementTemp;
	vecSpElementTemp.resize(bufferSize);
	std::swap(vecSpElement, vecSpElementTemp);

	for (int i = 0; i < bufferSize; ++i)
	{
		if (vecSpElementTemp.at(i) && vecSpElementTemp.at(i)->state)
		{
			Add(vecSpElementTemp.at(i)->data);
		}
	}

	vecSpElementTemp.clear();
	vecSpElementTemp.reserve(0);
}

/*return new HashTable with added element*/
template <class T>
HashTable<T> HashTable<T>::Add(const T& data, const HashFunction1& hash1, const HashFunction2& hash2)
{
	if (size + 1 > int(rehashSize * bufferSize))
	{
		Resize();
	}
	else if (sizeAllNonNullptr > 2 * size)
	{
		Rehash();
	}

	int h1 = hash1(data, bufferSize);
	int h2 = hash2(data, bufferSize);

	int i = 0;
	int firstDeleted = -1;
	while (vecSpElement.at(h1) && i < bufferSize)
	{
		if (vecSpElement.at(h1)->data == data && vecSpElement.at(h1)->state)
			return HashTable();;
		if (!vecSpElement.at(h1)->state && firstDeleted == -1)
			firstDeleted = h1;
		h1 = (h1 + h2) % bufferSize;
		++i;
	}
	if (firstDeleted == -1)
	{
		vecSpElement.at(h1) = std::make_unique<Element>(data);
		++sizeAllNonNullptr;
	}
	else
	{
		vecSpElement.at(firstDeleted)->data = data;
		vecSpElement.at(firstDeleted)->state = true;
	}

	++size;

	return HashTable(*this);
}

/*return new HashTable with removed element*/
template <class T>
HashTable<T> HashTable<T>::Remove(const T& data, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(data, bufferSize);
	int h2 = hash2(data, bufferSize);

	int i = 0;
	while (vecSpElement.at(h1) && i < bufferSize)
	{
		if (vecSpElement.at(h1)->data == data && vecSpElement.at(h1)->state)
		{
			vecSpElement.at(h1)->state = false;
			--size;

			return HashTable(*this);
		}
		h1 = (h1 + h2) % bufferSize;
		++i;
	}

	return HashTable();
}

/*find element in HashTable*/
template <class T>
bool HashTable<T>::Find(const T& data, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(data, bufferSize);
	int h2 = hash2(data, bufferSize);

	int i = 0;
	while (vecSpElement.at(h1) && i < bufferSize)
	{
		if (vecSpElement.at(h1)->data == data && vecSpElement.at(h1)->state)
			return true;
		h1 = (h1 + h2) % bufferSize;
		++i;
	}
	return false;
}

/*is empty flag*/
template <class T>
bool HashTable<T>::IsEmpty()
{
	return Count();
}

/*get num of elements in HashTable*/
template <class T>
int HashTable<T>::Count()
{
	return size;
}

/*print all elements from HashTable*/
template <class T>
void HashTable<T>::Print()
{
	std::cout << "Size: " << Count() << std::endl;
	if (size)
	{
		for (std::shared_ptr<Element>& element : vecSpElement)
		{
			if (element && element->state)
				std::cout << toString(element->data) << " ";
		}
		std::cout << std::endl;
	}
}
