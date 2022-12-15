#pragma once

#include <iostream>

namespace pdsLib
{
	/*doubly persistent linked list*/
	template<class T>
	class List
	{
	private:
		/*element of List*/
		struct Element
		{
			Element(T, std::shared_ptr<Element>, std::shared_ptr<Element>);
			T data;
			std::shared_ptr<Element> prev;
			std::shared_ptr<Element> next;
		};

		int count;

		std::shared_ptr<Element> head;

		std::shared_ptr<Element> tail;

		/*correct index flag*/
		bool CorrectIndex(int) const;

		/*return head of the list*/
		T Front() const;

		/*return rest of the list*/
		List<T> PoppedFront() const;

	public:
		/*default constructor*/
		List();

		/*list-constructor used to pop front*/
		List(std::shared_ptr<Element>, List const&);

		/*list-constructor used to Insert head element*/
		List(T, List const&);

		/*list-constructor used to Insert tail element*/
		List(List const&, T);

		/*is empty flag*/
		bool IsEmpty() const;

		/*get num of elements in List*/
		int Count() const;

		/*return new List with added head element*/
		List<T> AddHead(T) const;

		/*return new List with added tail element*/
		List<T> AddTail(T) const;

		/*get element of List by index*/
		T Get(int) const;

		/*set element of List by index*/
		List<T> Set(int, T) const;

		/*insert element in List by index*/
		List<T> Insert(T, int index = 0) const;

		/*delete element in List by index*/
		List Remove(int) const;

		/*print all List*/
		void PrintAll() const;
	};
}
