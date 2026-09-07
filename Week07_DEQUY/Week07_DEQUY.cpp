// Week07_DEQUY.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

//Đệ quy
//1. Tính tổng các phần tử trong mảng 1 chiều 
int tongmang(int a[], int n) {
    if (n <= 0) return 0;      //Suy biến, đặc biệt, đơn giản
    return tongmang(a, n - 1) + a[n - 1];
}
//2. Tính tổng các phần tử trong mảng chẵn
int tongchan(int a[], int n) {
    if (n <= 0) return 0;      //suy biến 
    //int tc = tongchan(a, n - 1);    //Gọi đệ quy để tính tc của mảng con 
    //if (a[n - 1] % 2 == 0) return tc + a[n - 1];
    //return tc; 
    if (a[n - 1] % 2 == 0) return a[n - 1] + tongchan(a, n - 1);
    return tongchan(a, n - 1);
}