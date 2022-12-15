#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

namespace pdsLib
{
	template <class T>
	class Array
	{
	private:
		/*element of Array*/
		struct Element
		{
			T data;
			Element(const T& _data) : data(_data) {}
		};

		/*return string from T*/
		static std::string toString(const T&);

		/*correct index flag*/
		bool CorrectIndex(int) const;

		/*vector of elements*/
		std::vector<std::shared_ptr<Element>> vecElement;

	public:

		/*constructor*/
		Array();

		/*constructor used to add elements*/;
		Array(std::shared_ptr<Element>, Array const&);

		/*constructor used to remove elements*/
		Array(int, Array const&);

		/*constructor used to set elements*/
		Array(const T&, int, Array const&);

		/*is empty flag*/
		bool IsEmpty() const;

		/*get num of elements in Array*/
		int Count() const;

		/*get element data of Array by index*/
		T Get(int) const;

		/*set element data of Array by index*/
		Array Set(const T&, int) const;

		/*return new Array with added element at the end*/
		Array Add(const T&) const;
		
		/*return new Array without element at given index*/
		Array Remove(int) const;

		/*find element in Array*/
		bool Find(const T&) const;
		
		/*print all elements from Array*/
		void PrintAll() const;
	};
}