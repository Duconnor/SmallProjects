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
//// ����ֵ��е��������(thisWord)�Ƿ���Ŀ�굥��(thatWord)���յ�
//bool isAnswer(Word *thisWord, Word *thatWord)
//{
//	for (int i = 0; i < 26; i++)
//	{
//		// �����������ʵ�frequency�����һ�������в���ͬ���򷵻�false
//		if (thisWord->frequency[i] != thatWord->frequency[i])
//			return false;
//	}
//	return true;
//}
//
//
//// Word�ĳ�ʼ������
//Word *initialWord(char s[])
//{
//	int length = strlen(s);
//	Word *word = new Word;
//	for (int i = 0; i < 26; i++)
//		word->frequency[i] = 0;
//
//	// �������ַ���������word�ڲ�ͳ�ƴ�Ƶ
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
//// ���յ׺������ҵ����е��յף�
//void findAllAnswers(Word* thatWord, Word* answers[], Word* dictionary[],int number,int &count)
//{
//	// number��ʾdictionary�еĵ�����Ŀ
//	// count��ʾ�м����յף���ʼ��Ϊ0��
//
//	// ����dictionary�е�����word�����ÿһ���Ƿ����յף�����Ǿͼ����answers��
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
//// ����õ��ĺ����𰸶���һ����Եõ��Ĵ𰸰��ֵ����������strcmp+bubble sort
//void sort(Word* answers[], int count)
//{
//	if (count == 1 || count == 0)
//		return;
//
//	//bubble sortֻ��Ҫ�Ƚ�n-1��
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
//// ��ӡ���
//void printAnswers(Word* answers[], int count)
//{
//	// count�����յ׵ĸ���
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
//	//�ֵ����뿪ʼ
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
//	// �ֵ�������� 
//
//	// �������뿪ʼ
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
//		// ����յײ�����
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
//		// ������ڽ���������ӡ����
//
//		printAnswers(answers, count);
//		delete w;
//		scanf_s("%s", stringInput, 200);
//		//cin >> stringInput;
//
//	}
//	// �������������ͬʱ��ӡ���
//
//	system("pause");
//	return 0;
//}