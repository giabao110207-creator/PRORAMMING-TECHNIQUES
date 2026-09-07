// Week06_Recursion.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo 
Mssv: 25AD11003
Ngày cập nhật: 2/6/2026
Công dụng: đệ quy 
*/
#include <iostream>
using namespace std;

//Example #1: Factorial function
// N! = 1.2.3....(N-1).N
//Second way: recursive
// N! = 1 if N<=1
// N! = N.(N-1)! if N>1
//1st way: no recursion!
long Factorial(int n)
{
	long F = 1;
	for (int i = 1; i <= n; i++)
		F = F * i;
	return F;
}
//2nd way: with recursion
long Factorial2(int n)
{
	if (n <= 1) return 1;
	return n * Factorial2(n - 1);
}
//Example #2: The Fibonacci string
//1 1 2 3 5 8 13 21 34 55 89 etc.
long Fibonacci(int n)
{
	if (n <= 2) return 1;		//first 2 elements
	return Fibonacci(n - 2) + Fibonacci(n - 1);
}

//Example #3: Array as a recursive structure
//3.1 Summing all elements of the array
int SumArray(int a[], int n)
{
	if (n <= 0) return 0;		//no elements --> sum is zero
	return SumArray(a, n - 1) + a[n - 1];
}
//3.2 Summing all even elements of the array
int SumEvenInArray(int a[], int n)
{
	if (n <= 0) return 0;
	if (a[n - 1] % 2 != 0) return SumEvenInArray(a, n - 1);
	return SumEvenInArray(a, n - 1) + a[n - 1];
}
//Search if the value x appears in the array or not
//If not, function returns -1
//Else returns the last position of that value
int Search(int a[], int n, int x)
{
	if (n <= 0) return -1;					//cannot find x in an empty array
	if (a[n - 1] == x) return n - 1;		//find x at the end of the array
	return Search(a, n - 1, x);				//try to search for x in the small array
}

//3.3 Finding the maximum value in an array
//Condition: n > 0
int FindMax(int a[], int n)
{
	if (n < 1) return 0;					//error!
	if (n == 1) return a[0];				//array with 1 element only
	int t = FindMax(a, n - 1);				//finding max of the sub array
	if (t > a[n - 1]) return t;
	return a[n - 1];
}

//3.4 Printing out the array in reverse order
void PrintArray(int a[], int n) {
	if (n > 0) {
		cout << a[n - 1] << "  ";		//print last element
		PrintArray(a, n - 1);
	}
}
//3.5 Printing out the array in normal order
void PrintArray2(int a[], int n) {
	if (n > 0) {
		PrintArray2(a, n - 1);
		cout << a[n - 1] << "  ";		//print last element
	}
}
//3.6 Input values for the array in normal order
void InputArray(int a[], int n) {
	if (n > 0) {
		InputArray(a, n - 1);
		cout << "Input element #" << n - 1 << ":";
		cin >> a[n - 1];
	}
}
//3.7 Finding the maximum odd number in the array (if any)
//If there is no odd number, returns 0
int FindMaxOdd(int a[], int n);
//3.8 Check if the array is is ascending order or not
bool IsAscending(int a[], int n);
//3.9 Sort the array increasingly, using InsertionSort
void InsertLast(int a[], int n);
//3.10 Checking if all the elements in the array is non-negative
bool AllNonNegative(int a[], int n);
//3.11 Find the MCD (Most Common Divident) of 2 integers (4 ways - 2 recursive)
int GCD_Iter(int a, int b);
int GCD_Iter2(int a, int b);
int GCD_Rec(int a, int b);
int GCD_Rec2(int a, int b);
//3.12 Check if a positive integer is a prime number or not
bool IsPrimeHelper(int n, int d);
//3.13 Kiểm tra mảng tăng giảm xen kẽ
bool IsAlternating(int a[], int n);
//3.14 Kiểm tra mảng âm dương xen kẽ
bool IsAltNegPos(int a[], int n);
//3.15 Kiểm tra mảng đối xứng
bool IsPalindrome(int a[], int left, int right);

//VD về chuỗi, đệ quy
//1. Tính tổng các ký tự số có trong chuỗi 
int tongktso(char s[]);

int main()
{
	int a[] = { 3,2,5,8,1,3,7,9 };
	int n = 8;
	InputArray(a, n);
	cout << SumArray(a, n) << endl;
	cout << SumEvenInArray(a, n) << endl;
	int p = Search(a, n, 3);				//search for value 6 in the array
	if (p == -1) cout << "Cannot find value 3!" << endl;
	else cout << "Found value 3 at " << p << endl;
	cout << "Maximum value = " << FindMax(a, n) << endl;
	PrintArray(a, n);
	cout << endl;
	PrintArray2(a, n);
	cout << endl;
	//cout << Factorial(5) << endl;
	//cout << Factorial2(5) << endl;
	return 0;
}

