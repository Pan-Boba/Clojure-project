#pragma once
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

		/*vector of elements*/
		std::vector<std::shared_ptr<Element>> vecElement;

	public:

		/*constructor*/
		Array();

		/*constructor used to add elements*/;
		Array(std::shared_ptr<Element>, Array const&);

		/*constructor used to remove elements*/
		Array(int, Array const&);

		/*is empty flag*/
		bool IsEmpty() const;

		/*get num of elements in Array*/
		int Count() const;

		/*return new Array with added element*/
		Array Add(const T&) const;
		
		/*return new Array with removed element*/
		Array Remove(const T&) const;

		/*find element in Array*/
		bool Find(const T&) const;
		
		/*print all elements from Array*/
		void PrintAll() const;
	};
}