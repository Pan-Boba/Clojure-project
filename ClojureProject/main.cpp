#include "HashTable.h"
#include "HashTable.cpp"

using namespace pdsLib;

int main()
{
	HashTable<int> htI;
	htI.Print();

	HashTable<int> htI2 = htI.Add(10).Add(1).Add(2);
	htI2.Print();

	HashTable<int> htI3 = htI2.Remove(10);
	htI3.Print();

	HashTable<double> htD;
	htD.Print();

	HashTable<double> htD2 = htD.Add(0.1).Add(0.5).Add(2.1);
	htD2.Print();

	HashTable<double> htD3 = htD2.Remove(0.5);
	htD3.Print();

	HashTable<std::string> htS;
	htS.Print();

	HashTable<std::string> htS2 = htS.Add("a").Add("b").Add("c");
	htS2.Print();

	HashTable<std::string> htS3 = htS2.Remove("c");
	htS3.Print();

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