#pragma once

#include <iostream>

// TO DO: Concat, change to shared_ptr, pds
namespace pdsLib
{
	/*element of List*/
	template<class T>
	struct Element
	{
		Element() {};
		Element(T, std::shared_ptr<Element<T>>, std::shared_ptr<Element<T>>);
		T data;
		std::shared_ptr<Element<T>> prev;
		std::shared_ptr<Element<T>> next;
	};

	/*doubly persistent linked list*/
	template<class T>
	class List
	{
	private:
		std::shared_ptr<Element<T>> head;
		std::shared_ptr<Element<T>> tail;
		int count;

		/*correct index flag*/
		bool CorrectIndex(int) const;

		/*return head of the list*/
		T Front() const;

		/*return rest of the list*/
		List<T> PoppedFront() const;

	public:
		/*constructor*/
		List();

		/*list-constructor used to pop front*/
		List(std::shared_ptr<Element<T>>, List const&);

		/*list-constructor used to add head element*/
		List(T, List const&);

		/*list-constructor used to add tail element*/
		List(List const&, T);

		/*is empty flag*/
		bool IsEmpty() const;

		/*get num of elements in List*/
		int Count() const;

		/*return new List with added head element*/
		List<T> AddHead(T) const;

		/*return new List with added tail element*/
		List<T> AddTail(T) const;

		/*take and return new List from 0 to int elements*/
		List<T> Take(int) const;

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
