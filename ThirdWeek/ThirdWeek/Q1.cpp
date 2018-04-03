#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#define PROGRAM 1 // 1 for normal, 2 for reading from binary file

const int DATASIZE = 178;
const int PROPERTYSIZE = 14;

// read all the data from the file, return false if failed
void readFromFile(double  **data)
{
	FILE* file;
	errno_t err = fopen_s(&file, "wine.txt", "r");
	if (err != 0)
	{
		printf("have trouble opening the file\n");
		exit(-1);
	}
	for (int i = 0; i < DATASIZE; i++)
	{
		fscanf_s(file, "%lf", &data[i][0]);

		// first, read from file

		char *temp = new char[10000];
		fscanf_s(file, "%s", temp, 10000);

		// split the string by ","
		
		char* buffer = NULL;
		char* p;
		p = strtok_s(temp, ",", &buffer);

		int j = 1; // j indicates the next position of the attribute array that we are going to deal with
		while (p != NULL)
		{
			if (p[0] == '#')
				data[i][j] = -1; // missing value is indicated by flag value -1
			else
				data[i][j] = strtod(p, NULL);
			j++;
			p = strtok_s(NULL, ",", &buffer);
		}
	}
	fclose(file);
}

// process missing value
void processData(double **data)
{
	double fixData[13] = { 0.0 }; // fixData stores all the average value that has been calculated
	for (int i = 0; i < DATASIZE; i++)
	{
		for (int j = 1; j < PROPERTYSIZE; j++)
		{
			if (data[i][j] == -1)
			{
				if (fixData[j - 1] != 0)
				{
					// if the average value of this column has been calculated before
					data[i][j] = fixData[j - 1];
					continue;
				}

				// the average value has not been calculated before
				// calculate the average value

				double sum = 0.0, count = 0.0; // count is the number of values that is not missing in this column
				for (int k = 0; k < DATASIZE; k++)
				{
					if (k == i || data[k][j] == -1)
						continue;
					sum += data[k][j];
					count++;
				}
				// now we get the sum of all other values
				double average = sum / count;
				data[i][j] = average;
				fixData[j - 1] = average; // put the average value in the array
			}
		}
	}
}

// keep only one digits after decimal point
void rounding(double **data)
{
	for (int i = 0; i<DATASIZE; i++)
		for (int j = 0; j < PROPERTYSIZE; j++)
		{
			data[i][j] = (long)(data[i][j] * 10 + 0.5);
			data[i][j] /= 10.0;
		}
}


// write data back to a binary file
void writeToBinary(double **data)
{
	FILE* file;
	errno_t err = fopen_s(&file, "wine_cpl.dat", "wb");
	if (err != 0)
	{
		printf("have trouble opening the file\n");
		exit(-1);
	}

	char s[2] = ",";
	char end[3] = "\n";
	for (int i = 0; i < DATASIZE; i++)
		for (int j = 0; j < PROPERTYSIZE; j++)
		{
			fwrite(&data[i][j], sizeof(double), 1, file);
			if (j != 13)
				fwrite(s, sizeof(char) * 2, 1, file);
			else
				fwrite(end, sizeof(char) * 3, 1, file);
		}

	fclose(file);
}


// write data back to text file
void writeToText(double **data)
{
	FILE* file;
	errno_t err = fopen_s(&file, "wine_norm.csv", "w");
	if (err != 0)
	{
		printf("have trouble opening the file\n");
		exit(-1);
	}

	for (int i = 0; i < DATASIZE; i++)
		for (int j = 0; j < PROPERTYSIZE; j++)
		{
			fprintf(file, "%0.1lf", data[i][j]);
			if (j != PROPERTYSIZE - 1)
				fprintf(file, ",");
			else
				fprintf(file, "\n");
		}

	fclose(file);
}


// test unit (for debug purpose)
// read from binary file
void readBinaryTest()
{
	FILE* file;
	errno_t err = fopen_s(&file, "wine_cpl.dat", "rb");
	if (err != 0)
	{
		printf("have trouble opening the file\n");
		exit(-1);
	}

	for(int i=0;i<DATASIZE;i++)
		for (int j = 0; j < PROPERTYSIZE; j++)
		{
			double data;
			char s[2], end[3];
			fread(&data, sizeof(double), 1, file);
			printf("%0.1lf", data);
			if (j != PROPERTYSIZE - 1)
			{
				fread(s, sizeof(char) * 2, 1, file);
				printf("%s", s);
			}
			else
			{
				fread(end, sizeof(char) * 3, 1, file);
				printf("%s", end);
			}
		}
	fclose(file);
}

// normalization
void normalizationData(double **data)
{
	double max[13]; // store the max value of each column
	double min[13];
	for (int i = 0; i < 13; i++)
	{
		max[i] = DBL_TRUE_MIN;
		min[i] = DBL_MAX;
	}

	// find the max and min of each column
	for(int i=0;i<DATASIZE;i++)
		for (int j = 1; j < PROPERTYSIZE; j++)
		{
			if (data[i][j] > max[j - 1])
				max[j - 1] = data[i][j];
			if (data[i][j] < min[j - 1])
				min[j - 1] = data[i][j];
		}

	// normalized the data
	for(int i=0;i<DATASIZE;i++)
		for (int j = 1; j < PROPERTYSIZE; j++)
		{
			if (min[j - 1] != max[j - 1])
				data[i][j] = (data[i][j] - min[j - 1]) / (max[j - 1] - min[j - 1]);
			else
				data[i][j] = 1;
		}
}


// solve problem
void solver(double **data)
{
	readFromFile(data);
	processData(data);
	rounding(data);
	writeToBinary(data);
	readFromFile(data);
	processData(data);
	normalizationData(data);
	rounding(data);
	writeToText(data);
}

#if PROGRAM == 1
int main()
{
	double **data = new double*[200];
	for (int i = 0; i < 200; i++)
		data[i] = new double[100];
	solver(data);
	system("pause");
	return 0;
}
#endif

#if PROGRAM == 2
int main()
{
	readBinaryTest();
	system("pause");
	return 0;
}
#endif