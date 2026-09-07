// Week14_QuyHoachDong.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Ho va Ten: Nguyen Hoang Gia Bao
Mssv: 25ad11003
Ngay cap nhat: 19/06/2026
Cong dung: Minh hoa ve quy hoach dong
*/

#include <iostream>
using namespace std;
#define MAX 101

//VD1: Dãy số Fibonacci
//Cách 1: dùng mảng 1 chiều 
long Fibo(int n) {
    if (n <= 2) return 1;    //suy biến không cần tính 
    long F[MAX];           //dùng mảng 1 chiều để lưu kết quả trung gian
    F[1] = F[2] = 1;       //2 phần tử đầu của dãy 
    for (int i = 3; i <= n; i++)
        F[i] = F[i - 1] + F[i - 2];
    return F[n];
}
//Cách 2: dùng 3 biến 
//F2 = Fibo(i - 2), F1 = Fibo(i-1), F = F(i)
long Fibo2(int n) {
    if (n <= 2) return 1;   //suy biến
    long f2, f1, f;
    f2 = f1 = 1;     //khởi gián 
    for (int i = 3; i <= n; i++)
    {
        f = f1 + f2;
        f2 = f1;
        f1 = f;
    }
    return f;
}

//VD2: Tính n! theo quy hoạch động 
//Cách 1: dùng mảng 1 chiều 
long Fact(int n) {
    if (n <= 0) return 1;      //lỗi 
    long F[MAX];
    F[0] = 1;
    for (int i = 1; i <= n; i++)
        F[i] = F[i - 1] * i;
    return F[n];
}
//Cách 2: dùng 2 biến đơn
long Fact2(int n) {
    if (n <= 0) return 1;
    long F1, F;
    F1 = 1;
    for (int i = 1; i <= 1; i++) {
        F = F1 * i;
        F1 = F;
    }
    return F;
}
//Cách 3: dùng 1 biến đơn 
long Fact3(int n) {
    if (n <= 0) return 1;
    long F = 1;
    for (int i = 1; i <= n; i++)
        F = F * i;
    return F;
}

//VD3: bài toán phân tích số
long phantichso(int n) {
    long a[MAX][MAX];          //bảng phương án 
    int m, v;         //m dòng, v cột
    for (int j = 0; j <= n; j++)
        a[0][j] = 0;
    a[0][0] = 1;      //giá trị xuất phát 
    for (m = 1; m <= n; m++)
        for (v = 0; v <= n; v++)
            if (m > v) a[m][v] = a[m - 1][v];
            else a[m][v] = a[m - 1][v] + a[m][v - m];
    return a[n][n];
}
int main()
{
    cout << Fibo(10) << endl;
    cout << Fibo2(10) << endl;
    cout << Fact(6) << endl;
    cout << Fact2(6) << endl;
    cout << Fact3(6) << endl;
    cout << phantichso(5) << endl;
    cout << phantichso(6) << endl;
    cout << phantichso(7) << endl;
    return 0;
}

"Giải bài toán sau bằng C++ cơ bản. Chỉ dùng cấu trúc mảng/vòng lặp thông thường, dùng using namespace std, không dùng thư viện nâng cao, không viết tắt, không dùng con trỏ lằng nhằng, chuẩn sinh viên, viết đơn giản nhất . Đề bài: