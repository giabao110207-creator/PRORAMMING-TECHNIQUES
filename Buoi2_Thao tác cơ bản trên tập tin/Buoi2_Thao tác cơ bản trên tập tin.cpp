// Buoi2_Thao tác cơ bản trên tập tin.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 8/5/2026
Công dụng: Thao tác cơ bản trên tập tin
*/

#include <iostream>
#include <stdio.h>  //Hàm thao tác trên tập tin
using namespace std;

int main()
{
	//Khai báo và nhập vào 1 mảng số nguyên gồm n phần tử
	 //Lưu nội dung của mảng này lên tập tin văn bản (Trên đĩa)
	int a[100];
	int n;         //Số phân tử
	cout << "Nhap so phan tu:";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Nhap phan tu thu " << i << ":";
		cin >> a[i];
	}
	//Lưu mảng lên tập tin 
	FILE* fp;             //Khai báo con trỏ tập tin
	//Dùng để thao tác trên tập tin
//1. Mở tập tin (để ghi)
	//fp = fopen("E:/OUTPUT.TXT", "wt");     //Mở tập tin văn bản để ghi
	fopen_s(&fp, "E:/OUTPUT.TXT", "wt");     //Dùng cho VS mới
	//1.1 Kiểm tra xem có mở được không
	if (fp == NULL)      //Không mở đượp tập tin
	{
		cout << "Khong  mo duoc tap tin!" << endl;    //Báo lỗi
		return -1;     //Kết thúc
	}
	//2. Mở thành công --> đọc / ghi
	fprintf(fp, "%d\n", n);        //dòng đầu ghi số phần tử 
	//dòng tiếp theo ghi các phần tử của mảng, mỗi phần tử chiếm 5 c hỗ
	for (int i = 0; i < n; i++)
		fprintf(fp, "%5d", a[i]);
	//3. Đóng tập tin lại
	fclose(fp);
	return 0;
}
