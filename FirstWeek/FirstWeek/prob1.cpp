//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//
//typedef struct stringWord
//{
//	char string[200];
//	char vowel[200]; // �ַ���������Ԫ����ĸ�������ҵĳ���˳�򹹳ɵ�����
//	int vowelPosition[200]; // ���ڴ洢�ַ�����Ԫ����λ�ã����������δ洢����һ��λ��Ϊ0��
//	int count; // ���ٸ�Ԫ����ĸ
//}Word;
//
//// ������ĸ�ǲ���Ԫ����ĸ
//int isVowel(char s)
//{
//	if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u')
//		return 1;
//	return 0;
//}
//
//// ��ʼ��Word���ҵ��������е�Ԫ����ĸ����¼��λ��
//void initialWord(char input[], Word *word)
//{
//	int length = strlen(input);
//	word->count = 0;
//
//	for (int i = 0; i < length; i++)
//	{
//		word->string[i] = input[i];
//		if (isVowel(input[i]))
//		{
//			// �����Ԫ���Ļ�������������ֵΪ1��
//			word->vowel[word->count] = input[i];
//			word->vowelPosition[word->count] = i;
//			word->count++;
//		}
//	}
//	word->string[length] = '\0';
//	word->vowel[word->count] = '\0';
//}
//
//
//// �������е�Ԫ�ؽ���ѭ������mλ�Ĵ���
//void moveRight(char string[] , int m)
//{
//	int length = strlen(string);
//
//	// ����ÿ��Ԫ�����ƺ����λ�ý�����ڸ�������aux��
//	char *aux = (char *)malloc(length * sizeof(char));
//	for (int i = 0; i < length; i++)
//	{
//		int newPosition = (i + m) % length;
//		aux[newPosition] = string[i];
//	}
//
//	// �����������е�Ԫ�ؿ�����ȥ
//	for (int i = 0; i < length; i++)
//		string[i] = aux[i];
//}
//
//
//// �������
//void solveProblem(Word *word, int m)
//{
//	// ��ֻ��Ԫ����ĸ����������
//	moveRight(word->vowel, m);
//
//	// �����µ�Ԫ����ĸ˳�򣬸����ַ����е�Ԫ����ĸ˳��
//	for (int i = 0; i < word->count; i++)
//		word->string[word->vowelPosition[i]] = word->vowel[i];
//
//	printf("%s\n", word->string);
//}
//
//
//// ��ں���main
//int main()
//{
//	int n;
//	//scanf("%d", &n);
//	scanf_s("%d", &n);
//	for (int i = 0; i < n; i++)
//	{
//		char input[200];
//		int m;
//		//scanf("%d", &m);
//		//scanf("%s", &input);
//		scanf_s("%s", &input, 200);
//		scanf_s("%d", &m);
//		Word *word = (Word *)malloc(sizeof(Word));
//		initialWord(input, word);
//		solveProblem(word, m);
//	}
//	return 0;
//}