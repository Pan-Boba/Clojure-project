#pragma once

#include <iostream>

// TO DO: Concat, change to shared_ptr, pds
namespace pdsLib
{
	/*element of List*/
	template<class T>
	struct Element
	{
		T data;
		std::shared_ptr<const Element> prev;
		std::shared_ptr<const Element> next;
	};

	/*doubly persistent linked list*/
	template<class T>
	class List
	{
	private:
		std::shared_ptr<const Element> head;
		std::shared_ptr<const Element> tail;
		int count;

	public:
		List();

		/*copy-constructor*/
		List(const List&);

		bool IsEmpty() const;

		bool CorrectIndex(int);

		/*insert element in head of List*/
		void AddHead(T);

		/*insert element in tail of List*/
		void AddTail(T);

		/*get num of elements in List*/
		int Count();

		/*get element of List by index*/
		T Get(int);
		
		/*get element of List by index*/
		void Set(T, int);

		/*delete element in List by index*/
		void Remove(int index = 0);

		/*insert element in List by index*/
		void Insert(T, int index = 0);
	};

	/*concatenate 2 Lists*/
	template<class T>
	List<T> Concat(List<T> const& a, List<T> const& b);

	/*print all List*/
	template<class T>
	void PrintAll();
}
