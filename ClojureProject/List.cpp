#include "List.h"

using namespace pdsLib;

template<class T>
List<T>::List()
{
	head = tail = nullptr;
	count = 0;
}

template<class T>
List<T>::List(const List<T>& list)
{
	count = 0;

	Element<T>* temp = list.head;

	while (temp != 0)
	{
		addTail(temp->data);
		temp = temp->next;
	}
}

template<class T>
bool List<T>::IsEmpty() const
{
	return !_head;
}

template<class T>
bool List<T>::CorrectIndex(int index)
{
	return (index >= 0) && (index < count);
}

template<class T>
void List<T>::AddHead(T _data)
{
	try
	{
		Element<T>* temp = new Element<T>;
		temp->prev = nullptr;
		temp->data = _data;
		temp->next = head;

		if (count > 0)
		{
			head->prev = temp;
			head = temp;
		}
		else
		{
			head = tail = temp;
		}

		++count;
	}
	catch (std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
	}
}

template<class T>
void List<T>::AddTail(T _data)
{
	try
	{
		Element<T>* temp = new Element<T>;
		temp->next = nullptr;
		temp->data = _data;
		temp->prev = tail;

		if (tail != nullptr)
			tail->next = temp;

		if (count == 0)
			head = tail = temp;
		else
			tail = temp;

		++count;
	}
	catch (std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
	}
}

template<class T>
int List<T>::Count()
{
	return count;
}

template<class T>
T List<T>::Get(int index)
{
	if (!CorrectIndex(index))
		throw std::out_of_range("Incorrect index");

	Element<T>* temp = head;
	for (int i = 0; i < index; i++)
		temp = temp->next;

	return temp->data;
}

template<class T>
void List<T>::Set(T _data, int index)
{
	if (!CorrectIndex(index))
		throw std::out_of_range("Incorrect index");

	Element<T>* temp = head;
	for (int i = 0; i < index; i++)
		temp = temp->next;
	
	temp->data = _data;
}

template<class T>
void List<T>::Remove(int index)
{
	if (count == 0) return;

	if (!CorrectIndex(index))
		return;

	Element<T>* item = head;
	for (int i = 0; i < index; i++)
		item = item->next;

	Element<T>* itemPrev = item->prev;
	Element<T>* itemNext = item->next;

	if ((count > 1) && (itemPrev != nullptr))
		itemPrev->next = itemNext;

	if ((itemNext != nullptr) && (count > 1))
		itemNext->prev = itemPrev;

	if (index == 0)
		head = itemNext;

	if (index == count - 1)
		tail = itemPrev;

	delete item;

	--count;
}

template<class T>
void List<T>::Insert(T _data, int pos)
{
	if (!CorrectIndex(index))
		return;

	if (index == 0)
	{
		AddHead(_data);
		return;
	}

	if (index == count)
	{
		AddTail(_data);
		return;
	}

	try
	{
		Element<T>* item = head;
		for (int i = 0; i < index; i++)
			item = item->next;

		Element<T>* itemPrev = item->prev;

		Element<T>* temp = new Element<T>;
		temp->data = _data;
		temp->next = item;
		temp->prev = itemPrev;
		itemPrev->next = temp;
		item->prev = temp;

		++count;;
	}
	catch (std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
	}
}

template<class T>
List<T> pdsLib::Concat(List<T> const& a, List<T> const& b)
{
	if (a.isEmpty())
		return b;

	return List<T>(a.front(), Concat(a.popped_front(), b));
}

template<class T>
void pdsLib::PrintAll()
{
	Element<T>* temp = head;
	for (int i = 0; i < count; i++)
	{
		std::cout << temp->data << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}