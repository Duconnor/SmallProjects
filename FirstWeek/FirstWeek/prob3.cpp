//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//
//// 记录我的手牌中每张牌的出现频率
//void countFrequency(char myCards[], int frequency[])
//{
//	// frequency初始化为全0
//	for (unsigned int i = 0; i < strlen(myCards); i++)
//		frequency[myCards[i] - '0']++;
//}
//
//
//// 检查对方的出牌是哪一种类型
//int whatType(char hisCards[])
//{
//	return strlen(hisCards);
//}
//
//
//// 如果是第四种出牌方式，进一步检查是哪一种
//int whatTypeFour(char hisCards[])
//{
//	for (int i = 1; i < 4; i++)
//		if (hisCards[i] != hisCards[0])
//			return 2;
//	return 1;
//}
//
//
//
//// 第一种出牌方式，检查能否压过对方
//int canBeatOne(int frequency[], char hisCards[])
//{
//	int number = hisCards[0] - '0';
//	for (int i = number + 1; i <= 9; i++)
//		if (frequency[i] > 0)
//			// 存在至少一张比对手出的牌更大的牌
//			return 1;
//	return 0;
//}
//
//
//// 第二种出牌方式，检查能否压过对方
//int canBeatTwo(int frequency[], char hisCards[])
//{
//	int number = hisCards[0] - '0';
//	for (int i = number + 1; i <= 9; i++)
//		if (frequency[i] > 1)
//			// 存在至少两张比对手出的牌更大的牌
//			return 1;
//	return 0;
//}
//
//
//// 第三种出牌方式，检查能否压过对方
//int canBeatThree(int frequency[], char hisCards[])
//{
//	int number = hisCards[0] - '0';
//	for (int i = number + 1; i <= 9; i++)
//		if (frequency[i] > 2)
//			// 存在至少三张比对手出的牌更大的牌
//			return 1;
//	return 0;
//}
//
//
//// 第四种出牌方式中的第一种（四张一样->type=1），检查能否压过对方
//int canBeatFourOne(int frequency[], char hisCards[])
//{
//	int number = hisCards[0];
//	for (int i = number + 1; i <= 9; i++)
//		if (frequency[i] > 3)
//			return 1;
//	return 0;
//}
//
//
//// 第四种出牌方式中的第二种（两张一样->type=2），检查能否压过对方
//int canBeatFourTwo(int frequency[], char hisCards[])
//{
//	int firstNumber = hisCards[0] - '0'; // firstNumber是两张中较小的那张
//	for (int i = 1; i < 4; i++)
//		if (hisCards[i] - '0' < firstNumber)
//		{
//			firstNumber = hisCards[i] - '0';
//			break;
//		}
//
//	for (int i = firstNumber + 1; i < 9; i++)
//		if (frequency[i] > 1 && frequency[i + 1] > 1)
//			return 1;
//	return 0;
//}
//
//
//// 第五种出牌方式，检查能否压过对方
//int canBeatFive(int frequency[], char hisCards[])
//{
//	int number = hisCards[0] - '0';
//	for (int i = number + 1; i <= 5; i++)
//		if (frequency[i] > 0 && frequency[i + 1] > 0 && frequency[i + 2] > 0 &&
//			frequency[i + 3] > 0 && frequency[i + 4] > 0)
//			return 1;
//	return 0;
//}
//
//
//// 第六种出牌方式，检查能否压过对方
//int canBeatSix(int frequency[], char hisCards[])
//{
//	int firstNumber = hisCards[0]; // firstNumber表示牌小的那张
//	for (int i = 1; i < 6; i++)
//		if (hisCards[i] - '0' < firstNumber)
//		{
//			firstNumber = hisCards[i] - '0';
//			break;
//		}
//
//	for (int i = firstNumber + 1; i < 9; i++)
//		if (frequency[i] > 2 && frequency[i + 1] > 2)
//			return 1;
//	return 0;
//}
//
//
//// 解决问题！
//void solveProblemThree(char myCards[], char hisCards[])
//{
//	int frequency[10] = { 0 };
//	countFrequency(myCards, frequency);
//	int type = whatType(hisCards), flag = 0; // flag用于表示能否压过
//	switch (type)
//	{
//	case 1:flag = canBeatOne(frequency, hisCards); break;
//	case 2:flag = canBeatTwo(frequency, hisCards); break;
//	case 3:flag = canBeatThree(frequency, hisCards); break;
//	case 4:
//	{
//		int smallerType = whatTypeFour(hisCards);
//		if (smallerType == 1)
//			flag = canBeatFourOne(frequency, hisCards);
//		else
//			flag = canBeatFourTwo(frequency, hisCards);
//	}break;
//	case 5:flag = canBeatFive(frequency, hisCards); break;
//	case 6:flag = canBeatSix(frequency, hisCards); break;
//	default:exit(-1);
//	}
//	if (flag)
//		printf("%s", "YES");
//	else
//		printf("%s", "NO");
//}
//
//
//// 程序入口函数
//int main()
//{
//	int n;
//	scanf_s("%d", &n);
//	char myCards[100], hisCards[100];
//	for (int i = 0; i < n; i++)
//	{
//		scanf_s("%s", myCards, 100);
//		scanf_s("%s", hisCards, 100);
//		solveProblemThree(myCards, hisCards);
//	}
//	return 0;
//}