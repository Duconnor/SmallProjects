#pragma once

#ifndef SMS_LIST_H
#define SMS_LIST_H

const int MAXSIZELIST = 3000;


template <class T>
class List
{
private:
	T* list;
	int numberOfElementsInList;
public:
	List() { list = new T[MAXSIZELIST]; numberOfElementsInList = 0; }
	~List() { delete list; }
	inline void getNumberOfElements() { return numberOfElementsInList; }
	void insert(const T &newElement) 
	{
		list[numberOfElementsInList] = newElement;
		numberOfElementsInList++;
	}; // ��β������һ������Ʒ
	void remove(int index);
	void clear() { numberOfElementsInList = 0; }
	int size() { return numberOfElementsInList; }
	T* begin() { return list; };
	T* end() { return list + numberOfElementsInList; }
	T get(int index); // ����index���ظô���Ԫ�ص�ַ
	T operator[](int index); // ���������
};

template<class T>
T List<T>::get(int index)
{
	if (index >= numberOfElementsInList)
		return nullptr;
	return list[index];
}

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
T List<T>::operator[](int index)
{
	if (index >= numberOfElementsInList)
		return nullptr;
	else
		return list[index];
}

#endif // !SMS_LIST_H