#include "HashTable.h"
#include "HashTable.cpp"

#include "Array.h"
#include "Array.cpp"

using namespace pdsLib;

int main()
{
	
	/*
	HashTable<int> htI;

	HashTable<int> htI2 = htI.Add(0).Add(2).Add(4).Add(5).Add(6);
	//htI.PrintAll();
	htI2.PrintAll();
	htI2.Remove(6).PrintAll();
	//std::cout << htI.Find(0) << std::endl;
	*/


	Array<int> array1;

	Array<int> array2 = array1.Add(0).Add(2).Add(4).Add(5).Add(6);
	array1.PrintAll();
	array2.PrintAll();
	array2.Remove(6).PrintAll();
	std::cout << array1.Find(0) << " Array" << std::endl;

	return 0;
}


//#include "List.h"
//#include "List.cpp"
//
//int main()
//{
//	pdsLib::List<double> list1;
//	pdsLib::List<double> list2 = list1.AddHead(1).AddTail(2).AddTail(3);
//
//	pdsLib::List<double> list3 = list2.Insert(0, 3);
//	//std::cout << list2.Get(0) << std::endl;
//	list1.PrintAll();
//	list2.PrintAll();
//	list3.PrintAll();
//
//	return 0;
//}