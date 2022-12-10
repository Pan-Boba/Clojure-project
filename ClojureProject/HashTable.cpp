#include "HashTable.h"

template <class T>
int HashTable<T>::HashFunctionHorner(const std::string& s, int table_size, const int key)
{
	int hash_result = 0;
	for (int i = 0; i < s.size(); ++i)
	{
		hash_result = (key * hash_result + s[i]) % table_size;
	}
	hash_result = (hash_result * 2 + 1) % table_size;
	return hash_result;
}

template <class T>
std::string HashTable<T>::toString(const T value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <class T>
void HashTable<T>::Resize()
{
	int past_buffer_size = bufferSize;
	bufferSize *= 2;
	sizeAllNonNullptr = 0;
	size = 0;
	Node** arr2 = new Node * [bufferSize];
	for (int i = 0; i < bufferSize; ++i)
		arr2[i] = nullptr;
	std::swap(arr, arr2);
	for (int i = 0; i < past_buffer_size; ++i)
	{
		if (arr2[i] && arr2[i]->state)
			Add(arr2[i]->value);
	}
	for (int i = 0; i < past_buffer_size; ++i)
		if (arr2[i])
			delete arr2[i];
	delete[] arr2;
}

template <class T>
void HashTable<T>::Rehash()
{
	sizeAllNonNullptr = 0;
	size = 0;
	Node** arr2 = new Node * [bufferSize];
	for (int i = 0; i < bufferSize; ++i)
		arr2[i] = nullptr;
	std::swap(arr, arr2);
	for (int i = 0; i < bufferSize; ++i)
	{
		if (arr2[i] && arr2[i]->state)
			Add(arr2[i]->value);
	}
	for (int i = 0; i < bufferSize; ++i)
		if (arr2[i])
			delete arr2[i];
	delete[] arr2;
}

template <class T>
HashTable<T>::HashTable()
{
	bufferSize = default_size;
	size = 0;
	sizeAllNonNullptr = 0;
	arr = new Node * [bufferSize];
	for (int i = 0; i < bufferSize; ++i)
		arr[i] = nullptr;
}

template <class T>
HashTable<T>::~HashTable()
{
	for (int i = 0; i < bufferSize; ++i)
		if (arr[i])
			delete arr[i];
	delete[] arr;
}

template <class T>
bool HashTable<T>::Add(const T& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	if (size + 1 > int(rehash_size * bufferSize))
		Resize();
	else if (sizeAllNonNullptr > 2 * size)
		Rehash();
	int h1 = hash1(value, bufferSize);
	int h2 = hash2(value, bufferSize);
	int i = 0;
	int first_deleted = -1;
	while (arr[h1] != nullptr && i < bufferSize)
	{
		if (arr[h1]->value == value && arr[h1]->state)
			return false;
		if (!arr[h1]->state && first_deleted == -1)
			first_deleted = h1;
		h1 = (h1 + h2) % bufferSize;
		++i;
	}
	if (first_deleted == -1)
	{
		arr[h1] = new Node(value);
		++sizeAllNonNullptr;
	}
	else
	{
		arr[first_deleted]->value = value;
		arr[first_deleted]->state = true;
	}
	++size;
	return true;
}

template <class T>
bool HashTable<T>::Remove(const T& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(value, bufferSize);
	int h2 = hash2(value, bufferSize);
	int i = 0;
	while (arr[h1] != nullptr && i < bufferSize)
	{
		if (arr[h1]->value == value && arr[h1]->state)
		{
			arr[h1]->state = false;
			--size;
			return true;
		}
		h1 = (h1 + h2) % bufferSize;
		++i;
	}
	return false;
}

template <class T>
bool HashTable<T>::Find(const T& value, const HashFunction1& hash1, const HashFunction2& hash2)
{
	int h1 = hash1(value, bufferSize);
	int h2 = hash2(value, bufferSize);
	int i = 0;
	while (arr[h1] != nullptr && i < bufferSize)
	{
		if (arr[h1]->value == value && arr[h1]->state)
			return true;
		h1 = (h1 + h2) % bufferSize;
		++i;
	}
	return false;
}


