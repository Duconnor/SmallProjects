// 文件的输出和输入

#include <cstdio>
#include <cstdlib>

#define PROGRAM 4 // define 的格式！！！

#if PROGRAM == 1

// write file

int main()
{
	FILE* file;
	errno_t err;
	err = fopen_s(&file, "StudentInformation.text", "w");
	if (err != 0)
	{
		printf("Error opening file\n");
		exit(-1);
	}
	char id[11], name[9];
	int courseNumber, score;
	printf("please input the id, name, number of course and score, end with E:\n");
	scanf_s("%s", id, 11);
	while (id[0] != 'E')
	{
		scanf_s("%s", name, 9);
		scanf_s("%d", &courseNumber);
		fprintf(file, "%s %s %d ", id, name, courseNumber);
		for (int i = 0; i < courseNumber; i++)
		{
			scanf_s("%d", &score);
			fprintf(file, "%d", score);
		}
		fputc('\n', file);
		scanf_s("%s", id, 9);
	}
	fclose(file);
	return 0;
}

#endif

#if PROGRAM == 2

int main()
{
	FILE* file;
	errno_t err = fopen_s(&file, "StudentInformation.text", "r");
	if (err != 0)
	{
		printf("error openning the file\n");
		exit(-1);
	}
	char id[4][11];
	char name[4][10];
	int numberCourse[4];
	int result[4];
	for (int i = 0; i < 4; i++)
	{
		fscanf_s(file, "%s", id[i], 11);
		fscanf_s(file, "%s", name[i], 10);
		fscanf_s(file, "%d", &numberCourse[i]);
		fscanf_s(file, "%d", &result[i]);
	}
	for (int i = 0; i < 4; i++)
		printf("%s %s %d %d\n", id[i], name[i], numberCourse[i], result[i]);
	fclose(file);
	system("pause");
	return 0;
}

#endif

#if PROGRAM == 3

enum Sex { male, female };

enum Major { MATHEMATICS, PHYSICS, CHEMISTRY, COMPUTER, GEOGRAPHY, ASTRONOMY, ENGLISH, CHINESE, PHILOSOPHY };

struct Student
{
	char id[11];
	char name[9];
	Sex sex;
	Major major;
};

int main()
{
	// first, get students' information from keyboard
	FILE* file;
	errno_t err = fopen_s(&file, "StudentInformation.txt", "wb");
	if (err != 0)
	{
		printf("Error openning the file\n");
		exit(-1);
	}
	printf("please input the student's id, name, sex and major, end with E \n");
	Student st;
	scanf_s("%s", st.id, 11);
	while (st.id[0] != 'E')
	{
		scanf_s("%s", st.name, 9);
		int sSex, sMajor;
		scanf_s("%d", &sSex);
		scanf_s("%d", &sMajor);
		switch (sSex)
		{
		case 1:st.sex = female; break;
		case 0:st.sex = male; break;
		default:exit(-1);
		}
		switch (sMajor)
		{
		case 0: st.major = MATHEMATICS; break;
		case 1: st.major = PHYSICS; break;
		case 2: st.major = CHEMISTRY; break;
		case 3: st.major = COMPUTER; break;
		case 4: st.major = GEOGRAPHY; break;
		case 5: st.major = ASTRONOMY; break;
		case 6: st.major = ENGLISH; break;
		case 7: st.major = CHINESE; break;
		case 8: st.major = PHILOSOPHY; break;
		default:exit(-1);
		}
		fwrite(&st, sizeof(Student), 1, file);
		scanf_s("%s", st.id, 11);
	}
	fclose(file);
	return 0;
}

#endif

#if PROGRAM == 4

// read from binary file

enum Sex { male, female };

enum Major { MATHEMATICS, PHYSICS, CHEMISTRY, COMPUTER, GEOGRAPHY, ASTRONOMY, ENGLISH, CHINESE, PHILOSOPHY };

struct Student
{
	char id[11];
	char name[9];
	Sex sex;
	Major major;
};

