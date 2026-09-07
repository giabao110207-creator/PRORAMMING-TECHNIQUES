#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

// ====================== KHAI BAO CAU TRUC ======================
typedef struct
{
	char hoten[50];
	char manv[15];
	float luong;
} NV;

// ====================== KHAI BAO CAC HAM ======================

// 1. Nhap 1 nhan vien
void nhap1NV(NV& nv);

// 2. Nhap danh sach nhan vien
void nhapDS(NV ds[], int n);

// 3. In 1 nhan vien
void in1NV(NV nv);

// 4. In danh sach nhan vien
void inds(NV ds[], int n);

// 5. Tim nhan vien co luong cao nhat
void NVLuongCaoNhat(NV ds[], int n);

// 6. Doi cho 2 nhan vien
void doiCho(NV& a, NV& b);

// 7. Sap xep danh sach tang dan theo luong
void sapxepTheoLuong(NV ds[], int n);


int main()
{
	NV ds[100];
	int n;

	// Nhap so luong nhan vien
	cout << "Nhap so luong nhan vien: ";
	cin >> n;

	// Nhap danh sach
	nhapDS(ds, n);

	// In danh sach vua nhap
	printf("\n=========== DANH SACH NHAN VIEN ===========\n");
	inds(ds, n);

	// Cau a: Tim nhan vien luong cao nhat
	NVLuongCaoNhat(ds, n);

	// Cau b: Sap xep tang dan theo luong
	sapxepTheoLuong(ds, n);

	printf("\n=========== DANH SACH SAP XEP TANG DAN THEO LUONG ===========\n");
	inds(ds, n);

	return 0;
}


// ====================== NHAP 1 NHAN VIEN ======================
void nhap1NV(NV& nv)
{
	cout << "Nhap ho ten: ";
	cin.ignore();
	cin.getline(nv.hoten, 50);

	cout << "Nhap ma nhan vien: ";
	cin.getline(nv.manv, 15);

	cout << "Nhap luong: ";
	cin >> nv.luong;
}


// ====================== NHAP DANH SACH ======================
void nhapDS(NV ds[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\n========== NHAN VIEN %d ==========\n", i + 1);
		nhap1NV(ds[i]);
	}
}


// ====================== IN 1 NHAN VIEN ======================
void in1NV(NV nv)
{
	printf("Ma NV    : %s\n", nv.manv);
	printf("Ho ten   : %s\n", nv.hoten);
	printf("Luong    : %.2f\n", nv.luong);
}


// ====================== IN DANH SACH ======================
void inds(NV ds[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\n============= NHAN VIEN %d =============\n", i + 1);
		in1NV(ds[i]);
	}
}


// ====================== NHAN VIEN LUONG CAO NHAT ======================
void NVLuongCaoNhat(NV ds[], int n)
{
	int vt = 0;

	for (int i = 1; i < n; i++)
	{
		if (ds[i].luong > ds[vt].luong)
		{
			vt = i;
		}
	}

	printf("\n=========== NHAN VIEN LUONG CAO NHAT ===========\n");
	in1NV(ds[vt]);
}


// ====================== DOI CHO 2 NHAN VIEN ======================
void doiCho(NV& a, NV& b)
{
	NV temp = a;
	a = b;
	b = temp;
}


// ====================== SAP XEP TANG DAN THEO LUONG ======================
void sapxepTheoLuong(NV ds[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (ds[i].luong > ds[j].luong)
			{
				doiCho(ds[i], ds[j]);
			}
		}
	}
}