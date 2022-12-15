#include "Array.h"

using namespace pdsLib;

/*return string from T*/
template <class T>
std::string Array<T>::toString(const T& data)
{
	std::ostringstream oss;
	oss << data;
	return oss.str();
}

/*constructor*/
template <class T>
Array<T>::Array<T>() {}

/*constructor used to add elements*/;
template <class T>
Array<T>::Array(std::shared_ptr<Element> element, Array const& caller)
{
	vecElement = std::move(caller.vecElement);
	vecElement.emplace_back(element);
}

/*constructor used to remove elements*/
template <class T>
Array<T>::Array(int index, Array const& caller)
{
	vecElement = std::move(caller.vecElement);
	vecElement.erase(vecElement.begin() + index);
}

/*is empty flag*/
template <class T>
bool Array<T>::IsEmpty() const
{
	// 0 = false, else - true
	if (Count() == 0)
		return true;
	else
		return false;
}

/*get num of elements in Array*/
template <class T>
int Array<T>::Count() const
{
	return vecElement.size();
}

/*return new Array with added element*/
template <class T>
Array<T> Array<T>::Add(const T& data) const
{
	return Array(std::make_shared<Element>(data), *this);
	
}

/*return new Array with removed element*/
template <class T>
Array<T> Array<T>::Remove(const T& data) const
{
	try
	{
		if (!IsEmpty() && !Find(data))
			throw std::invalid_argument("This element is not present in the array"); 

		std::shared_ptr<Element> element = std::make_shared<Element>(data);

		for (int i = 0; i < Count(); ++i)
		{
			if (vecElement.at(i)->data == data)
			{
				return Array(i, *this);
			}
		}
	}
	catch (std::invalid_argument e)
	{
		std::cout << e.what() << std::endl;
		return *this;
	}
}

template <class T>
bool Array<T>::Find(const T& data) const
{
	try
	{
		if (IsEmpty())
			throw std::invalid_argument("Empty array");

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

/*print all elements from Array*/
template <class T>
void Array<T>::PrintAll() const
{
	std::cout << "\nSize: " << Count() << std::endl;

	for (const std::shared_ptr<Element>& element : vecElement)
	{
		if (element)
			std::cout << toString(element->data) << " ";
	}
	std::cout << std::endl;
}
