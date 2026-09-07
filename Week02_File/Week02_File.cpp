// Week02_File.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Week02_Files.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Author:
ID:
Last updated:
Purpose: Demonstrate the reading and writing operations on text files
using ANSI C
*/

#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX 20

//Function declarations
//1. Input an array
void InputArr(int a[], int n);
//2. Output an array
void OutputArr(int a[], int n);
//3. Write the contents of an array onto a text file
bool WriteArrToFile(const char fname[], int a[], int n);
//4. Read data from a text file into an array
bool ReadArrFromFile(const char fname[], int a[], int& n);
//5. Write matrix to file
bool WriteMatrixToFile(const char fname[], int m[][MAX], int d, int c);
//6. Read matrix from file
bool ReadMatrixFromFile(const char fname[], int m[][MAX], int& d, int& c);

int main()
{
	int a[100], n;
	/*
	cout << "Input number of elements:";
	cin >> n;
	InputArr(a, n);
	if (WriteArrToFile("D:/DATA/2026/ARRAY.TXT", a, n) == true) {
		cout << "Data saved successfully!\n";
	}
	else cout << "Cannot save data!\n";
}*/

	if (ReadArrFromFile("D:/DATA/2026/ARRAY.TXT", a, n) == true)
		OutputArr(a, n);
	else cout << "Cannot read data from file!\n";
}

//1. Input an array
void InputArr(int a[], int n)
{
	for (int i = 0; i < n; i++) {
		cout << "Input element #" << i << ":";
		cin >> a[i];
	}
}
//2. Output an array
void OutputArr(int a[], int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}
//3. Write the contents of an array onto a text file
bool WriteArrToFile(const char fname[], int a[], int n)
{
	//1. Declare a file pointer
	FILE* fp;
	//2. Open the file + check
	//fp = fopen(fname, "wt");
	fopen_s(&fp, fname, "wt");
	if (fp == NULL) return false;			//unable to open the file
	//3. Work with the contents of the file
	fprintf(fp, "%d\n", n);
	for (int i = 0; i < n; i++)
		fprintf(fp, "%d\t", a[i]);
	//4. Close the file
	fclose(fp);
	return true;
}
//4. Read data from a text file into an array
bool ReadArrFromFile(const char fname[], int a[], int& n)
{
	//1. Declare a file pointer
	FILE* fp;
	//2. Open the file + check
	//fp = fopen(fname, "rt");
	fopen_s(&fp, fname, "rt");
	if (fp == NULL) return false;			//unable to open the file
	//3. Work with the contents of the file
	fscanf_s(fp, "%d", &n);					//read number of elements
	for (int i = 0; i < n; i++)
		fscanf_s(fp, "%d", &a[i]);
	//4. Close the file
	fclose(fp);
	return true;
}
//5. Write matrix to file
bool WriteMatrixToFile(const char fname[], int m[][MAX], int d, int c) {
	FILE* fp;
	fprintf(fp, fname, "wt");
	if (fp == NULL) return false;
	fprintf(fp, "%d %d\n", d, c);
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			fprintf(fp, "%d", m[i][j]);
		}
	}
	fclose(fp);
	return true;
}
//6. Read matrix from file
bool ReadMatrixFromFile(const char fname[], int m[][MAX], int& d, int& c) {
	FILE* fp;
	fopen_s(&fp, fname, "rt");
	if (fp = NULL) return false;
	fscanf_s(fp, "%d %d\n", d, c);
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			fscanf_s(fp, "%d", m[i][j]);
		}
	}
	fclose(fp);
	return true;
}