int main()
{
	FILE* file;
	errno_t err = fopen_s(&file, "StudentInformation.txt", "rb");
	if (err != 0)
	{
		printf("have trouble openning the file \n");
		exit(-1);
	}
	Student st[2];
	fread(&st, sizeof(Student), 2, file);
	for (int i = 0; i < 2; i++)
	{
		printf("%s %s ", st[i].id, st[i].name);
			switch (st[i].sex)
			{
			case female:printf("female "); break;
			case male:printf("male "); break;
			default:exit(-1);
			}
			switch (st[i].major)
			{
			case MATHEMATICS: printf("MATHEMATICS"); break;
			case PHYSICS: printf("PHYSICS"); break;
			case CHEMISTRY: printf("CHEMISTRY"); break;
			case COMPUTER: printf("COMPUTER"); break;
			case GEOGRAPHY: printf("GEOGRAPHY"); break;
			case ASTRONOMY: printf("ASTRONOMY"); break;
			case ENGLISH: printf("ENGLISH"); break;
			case CHINESE: printf("CHINESE"); break;
			case PHILOSOPHY: printf("PHILOSOPHY"); break;
			default:exit(-1);
			}
			printf("\n");
	}
	//while (!feof(file))
	//{
	//	printf("%s %s ", st.id, st.name);
	//	switch (st.sex)
	//	{
	//	case female:printf("female "); break;
	//	case male:printf("male "); break;
	//	default:exit(-1);
	//	}
	//	switch (st.major)
	//	{
	//	case MATHEMATICS: printf("MATHEMATICS"); break;
	//	case PHYSICS: printf("PHYSICS"); break;
	//	case CHEMISTRY: printf("CHEMISTRY"); break;
	//	case COMPUTER: printf("COMPUTER"); break;
	//	case GEOGRAPHY: printf("GEOGRAPHY"); break;
	//	case ASTRONOMY: printf("ASTRONOMY"); break;
	//	case ENGLISH: printf("ENGLISH"); break;
	//	case CHINESE: printf("CHINESE"); break;
	//	case PHILOSOPHY: printf("PHILOSOPHY"); break;
	//	default:exit(-1);
	//	}
	//	printf("\n");
	//	fread(&st, sizeof(Student), 1, file);
	//}
	getchar();
	return 0;
}

#endif

#if PROGRAM  == 5

// fseek

enum Sex { male, female };

enum Major { MATHEMATICS, PHYSICS, CHEMISTRY, COMPUTER, GEOGRAPHY, ASTRONOMY, ENGLISH, CHINESE, PHILOSOPHY };

struct Student
{
	char id[11];
	char name[9];
	Sex sex;
	Major major;
};

int main()
{
	Student st;
	FILE* file;
	errno_t err = fopen_s(&file, "StudentInformation.txt", "rb");
	if (err != 0)
	{
		printf("have trouble openning file\n");
		exit(-1);
	}
	fseek(file, sizeof(Student), SEEK_SET);
	if(!feof(file))
		fread(&st, sizeof(Student), 1, file);
	printf("%s %s ", st.id, st.name);
	switch (st.sex)
	{
	case female:printf("female "); break;
	case male:printf("male "); break;
	default:exit(-1);
	}
	switch (st.major)
	{
	case MATHEMATICS: printf("MATHEMATICS"); break;
	case PHYSICS: printf("PHYSICS"); break;
	case CHEMISTRY: printf("CHEMISTRY"); break;
	case COMPUTER: printf("COMPUTER"); break;
	case GEOGRAPHY: printf("GEOGRAPHY"); break;
	case ASTRONOMY: printf("ASTRONOMY"); break;
	case ENGLISH: printf("ENGLISH"); break;
	case CHINESE: printf("CHINESE"); break;
	case PHILOSOPHY: printf("PHILOSOPHY"); break;
	default:exit(-1);
	}
	printf("\n");
	getchar();
	return 0;
}

#endif