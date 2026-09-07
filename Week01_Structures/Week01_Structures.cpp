// Week01_Structures.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
- Người viết: Nguyễn Hoàng Gia Bảo
- MSSV : 25AD11003
- Ngày cập nhật cuối: 5/5/2026
- Công dụng: Buổi số 1.1: Structure
*/

#include <iostream>
using namespace std;

//Khai báo kiểu cấu trúc ( Toàn cục )
typedef struct PS {
    int ts;
    int ms;
};

//Khai báo hàm 
//1. Nhập giá trị cho 1 phân số
void NhapPS(PS& p);
//2. In giá trị của 1 phân số 
void InPS(PS p);
//3. Nhân 2 phân số
PS NhanPS(PS a, PS b);
//4. In Phân số có giá trị thực lớn nhất ( Đầu tiên )
void InDT(PS a[], int n);

int main()
{
    //Khai báo biến cấu trúc (Cục bộ)
    PS a, b, tich;
    PS m[100];         //Mảng 1 chiều có sức chứa tối đa 100 phân số 
    int n;


    //Nhập mảng phân số
    cout << "Nhap so luong phan so: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Nhap phan so thu " << i + 1 << ":\n";
        NhapPS(m[i]);
    }

    //Gọi hàm tìm phân số lớn nhất
    InDT(m, n);
    //Thao tác trên biến cấu trúc 
    /*
    cin >> a.ts;
    cin >> a.ms;
    cout << "a = " << a.ts << "/" << a.ms << endl;
    b = a;        //Gán 2 biến cấu trúc cùng kiểu 
    cout << "b = " << b.ts << "/" << b.ms << endl;
    */

    cout << "Nhap phan so thu nhat:\n";
    NhapPS(a);
    cout << "Nhap phan so thu hai:\n";
    NhapPS(b);
    tich = NhanPS(a, b);
    cout << "Tich = ";
    InPS(tich);
    cout << endl;

}

//Định nghĩa hàm 
//1. Nhập giá trị cho 1 phân số
void NhapPS(PS& p) {
    cout << "Nhap tu so:";
    cin >> p.ts;
    do {
        cout << "Nhap mau so (khac 0): ";
        cin >> p.ms;
    } while (p.ms == 0);
}
//2. In giá trị của 1 phân số 
void InPS(PS p)
{
    cout << p.ts << "/" << p.ms;
}
//3. Nhân 2 phân số
PS NhanPS(PS a, PS b) {
    PS t;
    t.ts = a.ts * b.ts;
    t.ms = a.ms * b.ms;
    //Tối giản phân số t
    return t;
}
//4. In Phân số có giá trị thực lớn nhất ( Đầu tiên )
void InDT(PS a[], int n) {
    int max = 0;

    for (int i = 1; i < n; i++) {
        if (a[i].ts * a[max].ms > a[max].ts * a[i].ms) {
            max = i;
        }
    }

    cout << "Phan so lon nhat (dau tien) la: ";
    InPS(a[max]);
}
