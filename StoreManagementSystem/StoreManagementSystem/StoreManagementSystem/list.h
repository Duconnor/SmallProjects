#pragma once

#ifndef SMS_LIST_H
#define SMS_LIST_H

const int MAXSIZE = 3000;


template <class T>
class List
{
private:
	T* list;
	int numberOfElementsInList;
public:
	List() { list = new T[MAXSIZE]; numberOfElementsInList = 0; }
	~List() { delete list; }
	inline void getNumberOfElements() { return numberOfElementsInList; }
	void insert(const T &newElement) 
	{
		list[numberOfElementsInList] = newElement;
		numberOfElementsInList++;
	}; // 在尾部插入一个新商品
	void remove(int index);
	void clear() { numberOfElementsInList = 0; }
	T* begin() { return list; };
	T* end() { return list + numberOfElementsInList; }
	T* get(int index); // 输入index返回该处的元素地址
	T* operator[](int index); // 重载运算符
};

#endif // !SMS_LIST_H