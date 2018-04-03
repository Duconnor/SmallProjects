//#include <iostream>
//#include <stdio.h>
//using namespace std;
//
//struct Word
//{
//	char word[100];
//	int frequency[26];
//};
//
//// 检查字典中的这个单词(thisWord)是否是目标单词(thatWord)的谜底
//bool isAnswer(Word *thisWord, Word *thatWord)
//{
//	for (int i = 0; i < 26; i++)
//	{
//		// 遍历两个单词的frequency，如果一旦发现有不相同的则返回false
//		if (thisWord->frequency[i] != thatWord->frequency[i])
//			return false;
//	}
//	return true;
//}
//
//
//// Word的初始化函数
//Word *initialWord(char s[])
//{
//	int length = strlen(s);
//	Word *word = new Word;
//	for (int i = 0; i < 26; i++)
//		word->frequency[i] = 0;
//
//	// 将输入字符串内输入word内并统计词频
//	for (int i = 0; i < length; i++)
//	{
//		word->word[i] = s[i];
//		word->frequency[s[i] - 'a']++;
//	}
//	word->word[length] = '\0';
//	return word;
//}
//
//
//// 找谜底函数（找到所有的谜底）
//void findAllAnswers(Word* thatWord, Word* answers[], Word* dictionary[],int number,int &count)
//{
//	// number表示dictionary中的单词数目
//	// count表示有几个谜底（初始化为0）
//
//	// 遍历dictionary中的所有word，检查每一个是否是谜底，如果是就加入进answers中
//	for (int i = 0; i < number; i++)
//	{
//		if (isAnswer(dictionary[i], thatWord))
//		{
//			answers[count] = dictionary[i];
//			count++;
//		}
//	}
//}
//
//
//// 如果得到的函数答案多于一个则对得到的答案按字典序进行排序：strcmp+bubble sort
//void sort(Word* answers[], int count)
//{
//	if (count == 1 || count == 0)
//		return;
//
//	//bubble sort只需要比较n-1次
//	for (int i = 0; i < count-1; i++)
//	{
//		for (int j = 1; j < count - i; j++)
//		{
//			if (strcmp(answers[j - 1]->word, answers[j]->word)>0)
//			{
//				Word *temp = answers[j - 1];
//				answers[j - 1] = answers[j];
//				answers[j] = temp;
//			}
//		}
//	}
//
//}
//
//
//// 打印结果
//void printAnswers(Word* answers[], int count)
//{
//	// count代表谜底的个数
//
//	sort(answers, count);
//
//	for (int i = 0; i < count; i++)
//		cout << answers[i]->word << endl;
//	cout << "******" << endl;
//}
//
//
//// testBubbleSort
////void bubbleSort(int a[], int n)
////{
////	for (int i = 0; i < n - 1; i++)
////	{
////		for (int j = 1; j < n - i; j++)
////		{
////			if (a[j - 1]>a[j])
////			{
////				int temp = a[j - 1];
////				a[j - 1] = a[j];
////				a[j] = temp;
////			}
////		}
////	}
////}
//
//int main()
//{
//	char stringInput[1000];
//	Word* dictionary[200];
//
//	//字典输入开始
//
//	scanf_s("%s", &stringInput, 200);
//	//cin >> stringInput;
//	int number = 0;
//	while (strcmp(stringInput, "XXXXXX") != 0)
//	{
//		Word *w = new Word;
//		w = initialWord(stringInput);
//		dictionary[number] = w;
//		number++;
//		scanf_s("%s", stringInput, 200);
//		//cin >> stringInput;
//	}
//	// 字典输入结束 
//
//	// 谜语输入开始
//
//	scanf_s("%s", stringInput, 200);
//	//cin >> stringInput;
//	Word* answers[200];
//	while (strcmp(stringInput, "XXXXXX") != 0)
//	{
//		int count = 0;
//		Word *w = new Word;
//		w = initialWord(stringInput);
//		findAllAnswers(w, answers, dictionary, number, count);
//		
//		// 如果谜底不存在
//
//		if (count == 0)
//		{
//			delete w;
//			cout << "NOT A VALID WORD" << endl;
//			cout << "******" << endl;
//			scanf_s("%s", stringInput, 200);
//			//cin >> stringInput;
//			continue;
//		}
//
//		// 如果存在结果，将其打印出来
//
//		printAnswers(answers, count);
//		delete w;
//		scanf_s("%s", stringInput, 200);
//		//cin >> stringInput;
//
//	}
//	// 谜语输入结束，同时打印完成
//
//	system("pause");
//	return 0;
//}