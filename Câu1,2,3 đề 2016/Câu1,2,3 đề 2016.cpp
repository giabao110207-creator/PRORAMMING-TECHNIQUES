// Câu1,2,3 đề 2016.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 26/05/2026
Công dụng: Câu 1,2,3 đề 2016
*/

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

void docfile(char* filename, int** M, int& N) {
    ifstream fin(filename);

    fin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> M[i][j];
        }
    }

    fin.close();
}

int mthinhthoi(int** M, int N) {

    // N phải là số lẻ
    if (N % 2 == 0) {
        return 0;
    }

    int mid = N / 2;

    for (int i = 0; i < N; i++) {

        int left = abs(mid - i);
        int right = N - left - 1;

        for (int j = 0; j < N; j++) {

            // Nằm trong hình thoi
            if (j >= left && j <= right) {

                // phải khác 0
                if (M[i][j] == 0) {
                    return 0;
                }
            }
            else {

                // ngoài hình thoi phải bằng 0
                if (M[i][j] != 0) {
                    return 0;
                }
            }
        }
    }

    return 1;
}

int tongcanh(int** M, int N) {

    int tong = 0;
    int mid = N / 2;

    for (int i = 0; i < N; i++) {

        int left = abs(mid - i);
        int right = N - left - 1;

        // cạnh trái
        tong += M[i][left];

        // cạnh phải
        if (left != right) {
            tong += M[i][right];
        }
    }

    return tong;
}

int main() {

    int N;

    int** M = new int* [20];

    for (int i = 0; i < 20; i++) {
        M[i] = new int[20];
    }

    docfile((char*)"INPUT.TXT", M, N);

    if (mthinhthoi(M, N) == 1) {
        cout << "La ma tran hinh thoi\n";
        cout << "Tong cac phan tu tren 4 canh: ";
        cout << tongcanh(M, N);
    }
    else {
        cout << "Khong phai ma tran hinh thoi";
    }

    for (int i = 0; i < 20; i++) {
        delete[] M[i];
    }

    delete[] M;

    return 0;
}