//VD về chuỗi, đệ quy
//1. Tính tổng các ký tự số có trong chuỗi 
//s = "12A1"
int tongktso(char s[]) {
	if (s[0] == NULL) return 0;   //if (!s[0])
	if (isdigit(s[0])) return tongktso(s + 1) + (s[0] - 48);
	return tongktso(s + 1);
}

//3.7 Finding the maximum odd number in the array (if any)
//If there is no odd number, returns 0
int FindMaxOdd(int a[], int n)
{
    if (n <= 0) return 0;                          // no odd number found
    int t = FindMaxOdd(a, n - 1);                  // max odd of sub array
    if (a[n - 1] % 2 == 0) return t;              // even number, skip
    if (t == 0) return a[n - 1];                   // first odd found
    return (a[n - 1] > t) ? a[n - 1] : t;         // return bigger odd
}

//3.8 Check if the array is in ascending order or not
bool IsAscending(int a[], int n)
{
    if (n <= 1) return true;                        // 0 or 1 element → always ascending
    if (a[n - 2] > a[n - 1]) return false;         // violation found
    return IsAscending(a, n - 1);
}

//3.9 Sort the array increasingly using InsertionSort (recursive)
void InsertLast(int a[], int n)
{
    // Insert a[n-1] into the correct position in sorted a[0..n-2]
    if (n <= 1) return;
    if (a[n - 2] <= a[n - 1]) return;             // already in place
    swap(a[n - 2], a[n - 1]);
    InsertLast(a, n - 1);
}
void InsertionSort(int a[], int n)
{
    if (n <= 1) return;
    InsertionSort(a, n - 1);                        // sort first n-1 elements
    InsertLast(a, n);                               // insert a[n-1] into sorted part
}

//3.10 Checking if all the elements in the array are non-negative
bool AllNonNegative(int a[], int n)
{
    if (n <= 0) return true;                        // empty array → true
    if (a[n - 1] < 0) return false;               // found a negative element
    return AllNonNegative(a, n - 1);
}

//3.11 Find the GCD (Greatest Common Divisor) of 2 integers
// Way 1: iterative (subtraction-based)
int GCD_Iter(int a, int b)
{
    while (a != b) {
        if (a > b) a -= b;
        else b -= a;
    }
    return a;
}
// Way 2: iterative (modulo-based)
int GCD_Iter2(int a, int b)
{
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
// Way 3: recursive (subtraction-based)
int GCD_Rec(int a, int b)
{
    if (a == b) return a;
    if (a > b) return GCD_Rec(a - b, b);
    return GCD_Rec(a, b - a);
}
// Way 4: recursive (modulo-based / Euclid)
int GCD_Rec2(int a, int b)
{
    if (b == 0) return a;
    return GCD_Rec2(b, a % b);
}

//3.12 Check if a positive integer is a prime number or not
// Helper: check divisibility from divisor d up to sqrt(n)
bool IsPrimeHelper(int n, int d)
{
    if (d * d > n) return true;                    // no divisor found → prime
    if (n % d == 0) return false;                  // divisible → not prime
    return IsPrimeHelper(n, d + 1);
}
bool IsPrime(int n)
{
    if (n < 2) return false;
    return IsPrimeHelper(n, 2);
}

//3.13 Kiểm tra mảng tăng giảm xen kẽ
// (alternating up-down: a[0]<a[1]>a[2]<a[3]...)
bool IsAlternating(int a[], int n)
{
    if (n <= 2) return true;
    // Check the relationship between the last two pairs
    bool lastShouldBeGreater = (n % 2 == 0);      // a[n-2] > a[n-1] when n is even
    if (lastShouldBeGreater && a[n - 2] <= a[n - 1]) return false;
    if (!lastShouldBeGreater && a[n - 2] >= a[n - 1]) return false;
    return IsAlternating(a, n - 1);
}

//3.14 Kiểm tra mảng âm dương xen kẽ
// (alternating negative-positive or positive-negative)
bool IsAltNegPos(int a[], int n)
{
    if (n <= 1) return true;
    // Adjacent elements must have opposite signs
    if ((a[n - 2] >= 0 && a[n - 1] >= 0) ||
        (a[n - 2] < 0 && a[n - 1] < 0)) return false;
    return IsAltNegPos(a, n - 1);
}

//3.15 Kiểm tra mảng đối xứng (palindrome)
bool IsPalindrome(int a[], int left, int right)
{
    if (left >= right) return true;                // crossed or met → symmetric
    if (a[left] != a[right]) return false;
    return IsPalindrome(a, left + 1, right - 1);
}
// Wrapper for convenient calling: IsPalindrome(a, n)
bool IsPalindrome(int a[], int n)
{
    return IsPalindrome(a, 0, n - 1);
}