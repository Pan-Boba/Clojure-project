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

/*constructor used to set elements*/
template <class T>
Array<T>::Array(const T& data, int index, Array const& caller)
{
	vecElement.resize(caller.Count());
	
	for (int i = 0; i < caller.Count(); ++i)
	{
		if (i == index)
			vecElement.at(i) = std::make_shared<Element>(data);
		else
			vecElement.at(i) = std::move(caller.vecElement.at(i));
	}
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

/*correct index flag*/
template<class T>
bool Array<T>::CorrectIndex(int index) const
{
	return (index >= 0) && (index < Count());
}

/*get num of elements in Array*/
template <class T>
int Array<T>::Count() const
{
	return vecElement.size();
}

/*return new Array with added element at the end*/
template <class T>
Array<T> Array<T>::Add(const T& data) const
{
	return Array(std::make_shared<Element>(data), *this);
}

/*return new Array without element at given index*/
template <class T>
Array<T> Array<T>::Remove(int index) const
{
	try
	{
		if (!CorrectIndex(index))
			throw std::out_of_range("\nIncorrect index: ");

		return Array(index, *this);

	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << index << std::endl;
		return *this;
	}
}

template <class T>
bool Array<T>::Find(const T& data) const
{
	try
	{
		if (IsEmpty())
			throw std::invalid_argument("\nEmpty array");

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

/*get element data of Array by index*/
template <class T>
T Array<T>::Get(int index) const
{
	try
	{
		if (!CorrectIndex(index))
			throw std::out_of_range("\nIncorrect index: ");

		return vecElement.at(index)->data;
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << index << std::endl;
		return NULL;
	}
}

/*set element data of Array by index*/
template <class T>
Array<T> Array<T>::Set(const T& data, int index) const
{
	try
	{
		if (!CorrectIndex(index))
			throw std::out_of_range("\nIncorrect index: ");

		return Array(data, index, *this);
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << index << std::endl;
		
		return *this;
	}
}

/*print all elements from Array*/
template <class T>
void Array<T>::PrintAll() const
{
	try
	{
		for (const std::shared_ptr<Element>& element : vecElement)
		{
			if (element)
				std::cout << toString(element->data) << " ";
		}
		std::cout << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
