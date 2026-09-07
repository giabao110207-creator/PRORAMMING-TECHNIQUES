// Week12_BaiToanToMau.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Ho va ten: Nguyen Hoang Gia Bao
MSSV: 25ad11003
Ngay cap nhat: 16/06/2026
Cong dung: bai toan to mau
*/

#include <iostream>
#include <cstdio>
using namespace std;

const int MAX = 100;

int a[MAX][MAX];     // ma tran ke
int color[MAX];      // mau cua cac dinh
int n;

// Doc file
bool docfile(const char filename[])
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
    {
        cout << "Khong mo duoc file!\n";
        return false;
    }
    fscanf(fp, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(fp, "%d", &a[i][j]);
        }
    }
    fclose(fp);
    return true;
}

// In ma tran ke
void inMaTran()
{
    cout << "Ma tran ke:\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
// Kiem tra co the to mau cho dinh u khong
bool anToan(int u, int mau)
{
    for (int v = 0; v < n; v++)
    {
        if (a[u][v] == 1 && color[v] == mau)
            return false;
    }
    return true;
}
// Backtracking
bool toMau(int u, int soMau)
{
    if (u == n)
        return true;
    for (int mau = 1; mau <= soMau; mau++)
    {
        if (anToan(u, mau))
        {
            color[u] = mau;
            if (toMau(u + 1, soMau))
               return true;
            color[u] = 0;
        }
    }
    return false;
}

// Tim so mau toi thieu
int timSoMauToiThieu()
{
    for (int m = 1; m <= n; m++)
    {
        for (int i = 0; i < n; i++)
            color[i] = 0;
        if (toMau(0, m))
            return m;
    }
    return n;
}

// In ket qua
void inKetQua(int soMau)
{
    cout << "\nSo mau toi thieu: " << soMau << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "Dinh "
            << i
            << " -> Mau "
            << color[i]
            << endl;
    }
}

int main()
{
    if (!docfile("D:\DOTHU.txt"))
        return 0;
    inMaTran();
    int soMau = timSoMauToiThieu();
    inKetQua(soMau);
    return 0;
}