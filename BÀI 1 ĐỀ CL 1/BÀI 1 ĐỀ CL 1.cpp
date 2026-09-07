// BÀI 1 ĐỀ CL 1.cpp : This file contains the 'main' function.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 26/05/2026
Công dụng: Bài 1 đề CL 1
*/

#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX 20

//KHAI BÁO
//1. In ma trận
void inmt(int a[][MAX], int d, int c);
//2. Đọc file
void docfile(char fname[], int a[][MAX]);
//3. Tính tỉ lệ ô trống
void tileotrong(int a[][MAX], int d, int c);
//4. Kiểm tra số x
void kiemtraX(int a[][MAX], int d, int c, int x);
//5. Tìm dòng có ít ô trống nhất
void dongittrongnhat(int a[][MAX], int d, int c);

int main()
{
	int a[MAX][MAX] = { 0 };
	char fname[] = "D:/INPUT.txt";
	docfile(fname, a);
	printf("=== MA TRAN SUDOKU ===\n");
	inmt(a, 9, 9);
	printf("\n=== TI LE O TRONG ===\n");
	tileotrong(a, 9, 9);
	int x;
	printf("\nNhap x (1 -> 9): ");
	scanf_s("%d", &x);
	printf("\n=== KIEM TRA GIA TRI X ===\n");
	kiemtraX(a, 9, 9, x);
	printf("\n=== DONG IT O TRONG NHAT ===\n");
	dongittrongnhat(a, 9, 9);

	return 0;
}

//1. In ma trận
void inmt(int a[][MAX], int d, int c)
{
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}
//2. Đọc file
void docfile(char fname[], int a[][MAX])
{
	FILE* f;
	fopen_s(&f, fname, "r");
	if (f == NULL) {
		printf("Khong mo duoc file!\n");
		return;
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf_s(f, "%d", &a[i][j]);
		}
	}
	fclose(f);
}
//3. Tính tỉ lệ ô trống
void tileotrong(int a[][MAX], int d, int c)
{
	int dem = 0;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {

			if (a[i][j] == 0)
				dem++;
		}
	}
	float tile = (float)dem / (d * c) * 100;
	printf("So o trong: %d\n", dem);
	printf("Ti le o trong: %.2f%%\n", tile);
}
//4. Kiểm tra số x
void kiemtraX(int a[][MAX], int d, int c, int x)
{
	int dem = 0;
	bool vipham = false;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			if (a[i][j] == x)
				dem++;
		}
	}

	printf("So lan xuat hien cua %d la: %d\n", x, dem);
	for (int i = 0; i < d; i++) {
		int count = 0;
		for (int j = 0; j < c; j++) {
			if (a[i][j] == x)
				count++;
		}
		if (count >= 2) {
			printf("Vi pham dong %d\n", i);
			vipham = true;
		}
	}
	for (int j = 0; j < c; j++) {
		int count = 0;
		for (int i = 0; i < d; i++) {
			if (a[i][j] == x)
				count++;
		}
		if (count >= 2) {
			printf("Vi pham cot %d\n", j);
			vipham = true;
		}
	}
	for (int dong = 0; dong < 9; dong += 3) {
		for (int cot = 0; cot < 9; cot += 3) {
			int count = 0;
			for (int i = dong; i < dong + 3; i++) {
				for (int j = cot; j < cot + 3; j++) {
					if (a[i][j] == x)
						count++;
				}
			}
			if (count >= 2) {
				printf("Vi pham vung 3x3 bat dau tai (%d,%d)\n", dong, cot);
				vipham = true;
			}
		}
	}
	if (vipham == true)
		printf("Gia tri %d VI PHAM Sudoku\n", x);
	else
		printf("Gia tri %d KHONG vi pham Sudoku\n", x);
}

//5. Tìm dòng có ít ô trống nhất
void dongittrongnhat(int a[][MAX], int d, int c) {
	int vitri = -1;
	int min = 10;
	for (int i = 0; i < d; i++) {
		int dem = 0;
		for (int j = 0; j < c; j++) {
			if (a[i][j] == 0)
				dem++;
		}
		if (dem > 0 && dem < min) {
			min = dem;
			vitri = i;
		}
	}
	printf("Dong it o trong nhat la dong %d\n", vitri);
	printf("So o trong: %d\n", min);
	// Nếu chỉ còn 1 ô trống
	if (min == 1) {
		bool check[10] = { false };
		// Đánh dấu các số đã có
		for (int j = 0; j < c; j++) {
			if (a[vitri][j] != 0)
				check[a[vitri][j]] = true;
		}
		// Tìm số còn thiếu
		for (int k = 1; k <= 9; k++) {
			if (check[k] == false) {
				printf("So con thieu la: %d\n", k);
			}
		}
	}
}