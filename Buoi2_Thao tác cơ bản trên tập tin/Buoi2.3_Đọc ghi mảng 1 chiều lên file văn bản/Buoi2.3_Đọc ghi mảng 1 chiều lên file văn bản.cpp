// Buoi2.3_Đọc ghi mảng 1 chiều lên file văn bản.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 8/5/2026
Công dụng: Cho trước 1 tập tin INPUT.TXT chứa mảng 1 chiều các số nguyê
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
//3. Tạo mảng gồm các số chẵn lấy từ mảng ban đầu
void tachchan(int a[], int n, int mc[], int &nc);

int main()
{
    int a[100], mc[100];   //Mảng gốc , mảng chẵn
    int n, nc;             //số phần tử tương ứng
    docfile("E:/INPUT.TXT", a, n);    //Đổ dữ liệu từ file INPUT vào mảng a 
    tachchan(a, n, mc, nc);           //Tách các số chẵn cho vào mc
 ghifile("E:/OUTPUT.TXT", mc, nc); //Đổ dữ từ mảng mc chẵn lên tập tin output

   return 0;
}
  


//1. Đọc dữ liệu từ tập tin, lưu mảng 1 chiều các số nguyên
void docfile(const char fname[], int a[], int& n){
    FILE* fp;    //Khai báo con trot tập tin
    //1. Mở file đọc
    fopen_s(&fp, fname, "rt");
    if (fp == NULL) {
        cout << "Ko mo duoc tap tin!\n";
        return;  //Vì kiểu trả về là void
    }
    //2. Đọc dữ liệu
    fscanf_s(fp, "%d", &n);        //Đọc số phân tử
    for (int i = 0; i < n; i++)
        fscanf_s(fp, "%d", &a[i]);
    //3. Đóng tập tin 
    fclose(fp);
}


//2. Ghi dữ liệu từ mảng 1 chiều các số nguyên lên tập tin văn bản
void ghifile(const char fname[], int a[], int n)
{
    FILE* fp;    //Khai báo con trot tập tin
    //1. Mở file để ghi
    fopen_s(&fp, fname, "wt");
    if (fp == NULL) {
        cout << "Ko mo duoc tap tin!\n";
        return;  //Vì kiểu trả về là void
    }
    //2. Đọc dữ liệu
    fprintf(fp, "%d", n);        //ghi số phân tử
    for (int i = 0; i < n; i++)
        fprintf(fp, "%5d", a[i]);
    //3. Đóng tập tin 
    fclose(fp);
}

//3. Tạo mảng gồm các số chẵn lấy từ mảng ban đầu
void tachchan(int a[], int n, int mc[], int& nc) {
    nc = 0;            //Ban đầu mảng chẵn rỗng 
    for (int i = 0; i < n; i++)
        if (a[i] % 2 == 0)
            mc[nc++] = a[i];     //Thêm a[i] vào cuối mảng mc, tăng nc lên
}