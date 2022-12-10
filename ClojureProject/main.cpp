#include "HashTable.h"
#include "HashTable.cpp"

int main()
{
	HashTable<int> htI;

	std::cout << "Add " << htI.Add(10) << std::endl;
	std::cout << "Add " << htI.Add(11) << std::endl;
	std::cout << "Add " << htI.Add(1) << std::endl;

	std::cout << "Find " << htI.Find(1) << std::endl;
	std::cout << "Remove " << htI.Remove(1) << std::endl;
	std::cout << "Find " << htI.Find(1) << std::endl;

	HashTable<double> htD;

	std::cout << "Add " << htD.Add(0.5) << std::endl;
	std::cout << "Add " << htD.Add(0.6) << std::endl;
	std::cout << "Add " << htD.Add(0.7) << std::endl;

	std::cout << "Find " << htD.Find(0.5) << std::endl;
	std::cout << "Remove " << htD.Remove(0.5) << std::endl;
	std::cout << "Find " << htD.Find(0.5) << std::endl;

	/*HashTable<std::string> htS;

	std::cout << "Add " << htS.Add("a") << std::endl;
	std::cout << "Add " << htS.Add("b") << std::endl;
	std::cout << "Add " << htS.Add("c") << std::endl;

	std::cout << "Find " << htS.Find("a") << std::endl;
	std::cout << "Remove " << htS.Remove("a") << std::endl;
	std::cout << "Find " << htS.Find("a") << std::endl;*/

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