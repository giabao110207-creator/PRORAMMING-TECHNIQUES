// Week10_Chiadetri.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

//VD1: Tìm kiếm giá trị x trong mảng 
int LinearSearch(int a[], int n, int x) {
    int i = 0;       //xp từ đầu mảng
    while (i < n && a[i] != x)i++;
    if (i >= n) return -1;       //ko tìm thấy x trong mảng 
    return i;                    //vị trí đầu tiên bằng x
}
//Tìm kiếm nhị phân trên mảng tăng, dùng đệ quy 
int BinarySearch1(int a[], int left, int right, int x) {
    if (left > right) return -1;     //ko có x
    int mid = (left + right) / 2;    //tính trung điểm 
        if (x == a[mid])
            return mid;                    //tìm thấy 
        else if (x < a[mid]) return BinarySearch1(a, left, mid - 1, x);  //tìm bên trái 
        else return BinarySearch1(a, mid + 1, right, x);  //tìm bên phải 
}

//Tạo vỏ ngoài giống LinearSearch
    int BSearch1(int a[], int n, int x) {
        return BinarySearch1(a, 0, n - 1, x);
    }
//Cách 2: ko dùng đệ quy
    int BSearch2(int a[], int n, int x){
        int left = 0;int  right = n - 1;
        while (left <=right) {
            int mid = (left + right) / 2;
            if (x == a[mid]) return mid;
            else if (x < a[mid]) right = mid - 1;
        }
        return -1;     //ko tìm thấy x
    }
//Hàm tìm nhị phân trên mảng có thứ tự giảm 

//VD2: MergeSort

//VD3: Partition
int main()
{
    int a[10] = { 1,3,3,5,6,8,9,9 };
    int n = 8; 
    cout << LinearSearch(a, n, 6) << endl;
    cout << BSearch1(a, n, 6) << endl;
    cout << BSearch2(a, n, 6) << endl;
}


