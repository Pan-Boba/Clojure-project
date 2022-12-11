#include "HashTable.h"

template <class T>
HashTable<T>::HashTable<T>()
{
	vecSpNodes.resize(defaultSize);
	sizeAllNonNullptr = 0;
	size = 0;
	bufferSize = defaultSize;
}

template <class T>
HashTable<T>::HashTable<T>(const std::vector<std::shared_ptr<Node>>& vecSpNodes)
{
	for (std::shared_ptr<Node> node : vecSpNodes)
	{
		this = this->Add(node);
	}
}

template <class T>
HashTable<T>::HashTable<T>(const HashTable& hashTable)
{
	vecSpNodes.resize(hashTable.bufferSize);
	sizeAllNonNullptr = hashTable.sizeAllNonNullptr;
	size = hashTable.size;
	bufferSize = hashTable.bufferSize;

	for (int i = 0; i < bufferSize; ++i)
	{
		vecSpNodes.at(i) = hashTable.vecSpNodes.at(i);
	}
}

template <class T>
struct HashTable<T>::HashFunction1
{
	int operator()(const T& value, int tableSize) const
	{
		const std::string s = toString(value);
		return HashFunctionHorner(s, tableSize, tableSize - 1);
	}
};

template <class T>
struct HashTable<T>::HashFunction2
{
	int operator()(const T& value, int tableSize) const
	{
		const std::string s = toString(value);
		return HashFunctionHorner(s, tableSize, tableSize + 1);
	}
};

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

template <class T>
std::string HashTable<T>::toString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <class T>
void HashTable<T>::Resize()
{
	sizeAllNonNullptr = 0;
	int prevBufferSize = bufferSize;
	bufferSize *= 2;
	size = 0;

	std::vector<std::shared_ptr<Node>> vecSpNodesTemp;
	vecSpNodesTemp.resize(bufferSize);
	std::swap(vecSpNodes, vecSpNodesTemp);

	for (int i = 0; i < prevBufferSize; ++i)
	{
		if (vecSpNodesTemp.at(i) && vecSpNodesTemp.at(i)->state)
		{
			Add(vecSpNodesTemp.at(i)->value);
		}
	}

	vecSpNodesTemp.clear();
	vecSpNodesTemp.reserve(0);
}

template <class T>
void HashTable<T>::Rehash()
{
	sizeAllNonNullptr = 0;
	size = 0;
	std::vector<std::shared_ptr<Node>> vecSpNodesTemp;
	vecSpNodesTemp.resize(bufferSize);
	std::swap(vecSpNodes, vecSpNodesTemp);

	for (int i = 0; i < bufferSize; ++i)
	{
		if (vecSpNodesTemp.at(i) && vecSpNodesTemp.at(i)->state)
		{
			Add(vecSpNodesTemp.at(i)->value);
		}
	}

	vecSpNodesTemp.clear();
	vecSpNodesTemp.reserve(0);
}

template <class T>
HashTable<T> HashTable<T>::Add(const T& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	if (size + 1 > int(rehashSize * bufferSize))
	{
		Resize();
	}
	else if (sizeAllNonNullptr > 2 * size)
	{
		Rehash();
	}

	int h1 = hash1(value, bufferSize);
	int h2 = hash2(value, bufferSize);
	int i = 0;
	int firstDeleted = -1;
	while (vecSpNodes.at(h1) != nullptr && i < bufferSize)
	{
		if (vecSpNodes.at(h1)->value == value && vecSpNodes.at(h1)->state)
			return HashTable();;
		if (!vecSpNodes.at(h1)->state && firstDeleted == -1)
			firstDeleted = h1;
		h1 = (h1 + h2) % bufferSize;
		++i;
	}
	if (firstDeleted == -1)
	{
		vecSpNodes.at(h1) = std::make_unique<Node>(value);
		++sizeAllNonNullptr;
	}
	else
	{
		vecSpNodes.at(firstDeleted)->value = value;
		vecSpNodes.at(firstDeleted)->state = true;
	}

	++size;

	return HashTable(*this);
}

template <class T>
HashTable<T> HashTable<T>::Remove(const T& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(value, bufferSize);
	int h2 = hash2(value, bufferSize);

	int i = 0;
	while (vecSpNodes.at(h1) != nullptr && i < bufferSize)
	{
		if (vecSpNodes.at(h1)->value == value && vecSpNodes.at(h1)->state)
		{
			vecSpNodes.at(h1)->state = false;
			--size;

			return HashTable(*this);
		}
		h1 = (h1 + h2) % bufferSize;
		++i;
	}

	return HashTable();
}

template <class T>
bool HashTable<T>::Find(const T& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(value, bufferSize);
	int h2 = hash2(value, bufferSize);

	int i = 0;
	while (vecSpNodes.at(h1) != nullptr && i < bufferSize)
	{
		if (vecSpNodes.at(h1)->value == value && vecSpNodes.at(h1)->state)
			return true;
		h1 = (h1 + h2) % bufferSize;
		++i;
	}
	return false;
}

template <class T>
bool HashTable<T>::IsEmpty()
{
	return Count();
}

template <class T>
int HashTable<T>::Count()
{
	return size;
}

template <class T>
void HashTable<T>::Print()
{
	std::cout << "Size: " << Count() << std::endl;
	if (size > 0)
	{
		for (std::shared_ptr<Node> node : vecSpNodes)
		{
			if (node && node->state)
				std::cout << toString(node->value) << " ";
		}
		std::cout << std::endl;
	}
}
