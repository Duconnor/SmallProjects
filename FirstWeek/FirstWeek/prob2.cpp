//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//// 位数过多，必须使用数组来表示小数
//
//
//// 求小数点后的数字位数
//int findDigitsAfterDecimal(char number[])
//{
//	int length = strlen(number), count = 0, flag = 0;
//	for (int i = 0; i < length; i++)
//	{
//		if (!flag)
//		{
//			if (number[i] == '.')
//				flag = 1;
//			continue;
//		}
//		count++;
//	}
//	return count;
//}
//
//
//// 利用char型变量进行加法
//char twoCharPlus(char c1, char c2, int *flag)
//{
//	int sum = (c1 - '0') + (c2 - '0');
//	if (*flag)
//	{
//		// 如果上一位的运算进位了
//		sum++;
//		*flag = 0;
//	}
//	if (sum > 9)
//	{
//		// 这一位的运算需要进位
//		*flag = 1;
//		sum %= 10;
//	}
//	return sum + '0';
//}
//
//char oneCharPlus(char c, int *flag)
//{
//	int sum = c - '0';
//	if (*flag)
//	{
//		// 如果上一位的运算进位了
//		sum++;
//		*flag = 0;
//	}
//	if (sum > 9)
//	{
//		// 这一位的运算需要进位
//		*flag = 1;
//		sum %= 10;
//	}
//	return sum + '0';
//}
//
//
//void numberPlus(char number1[], char number2[], char result[])
//{
//	// 参数中number1小数点后的位数大于等于number2的
//
//	char aux[1000]; // 辅助数组，用于暂存结果
//	int digitsAfterDecimal1 = findDigitsAfterDecimal(number1);
//	int digitsAfterDecimal2 = findDigitsAfterDecimal(number2);
//	int length1 = strlen(number1), length2 = strlen(number2);
//	int digitsBeforeDecimal1 = length1 - digitsAfterDecimal1;
//	int digitsBeforeDecimal2 = length2 - digitsAfterDecimal2;
//	if (digitsAfterDecimal2 != 0)
//		digitsBeforeDecimal2--; // 如果有小数点的话，减掉小数点那一位
//	if (digitsAfterDecimal1 != 0)
//		digitsBeforeDecimal1--;
//	int lengthOfAnswer = 0;
//
//	// 确定答案的长度
//	if (digitsBeforeDecimal1 > digitsBeforeDecimal2)
//		lengthOfAnswer = digitsBeforeDecimal1 + digitsAfterDecimal1;
//	else
//		lengthOfAnswer = digitsBeforeDecimal2 + digitsAfterDecimal1;
//	if (digitsAfterDecimal1 != 0 || digitsAfterDecimal2 != 0)
//		// 如果输入中存在小数，那么则为最终答案加上小数点要占的那一位
//		lengthOfAnswer++;
//
//	aux[lengthOfAnswer] = '\0';
//	int count1 = 0, count2 = 0; // count1代表number1中已经有多少位参加了运算，count2代表number2中有多少位参加了运算
//	int isCarry = 0; // carry用于表示这一位的运算有没有进位
//	int *flag = &isCarry; // flag使得函数可以更改isCarry的值
//
//	// 计算开始
//	for (int i = lengthOfAnswer - 1; i >= 0; i--)
//	{
//
//		if (count1 < digitsAfterDecimal1 - digitsAfterDecimal2)
//		{
//			// 此时number1中的数可以直接copy进aux中，因为对应的number2中这些位均为0
//			aux[i] = number1[length1 - 1 - count1];
//			count1++;
//			continue;
//		}
//
//		// 先检查有没有到小数点，如果到了就直接加进aux中
//		if (digitsAfterDecimal1!=0&&number1[length1 - 1 - count1] == '.')
//		{
//			aux[i] = '.';
//			count1++;
//			if(digitsAfterDecimal2!=0)
//				count2++;
//			continue;
//		}
//
//		// 当number1和number2中都有数字时，来自number1和number2的两个数相加
//		if (count1 < length1&&count2 < length2)
//		{
//			char sum = twoCharPlus(number1[length1 - 1 - count1], number2[length2 - 1 - count2], flag);
//			aux[i] = sum;
//			count1++;
//			count2++;
//			continue;
//		}
//
//		// 当number1中的数字没有了，直接将number2中的拷贝过去即可
//		if (count1 >= length1&&count2 < length2)
//		{
//			char sum = oneCharPlus(number2[length2 - 1 - count2], flag);
//			aux[i] = sum;
//			count2++;
//		}
//		// number2中的数字没有了则同理
//		else
//		{
//			char sum = oneCharPlus(number1[length1 - 1 - count1], flag);
//			aux[i] = sum;
//			count1++;
//		}
//	}
//
//	if (*flag)
//		// 仍然有进位，结果会比aux多一位
//		result[0] = '1';
//	for (int i = 1; i <= lengthOfAnswer + 1; i++)
//		result[i] = aux[i - 1];
//}
//
//
//// 程序的入口函数
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	char number1[1000], number2[1000], result[1000];
//	for (int i = 0; i < n; i++)
//	{
//		result[0] = 'n'; // 特殊标识符
//		scanf("%s%s", number1, number2);
//		if (findDigitsAfterDecimal(number1) > findDigitsAfterDecimal(number2))
//			numberPlus(number1, number2, result);
//		else
//			numberPlus(number2, number1, result);
//		int length = strlen(result);
//		// 该算法的结果末位可能出现0，现对其进行处理
//		int count = 0; // count计数末尾有多少个0
//		for (int k = length - 1; k >= 0; k--)
//		{
//			if (result[k] == '0')
//				count++;
//			else
//				break;
//		}
//		int j = 0;
//		if (result[0] == 'n')
//			j++;
//		for (; j<length - count; j++)
//			printf("%c", result[j]);
//		printf("\n");
//	}
//	system("pause");
//	return 0;
//}
