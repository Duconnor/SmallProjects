//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//
//// ��¼�ҵ�������ÿ���Ƶĳ���Ƶ��
//void countFrequency(char myCards[], int frequency[])
//{
//	// frequency��ʼ��Ϊȫ0
//	for (unsigned int i = 0; i < strlen(myCards); i++)
//		frequency[myCards[i] - '0']++;
//}
//
//
//// ���Է��ĳ�������һ������
//int whatType(char hisCards[])
//{
//	return strlen(hisCards);
//}
//
//
//// ����ǵ����ֳ��Ʒ�ʽ����һ���������һ��
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
//// ��һ�ֳ��Ʒ�ʽ������ܷ�ѹ���Է�
//int canBeatOne(int frequency[], char hisCards[])
//{
//	int number = hisCards[0] - '0';
//	for (int i = number + 1; i <= 9; i++)
//		if (frequency[i] > 0)
//			// ��������һ�űȶ��ֳ����Ƹ������
//			return 1;
//	return 0;
//}
//
//
//// �ڶ��ֳ��Ʒ�ʽ������ܷ�ѹ���Է�
//int canBeatTwo(int frequency[], char hisCards[])
//{
//	int number = hisCards[0] - '0';
//	for (int i = number + 1; i <= 9; i++)
//		if (frequency[i] > 1)
//			// �����������űȶ��ֳ����Ƹ������
//			return 1;
//	return 0;
//}
//
//
//// �����ֳ��Ʒ�ʽ������ܷ�ѹ���Է�
//int canBeatThree(int frequency[], char hisCards[])
//{
//	int number = hisCards[0] - '0';
//	for (int i = number + 1; i <= 9; i++)
//		if (frequency[i] > 2)
//			// �����������űȶ��ֳ����Ƹ������
//			return 1;
//	return 0;
//}
//
//
//// �����ֳ��Ʒ�ʽ�еĵ�һ�֣�����һ��->type=1��������ܷ�ѹ���Է�
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
//// �����ֳ��Ʒ�ʽ�еĵڶ��֣�����һ��->type=2��������ܷ�ѹ���Է�
//int canBeatFourTwo(int frequency[], char hisCards[])
//{
//	int firstNumber = hisCards[0] - '0'; // firstNumber�������н�С������
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
//// �����ֳ��Ʒ�ʽ������ܷ�ѹ���Է�
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
//// �����ֳ��Ʒ�ʽ������ܷ�ѹ���Է�
//int canBeatSix(int frequency[], char hisCards[])
//{
//	int firstNumber = hisCards[0]; // firstNumber��ʾ��С������
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
//// ������⣡
//void solveProblemThree(char myCards[], char hisCards[])
//{
//	int frequency[10] = { 0 };
//	countFrequency(myCards, frequency);
//	int type = whatType(hisCards), flag = 0; // flag���ڱ�ʾ�ܷ�ѹ��
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
//// ������ں���
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