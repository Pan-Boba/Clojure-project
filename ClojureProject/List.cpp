#include <cassert>
#include "List.h"

using namespace pdsLib;

template<class T>
Element<T>::Element(T _data, std::shared_ptr<Element<T>> _prev, std::shared_ptr<Element<T>> _next)
{
	data = _data;
	prev = _prev;
	next = _next;
}

template<class T>
List<T>::List()
{
	count = 0;
}

/*list-constructor used to pop front*/
template<class T>
List<T>::List(std::shared_ptr<Element<T>> element, List const& rest)
{
	head = element;
	tail = rest.tail;
	count = rest.count - 1;
}

/*list-constructor used to add head element*/
template<class T>
List<T>::List(T element, List const& rest)
{
	if (rest.count > 0)
	{
		head = std::make_shared<Element<T>>(element, nullptr, rest.head);
		//head = new Element<T>(element, nullptr, rest.head);
		head->next->prev = head;
		tail = rest.tail;
	}
	else
	{
		head = tail = std::make_shared<Element<T>>(element, nullptr, rest.head);
	}

	count = rest.count + 1;
}

/*list-constructor used to add tail element*/
template<class T>
List<T>::List(List const& initial, T element)
{
	if (initial.count > 0)
	{
		head = initial.head;
		tail = std::make_shared<Element<T>>(element, initial.tail, nullptr);
		tail->prev->next = tail;
	}
	else
	{
		head = tail = std::make_shared<Element<T>>(element, initial.tail, nullptr);
	}

	count = initial.count + 1;
}

template<class T>
bool List<T>::IsEmpty() const
{
	return !head;
}

template<class T>
bool List<T>::CorrectIndex(int index) const
{
	return (index >= 0) && (index < count);
}

template<class T>
int List<T>::Count() const
{
	return count;
}

/*return head of the list*/
template<class T>
T List<T>::Front() const
{
	assert(!IsEmpty());
	return head->data;
}

/*return rest of the list*/
template<class T>
List<T> List<T>::PoppedFront() const
{
	assert(!IsEmpty());
	return List(head->next, *this);
}

template<class T>
List<T> List<T>::AddHead(T element) const
{
	try
	{
		return List(element, *this);
	}
	catch (std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
	}
}

template<class T>
List<T> List<T>::AddTail(T element) const
{
	try
	{
		return List(*this, element);
	}
	catch (std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
	}
}

template<class T>
List<T> List<T>::Take(int n) const
{
	if (n <= 0 || IsEmpty()) return List();
	return PoppedFront().Take(n - 1).AddHead(Front());
}

template<class T>
T List<T>::Get(int index) const
{
	assert(!IsEmpty());

	try
	{
		if (!CorrectIndex(index))
			throw std::out_of_range("Incorrect index");

		std::shared_ptr<Element<T>> temp = head;
		for (int i = 0; i < index; i++)
			temp = temp->next;

		return temp->data;
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << std::endl;
	}
}

template<class T>
List<T> List<T>::Set(int index, T _data) const
{
	assert(!IsEmpty());

	try
	{
		if (!CorrectIndex(index))
			throw std::out_of_range("Incorrect index");

		if (index == 0)	
			return Remove(index).AddHead(_data);

		return List(Front(), PoppedFront().Set(index - 1, _data));
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << std::endl;

		return *this;
	}
}

template<class T>
List<T> List<T>::Insert(T _data, int index) const
{
	if (index == 0)
		return AddHead(_data);
	else if (index == count)
		return AddTail(_data);
	else
	{
		assert(!IsEmpty());
		return List<T>(Front(), PoppedFront().Insert(_data, index - 1));
	}
}

template<class T>
List<T> List<T>::Remove(int index) const
{
	try
	{
		if (!CorrectIndex(index))
			throw std::out_of_range("Incorrect index");

		if (IsEmpty())
			return List();

		if (index == 0)
			return PoppedFront();

		else
		{
			return List(Front(), PoppedFront().Remove(index - 1));
		}
	}
	catch (std::out_of_range e)
	{
		std::cout << e.what() << std::endl;
	}
}

template<class T>
void List<T>::PrintAll() const
{
	try
	{
		std::shared_ptr<Element<T>> temp = head;
		for (int i = 0; i < count; i++)
		{
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}
