#include "list.h"

template<class T>
void List<T>::remove(int index)
{
	if (index >= numberOfElementsInList)
		return;
	else
		for (int i = index; i < numberOfElementsInList - 1; i++)
			list[i] = list[i + 1];
}

template<class T>
T * List<T>::get(int index)
{
	if (index >= numberOfElementsInList)
		return nullptr;
	return &list[index];
}

template<class T>
T* List<T>::operator[](int index)
{
	if (index >= numberOfElementsInList)
		return nullptr;
	else
		return &list[index];
}

#define TEST 0

#if TEST == 1
// unit test for list

int main()
{
	List<int> myList;
	int val;
	for (int i = 0; i < 5; i++)
	{
		std::cin >> val;
		myList.insert(val);
	}
	//std::cout << *myList[2];
	for (int x : myList)
		std::cout << x << " ";
	system("pause");
	return 0;
}

#endif