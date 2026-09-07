// Buoi2.4_Thao tác cơ bản trên tập tin nhị phân.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 8/5/2026
công dụng: Cho trước 1 tập tin INPUT.TXT chứa mảng 1 chiều các số nguyê
           Viết chương trình tạo tập tin OUTPUT.TXT, chứa các số chẵn có trong tập tin ban đầu

*/

#include <iostream>
#include <stdio.h>

using namespace std;

//Khai báo hàm
//1. Đọc dữ liệu từ tập tin, lưu mảng 1 chiều các số nguyên
void docfile(const char fname[], int a[], int& n);
//2. Ghi dữ liệu từ mảng 1 chiều các số nguyên lên tập tin văn bản
void ghifile(const char fname[], int a[], int n);

int main()
{
    int a[100] = { 1,3,5,7,9 };   //Gủa sủ mảng a có sẵn giá trị
    int n = 5;
    int b[100];                   //Mảng chưa có giá trị
    int nb;
    //1. Ghi mảng a lên tập tin VD1.BIN
    ghifile("E:/VD1.BIN", a, n);
    //2. Đọc dữ liệu từ tập tin VD1.BIN bỏ vào mảng b
    //In mảng b ra màn hình
    docfile("E:/VD1.BIN", b, nb);
    for (int i = 0; i < nb; i++)
        cout << b[i] << "  ";
    cout << endl;
    return 0;
}

//1. Đọc dữ liệu từ tập tin, lưu mảng 1 chiều các số nguyên
void docfile(const char fname[], int a[], int& n) {
    FILE* fp;    //Khai báo con trot tập tin
    //1. Mở file đọc
    fopen_s(&fp, fname, "rb");
    if (fp == NULL) {
        cout << "Ko mo duoc tap tin!\n";
        return;  //Vì kiểu trả về là void
    }
    //2. Đọc dữ liệu
    //fscanf_s(fp, "%d", &n);        //Đọc số phân tử
    fread(&n, sizeof(int), 1, fp);   //Đọc số phân tử nhị phân 
    /*for (int i = 0; i < n; i++)
        fscanf_s(fp, "%d", &a[i]);*/
    fread(a, sizeof(int), n, fp);    //Đọc toàn bộ mảng, lưu vào a
    //3. Đóng tập tin 
    fclose(fp);
}


//2. Ghi dữ liệu từ mảng 1 chiều các số nguyên lên tập tin văn bản
void ghifile(const char fname[], int a[], int n)
{
    FILE* fp;    //Khai báo con trot tập tin
    //1. Mở file để ghi
    fopen_s(&fp, fname, "wb");
    if (fp == NULL) {
        cout << "Ko mo duoc tap tin!\n";
        return;  //Vì kiểu trả về là void
    }
    //2. Đọc dữ liệu
    //fprintf(fp, "%d", n);         //ghi số phân tử
    fwrite(&n, sizeof(int), 1, fp); //ghi số phần tử vào tập tin (1 số nguyên)
    /*for (int i = 0; i < n; i++)
        fprintf(fp, "%5d", a[i]);*/
    fwrite(a, sizeof(int), n, fp);
    //3. Đóng tập tin 
    fclose(fp);
}
