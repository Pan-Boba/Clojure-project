#include "List.h"
#include "List.cpp"

int main()
{
	pdsLib::List<double> list1;
	pdsLib::List<double> list2 = list1.AddHead(1).AddTail(2).AddTail(3);

	pdsLib::List<double> list3 = list2.Insert(0, 3);
	//std::cout << list2.Get(0) << std::endl;
	list1.PrintAll();
	list2.PrintAll();
	list3.PrintAll();

	return 0;
}