//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//
//typedef struct stringWord
//{
//	char string[200];
//	char vowel[200]; // 字符串中所有元音字母按从左到右的出现顺序构成的数组
//	int vowelPosition[200]; // 用于存储字符串中元音的位置，从左到右依次存储（第一个位置为0）
//	int count; // 多少个元音字母
//}Word;
//
//// 检测该字母是不是元音字母
//int isVowel(char s)
//{
//	if (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u')
//		return 1;
//	return 0;
//}
//
//// 初始化Word，找到其中所有的元音字母并记录其位置
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
//			// 如果是元音的话（即函数返回值为1）
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
//// 对数组中的元素进行循环右移m位的处理
//void moveRight(char string[] , int m)
//{
//	int length = strlen(string);
//
//	// 按照每个元素右移后的新位置将其放在辅助数组aux中
//	char *aux = (char *)malloc(length * sizeof(char));
//	for (int i = 0; i < length; i++)
//	{
//		int newPosition = (i + m) % length;
//		aux[newPosition] = string[i];
//	}
//
//	// 将辅助数组中的元素拷贝回去
//	for (int i = 0; i < length; i++)
//		string[i] = aux[i];
//}
//
//
//// 解决问题
//void solveProblem(Word *word, int m)
//{
//	// 先只看元音字母，进行右移
//	moveRight(word->vowel, m);
//
//	// 按照新的元音字母顺序，更改字符串中的元音字母顺序
//	for (int i = 0; i < word->count; i++)
//		word->string[word->vowelPosition[i]] = word->vowel[i];
//
//	printf("%s\n", word->string);
//}
//
//
//// 入口函数main
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