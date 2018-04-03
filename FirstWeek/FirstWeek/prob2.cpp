//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//
//// λ�����࣬����ʹ����������ʾС��
//
//
//// ��С����������λ��
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
//// ����char�ͱ������мӷ�
//char twoCharPlus(char c1, char c2, int *flag)
//{
//	int sum = (c1 - '0') + (c2 - '0');
//	if (*flag)
//	{
//		// �����һλ�������λ��
//		sum++;
//		*flag = 0;
//	}
//	if (sum > 9)
//	{
//		// ��һλ��������Ҫ��λ
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
//		// �����һλ�������λ��
//		sum++;
//		*flag = 0;
//	}
//	if (sum > 9)
//	{
//		// ��һλ��������Ҫ��λ
//		*flag = 1;
//		sum %= 10;
//	}
//	return sum + '0';
//}
//
//
//void numberPlus(char number1[], char number2[], char result[])
//{
//	// ������number1С������λ�����ڵ���number2��
//
//	char aux[1000]; // �������飬�����ݴ���
//	int digitsAfterDecimal1 = findDigitsAfterDecimal(number1);
//	int digitsAfterDecimal2 = findDigitsAfterDecimal(number2);
//	int length1 = strlen(number1), length2 = strlen(number2);
//	int digitsBeforeDecimal1 = length1 - digitsAfterDecimal1;
//	int digitsBeforeDecimal2 = length2 - digitsAfterDecimal2;
//	if (digitsAfterDecimal2 != 0)
//		digitsBeforeDecimal2--; // �����С����Ļ�������С������һλ
//	if (digitsAfterDecimal1 != 0)
//		digitsBeforeDecimal1--;
//	int lengthOfAnswer = 0;
//
//	// ȷ���𰸵ĳ���
//	if (digitsBeforeDecimal1 > digitsBeforeDecimal2)
//		lengthOfAnswer = digitsBeforeDecimal1 + digitsAfterDecimal1;
//	else
//		lengthOfAnswer = digitsBeforeDecimal2 + digitsAfterDecimal1;
//	if (digitsAfterDecimal1 != 0 || digitsAfterDecimal2 != 0)
//		// ��������д���С������ô��Ϊ���մ𰸼���С����Ҫռ����һλ
//		lengthOfAnswer++;
//
//	aux[lengthOfAnswer] = '\0';
//	int count1 = 0, count2 = 0; // count1����number1���Ѿ��ж���λ�μ������㣬count2����number2���ж���λ�μ�������
//	int isCarry = 0; // carry���ڱ�ʾ��һλ��������û�н�λ
//	int *flag = &isCarry; // flagʹ�ú������Ը���isCarry��ֵ
//
//	// ���㿪ʼ
//	for (int i = lengthOfAnswer - 1; i >= 0; i--)
//	{
//
//		if (count1 < digitsAfterDecimal1 - digitsAfterDecimal2)
//		{
//			// ��ʱnumber1�е�������ֱ��copy��aux�У���Ϊ��Ӧ��number2����Щλ��Ϊ0
//			aux[i] = number1[length1 - 1 - count1];
//			count1++;
//			continue;
//		}
//
//		// �ȼ����û�е�С���㣬������˾�ֱ�Ӽӽ�aux��
//		if (digitsAfterDecimal1!=0&&number1[length1 - 1 - count1] == '.')
//		{
//			aux[i] = '.';
//			count1++;
//			if(digitsAfterDecimal2!=0)
//				count2++;
//			continue;
//		}
//
//		// ��number1��number2�ж�������ʱ������number1��number2�����������
//		if (count1 < length1&&count2 < length2)
//		{
//			char sum = twoCharPlus(number1[length1 - 1 - count1], number2[length2 - 1 - count2], flag);
//			aux[i] = sum;
//			count1++;
//			count2++;
//			continue;
//		}
//
//		// ��number1�е�����û���ˣ�ֱ�ӽ�number2�еĿ�����ȥ����
//		if (count1 >= length1&&count2 < length2)
//		{
//			char sum = oneCharPlus(number2[length2 - 1 - count2], flag);
//			aux[i] = sum;
//			count2++;
//		}
//		// number2�е�����û������ͬ��
//		else
//		{
//			char sum = oneCharPlus(number1[length1 - 1 - count1], flag);
//			aux[i] = sum;
//			count1++;
//		}
//	}
//
//	if (*flag)
//		// ��Ȼ�н�λ��������aux��һλ
//		result[0] = '1';
//	for (int i = 1; i <= lengthOfAnswer + 1; i++)
//		result[i] = aux[i - 1];
//}
//
//
//// �������ں���
//int main()
//{
//	int n;
//	scanf("%d", &n);
//	char number1[1000], number2[1000], result[1000];
//	for (int i = 0; i < n; i++)
//	{
//		result[0] = 'n'; // �����ʶ��
//		scanf("%s%s", number1, number2);
//		if (findDigitsAfterDecimal(number1) > findDigitsAfterDecimal(number2))
//			numberPlus(number1, number2, result);
//		else
//			numberPlus(number2, number1, result);
//		int length = strlen(result);
//		// ���㷨�Ľ��ĩλ���ܳ���0���ֶ�����д���
//		int count = 0; // count����ĩβ�ж��ٸ�0
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
