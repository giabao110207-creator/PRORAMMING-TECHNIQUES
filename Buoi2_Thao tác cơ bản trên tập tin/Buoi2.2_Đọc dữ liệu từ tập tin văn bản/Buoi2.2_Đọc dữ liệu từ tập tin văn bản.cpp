// Buoi2.2_Đọc dữ liệu từ tập tin văn bản.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 8/5/2026
Công dụng: Đọc dữ liệu từ tập tin văn bản
*/

#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    //Đọc dữ liệu từ tập tin OUTPUT.TXT ở chương trình trước
    //Đưa vào mảng 1 chiều và in mảng kết quả ra màn hình
    int a[100];
    int n;
    FILE* fp;   //Con trỏ tập tin
    //1. Mở tập tin để đọc
    fopen_s(&fp, "E:/OUTPUT.TXT", "r");    //Mở tập tin văn bản
    if (fp == NULL) {
        cout << "Ko mo duoc tap tin!\n";
        return -1;
    }

//2. Đọc dữ liệu
    fscanf_s(fp, "%d", &n);   //Đọc số nguyên đầu tiên trong tập tin 
                          //Lưu vào biến n
    for (int i = 0; i < n; i++)
        fscanf_s(fp, "%d", &a[i]);  //Lần lượt đọc từng giá trị tiếp theo

                                    //Lưu vào mảng a
    //3. Đóng tập tin
    fclose(fp);
    //Thao tác trên mảng a --> xuất ra màn hình
    cout << "Mang vua doc duoc:\n";
    for (int i = 0; i < n; i++)
        cout << a[i] << "  ",
        cout << endl;
    return 0;
}