// BÀI 1 ĐỀ CL2.cpp : This file contains the 'main' function.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 26/05/2026
Công dụng:
- Đọc ma trận bãi mìn từ file
- Kiểm tra bãi mìn hợp lệ
- Đếm tổng số mìn
- Tìm vùng d x c có nhiều mìn nhất
*/

#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX 20

// ================= KHAI BÁO HÀM =================

// 1. In ma trận
void inmt(int a[][MAX], int d, int c);

// 2. Đọc file
bool docfile(char fname[], int a[][MAX], int& d, int& c);

// 3. Đếm số mìn xung quanh ô (i,j)
int demmin(int a[][MAX], int d, int c, int i, int j);

// 4. Kiểm tra bãi mìn hợp lệ
bool kiemtra(int a[][MAX], int d, int c);

// 5. Đếm tổng số mìn
int tongmin(int a[][MAX], int d, int c);

// 6. Đếm số mìn trong vùng dxc
int demsomin_vung(int a[][MAX], int d, int c,
	int r, int col,
	int sodong, int socot);

// 7. Tìm vùng dxc có nhiều mìn nhất
void timvungmax(int a[][MAX], int d, int c,
	int sodong, int socot);

// ================= MAIN =================

int main()
{
	int a[MAX][MAX] = { 0 };

	int d = 0;
	int c = 0;

	char fname[] = "D:/INPUT.txt";

	// Đọc file
	if (docfile(fname, a, d, c) == false) {
		return 0;
	}

	// In ma trận
	printf("===== MA TRAN BAI MIN =====\n");
	inmt(a, d, c);

	// Kiểm tra hợp lệ
	if (kiemtra(a, d, c) == true) {
		printf("\n=> Day la bai min HOP LE.\n");
	}
	else {
		printf("\n=> Day la bai min KHONG HOP LE.\n");
	}

	// Đếm tổng số mìn
	int tong = tongmin(a, d, c);

	printf("\nTong so qua min: %d\n", tong);

	// Nhập kích thước vùng
	int sodong = 0;
	int socot = 0;

	printf("\nNhap kich thuoc vung d x c: ");
	scanf_s("%d%d", &sodong, &socot);

	// Kiểm tra hợp lệ
	if (sodong > d || socot > c ||
		sodong <= 0 || socot <= 0) {

		printf("Kich thuoc vung khong hop le!\n");

		return 0;
	}

	// Tìm vùng nhiều mìn nhất
	timvungmax(a, d, c, sodong, socot);

	return 0;
}

// ================= ĐỊNH NGHĨA HÀM =================

// 1. In ma trận
void inmt(int a[][MAX], int d, int c)
{
	for (int i = 0; i < d; i++) {

		for (int j = 0; j < c; j++) {

			printf("%4d", a[i][j]);
		}

		printf("\n");
	}
}

// 2. Đọc file
bool docfile(char fname[], int a[][MAX], int& d, int& c)
{
	FILE* f;

	fopen_s(&f, fname, "r");

	if (f == NULL) {

		printf("Khong mo duoc file!\n");

		return false;
	}

	// Đọc số dòng và số cột
	fscanf_s(f, "%d%d", &d, &c);

	// Đọc ma trận
	for (int i = 0; i < d; i++) {

		for (int j = 0; j < c; j++) {

			fscanf_s(f, "%d", &a[i][j]);
		}
	}

	fclose(f);

	return true;
}

// 3. Đếm số mìn xung quanh ô (i,j)
int demmin(int a[][MAX], int d, int c, int i, int j)
{
	int dem = 0;

	for (int x = i - 1; x <= i + 1; x++) {

		for (int y = j - 1; y <= j + 1; y++) {

			// bỏ qua chính nó
			if (x == i && y == j)
				continue;

			// kiểm tra biên
			if (x >= 0 && x < d &&
				y >= 0 && y < c) {

				if (a[x][y] == -1)
					dem++;
			}
		}
	}

	return dem;
}

// 4. Kiểm tra bãi mìn hợp lệ
bool kiemtra(int a[][MAX], int d, int c)
{
	for (int i = 0; i < d; i++) {

		for (int j = 0; j < c; j++) {

			// Nếu không phải ô mìn
			if (a[i][j] != -1) {

				int somin = demmin(a, d, c, i, j);

				// Sai số mìn xung quanh
				if (a[i][j] != somin) {

					return false;
				}
			}
		}
	}

	return true;
}

// 5. Đếm tổng số mìn
int tongmin(int a[][MAX], int d, int c)
{
	int dem = 0;

	for (int i = 0; i < d; i++) {

		for (int j = 0; j < c; j++) {

			if (a[i][j] == -1)
				dem++;
		}
	}

	return dem;
}

// 6. Đếm số mìn trong vùng dxc
int demsomin_vung(int a[][MAX], int d, int c,
	int r, int col,
	int sodong, int socot)
{
	int dem = 0;

	for (int i = r; i < r + sodong; i++) {

		for (int j = col; j < col + socot; j++) {

			if (a[i][j] == -1)
				dem++;
		}
	}

	return dem;
}

// 7. Tìm vùng dxc có nhiều mìn nhất
void timvungmax(int a[][MAX], int d, int c,
	int sodong, int socot)
{
	int maxmin = -1;

	int vt_dong = 0;
	int vt_cot = 0;

	// duyệt các vị trí bắt đầu
	for (int i = 0; i <= d - sodong; i++) {

		for (int j = 0; j <= c - socot; j++) {

			int somin =
				demsomin_vung(a, d, c,
					i, j,
					sodong, socot);

			if (somin > maxmin) {

				maxmin = somin;

				vt_dong = i;
				vt_cot = j;
			}
		}
	}

	// Kết quả
	printf("\n===== VUNG CO NHIEU MIN NHAT =====\n");

	printf("Kich thuoc: %d x %d\n",
		sodong, socot);

	printf("Vi tri bat dau: (%d, %d)\n",
		vt_dong, vt_cot);

	printf("So qua min: %d\n", maxmin);

	// In vùng
	printf("\nNoi dung vung:\n");

	for (int i = vt_dong;
		i < vt_dong + sodong;
		i++) {

		for (int j = vt_cot;
			j < vt_cot + socot;
			j++) {

			printf("%4d", a[i][j]);
		}

		printf("\n");
	}
}