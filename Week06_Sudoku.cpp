// Week06_Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25AD11003
Ngày cập nhật: 19/05/2026
Công dụng: Sudoku
*/

#include "stdio.h"
#include <iostream>
using namespace std;

#define MAX 20			//kích thước tối đa

//Khai báo
//2. In ma trận (kích thước dxc)
void inmt(int a[][MAX], int d, int c);

//12. Đọc ma trận từ tập tin (văn bản)
void docfile(char fname[], //tên tập tin dữ liệu
	int a[][MAX]); //ma trận
//Kiểm tra dòng k (k=0..8) của ô số xem có bị vi phạm tính chất ko
int ktdong(int a[][MAX], int k);

//Kiểm tra cột k
int ktcot(int a[][MAX], int k);

//Kiểm tra khối 3x3
int kt3x3(int a[][MAX], int k);

//Kiểm tra dòng, cột, vùng 3x3 chứa ô (i,j) có vi phạm không
int ktô(int a[][MAX], int i, int j);

//Tìm một số có thể điền vào ô trống chắc chắn (đã có 8 số)
int timso(int a[][MAX]);

// Đếm số ô trống
int demOTrong(int a[][MAX]);

// Tìm vị trí ô trống đầu tiên
int timOTrong(int a[][MAX], int& row, int& col);

// Kiểm tra Sudoku hoàn thành chưa
int hoanthanh(int a[][MAX]);

// Kiểm tra có thể đặt số num vào (row,col) hay không
int codatduoc(int a[][MAX], int row, int col, int num);

// Giải Sudoku bằng backtracking
int solveSudoku(int a[][MAX]);

// Thống kê số lần xuất hiện
void thongke(int a[][MAX]);

// In Sudoku đẹp hơn
void inSudokuDep(int a[][MAX]);

// Chế độ game tương tác
void choiSudoku(int a[][MAX]);

//In ma trận
void inmt(int a[][MAX], int d, int c) {
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
}


// Đọc ma trận 9x9 từ tập tin văn bản
void docfile(char fname[], int a[][MAX]) {
	FILE* f = fopen(fname, "r");
	if (f == NULL) {
		printf("Khong mo duoc file: %s\n", fname);
		return;
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			fscanf(f, "%d", &a[i][j]);
	fclose(f);
}

// Kiểm tra dòng k (k = 0..8)
// Nếu vi phạm trả về 1, ngược lại trả về 0
int ktdong(int a[][MAX], int k) {
	if (k < 0 || k > 8) return 1; //k không hợp lệ
	for (int i = 0; i < 9; i++) {
		if (a[k][i] < 0 || a[k][i] > 9) return 1; //miền giá trị
		if (a[k][i] != 0)
			for (int j = i + 1; j < 9; j++)
				if (a[k][j] == a[k][i]) return 1; //trùng
	}
	return 0; //không tìm thấy vi phạm
}

// Kiểm tra cột k (k = 0..8)
// Nếu vi phạm trả về 1, ngược lại trả về 0
int ktcot(int a[][MAX], int k) {
	if (k < 0 || k > 8) return 1; //k không hợp lệ
	for (int i = 0; i < 9; i++) {
		if (a[i][k] < 0 || a[i][k] > 9) return 1; //miền giá trị
		if (a[i][k] != 0)
			for (int j = i + 1; j < 9; j++)
				if (a[j][k] == a[i][k]) return 1; //trùng
	}
	return 0; //không tìm thấy vi phạm
}


// Kiểm tra khối 3x3 thứ k (k = 0..8)
// Nếu vi phạm trả về 1, ngược lại trả về 0

int kt3x3(int a[][MAX], int k) {
	if (k < 0 || k > 8) return 1;
	int d = 3 * (k / 3) + 1; //tọa độ ô trung tâm khối 3x3 thứ k
	int c = 3 * (k % 3) + 1;
	int temp[9]; //mảng 1 chiều tạm
	int n = 0; //số phần tử của mảng 1 chiều
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			temp[n++] = a[d + i][c + j]; //đổ ra mảng 1 chiều

	//kiểm tra trùng trên mảng 1 chiều temp (giống ktdong nhưng trên temp)
	for (int i = 0; i < 9; i++) {
		if (temp[i] < 0 || temp[i] > 9) return 1; //miền giá trị
		if (temp[i] != 0)
			for (int j = i + 1; j < 9; j++)
				if (temp[j] == temp[i]) return 1; //trùng
	}
	return 0; //không tìm thấy vi phạm
}

// Kiểm tra dòng, cột, vùng 3x3 chứa ô (i, j) có vi phạm không
// Nếu vi phạm trả về 1, ngược lại trả về 0
int ktô(int a[][MAX], int i, int j) {
	if (i < 0 || i > 8 || j < 0 || j > 8) return 1;

	// Kiểm tra dòng i
	if (ktdong(a, i)) return 1;

	// Kiểm tra cột j
	if (ktcot(a, j)) return 1;

	// Xác định khối 3x3 chứa ô (i, j)
	// Khối k: hàng khối = i/3, cột khối = j/3 => k = (i/3)*3 + (j/3)
	int k = (i / 3) * 3 + (j / 3);
	if (kt3x3(a, k)) return 1;

	return 0; //không vi phạm
}

// Tìm một số (1..9) có thể điền vào ô trống một cách chắc chắn
// (ô đó đã có 8 số khác trong dòng/cột/khối => chỉ còn 1 khả năng)
// Nếu tìm được: điền vào và trả về số đó
// Nếu không tìm được ô nào: trả về 0
int timso(int a[][MAX]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (a[i][j] != 0) continue; //ô đã có số, bỏ qua

			// Thu thập tập hợp các số đã xuất hiện trong dòng, cột, khối
			bool used[10] = { false }; //used[1..9]

			// Dòng i
			for (int c = 0; c < 9; c++)
				if (a[i][c] >= 1 && a[i][c] <= 9)
					used[a[i][c]] = true;

			// Cột j
			for (int r = 0; r < 9; r++)
				if (a[r][j] >= 1 && a[r][j] <= 9)
					used[a[r][j]] = true;

			// Khối 3x3 chứa (i, j)
			int startR = (i / 3) * 3;
			int startC = (j / 3) * 3;
			for (int r = startR; r < startR + 3; r++)
				for (int c = startC; c < startC + 3; c++)
					if (a[r][c] >= 1 && a[r][c] <= 9)
						used[a[r][c]] = true;

			// Đếm số còn lại có thể điền
			int count = 0, candidate = 0;
			for (int num = 1; num <= 9; num++)
				if (!used[num]) {
					count++;
					candidate = num;
				}

			// Chắc chắn khi chỉ còn đúng 1 khả năng
			if (count == 1) {
				a[i][j] = candidate;
				return candidate;
			}
		}
	}
	return 0; //không tìm thấy ô nào chắc chắn
}

// Đếm số ô trống
int demOTrong(int a[][MAX]) {
	int dem = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (a[i][j] == 0)
				dem++;
	return dem;
}
// Tìm ô trống đầu tiên
int timOTrong(int a[][MAX], int& row, int& col) {
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			if (a[row][col] == 0)
				return 1;
	return 0;
}
// Kiểm tra Sudoku hoàn chỉnh chưa
int hoanthanh(int a[][MAX]) {
	if (demOTrong(a) != 0)
		return 0;
	for (int i = 0; i < 9; i++) {
		if (ktdong(a, i)) return 0;
		if (ktcot(a, i)) return 0;
		if (kt3x3(a, i)) return 0;
	}
	return 1;
}
// Có đặt được số không
int codatduoc(int a[][MAX], int row, int col, int num) {
	if (a[row][col] != 0)
		return 0;
	a[row][col] = num;
	int ok = !ktô(a, row, col);
	a[row][col] = 0;
	return ok;
}
// Backtracking Solver
int solveSudoku(int a[][MAX]) {
	int row, col;
	if (!timOTrong(a, row, col))
		return 1;
	for (int num = 1; num <= 9; num++) {
		if (codatduoc(a, row, col, num)) {
			a[row][col] = num;
			if (solveSudoku(a))
				return 1;
			a[row][col] = 0;
		}
	}
	return 0;
}
// Thống kê số xuất hiện
void thongke(int a[][MAX]) {
	int dem[10] = { 0 };
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (a[i][j] >= 1 && a[i][j] <= 9)
				dem[a[i][j]]++;
	for (int i = 1; i <= 9; i++)
		printf("So %d xuat hien %d lan\n", i, dem[i]);
}
// In Sudoku đẹp hơn
void inSudokuDep(int a[][MAX]) {
	for (int i = 0; i < 9; i++) {
		if (i != 0 && i % 3 == 0)
			printf("-----------------------------\n");
		for (int j = 0; j < 9; j++) {
			if (j != 0 && j % 3 == 0)
				printf("| ");
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}
// Chế độ chơi tương tác
void choiSudoku(int a[][MAX]) {
	int row, col, num;
	while (!hoanthanh(a)) {
		inSudokuDep(a);
		printf("Nhap dong cot so: ");
		cin >> row >> col >> num;
		if (row < 0 || row > 8 ||
			col < 0 || col > 8 ||
			num < 1 || num > 9) {
			printf("Khong hop le\n");
			continue;
		}
		if (codatduoc(a, row, col, num)) {
			a[row][col] = num;
			printf("Da dien\n");
		}
		else {
			printf("Khong the dat\n");
		}
	}
	printf("Hoan thanh Sudoku!\n");
}
int main() {
	int a[MAX][MAX] = { 0 };
	char fname[] = "/home/hunghaohan/Documents/Code 2026/kythuatlaptrinhbuoi4/sudoku.txt";
	// Đọc dữ liệu từ file
	docfile(fname, a);
	printf("=== Ma tran Sudoku ban dau ===\n");
	inmt(a, 9, 9);
	// Kiểm tra từng dòng
	printf("\n=== Kiem tra dong ===\n");
	for (int k = 0; k < 9; k++)
		printf("Dong %d: %s\n", k, ktdong(a, k) ? "VI PHAM" : "hop le");
	// Kiểm tra từng cột
	printf("\n=== Kiem tra cot ===\n");
	for (int k = 0; k < 9; k++)
		printf("Cot %d: %s\n", k, ktcot(a, k) ? "VI PHAM" : "hop le");
	// Kiểm tra 9 khối 3x3
	printf("\n=== Kiem tra khoi 3x3 ===\n");
	for (int k = 0; k < 9; k++)
		printf("Khoi %d: %s\n", k, kt3x3(a, k) ? "VI PHAM" : "hop le");
	// Thử điền số chắc chắn vào ô trống
	printf("\n=== Tim so chac chan ===\n");
	int so;
	while ((so = timso(a)) != 0)
		printf("Da dien so %d vao o trong.\n", so);
	printf("\n=== Ma tran sau khi dien them ===\n");
	inmt(a, 9, 9);
	printf("\n=== Dem o trong ===\n");
	printf("So o trong: %d\n", demOTrong(a));
	printf("\n=== Sudoku dep hon ===\n");
	inSudokuDep(a);
	printf("\n=== Thong ke ===\n");
	thongke(a);
	printf("\n=== Kiem tra hoan thanh ===\n");
	if (hoanthanh(a))
		printf("Sudoku da hoan thanh\n");
	else
		printf("Sudoku chua hoan thanh\n");
	printf("\n=== Giai bang Backtracking ===\n");
	int temp[MAX][MAX];
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			temp[i][j] = a[i][j];
	if (solveSudoku(temp)) {
		printf("Giai thanh cong:\n");
		inSudokuDep(temp);
	}
	else {
		printf("Khong giai duoc\n");
	}
	// Muon choi tay thi mo comment
	// choiSudoku(a);
	return 0;
}


//CÁC KÍCH THUỚC KHÁC
/*
#include<iostream>
#include<stdio.h>

using namespace std;

#define MAX 20

void inmt(int a[][MAX],int n){

	for(int i=0;i<n;i++){

		for(int j=0;j<n;j++)
			printf("%3d",a[i][j]);

		printf("\n");
	}
}

int ktdong(int a[][MAX],int n,int k){

	for(int i=0;i<n;i++){

		if(a[k][i]<0 || a[k][i]>n)
			return 1;

		if(a[k][i]!=0)

			for(int j=i+1;j<n;j++)

				if(a[k][i]==a[k][j])

					return 1;
	}

	return 0;
}

int ktcot(int a[][MAX],int n,int k){

	for(int i=0;i<n;i++){

		if(a[i][k]!=0)

			for(int j=i+1;j<n;j++)

				if(a[i][k]==a[j][k])

					return 1;
	}

	return 0;
}

int ktblock(int a[][MAX],int n,int block,int k){

	int sr=(k/(n/block))*block;

	int sc=(k%(n/block))*block;

	int temp[MAX];

	int cnt=0;

	for(int i=sr;i<sr+block;i++)

		for(int j=sc;j<sc+block;j++)

			temp[cnt++]=a[i][j];

	for(int i=0;i<cnt;i++){

		if(temp[i]!=0)

			for(int j=i+1;j<cnt;j++)

				if(temp[i]==temp[j])

					return 1;
	}

	return 0;
}

int main(){

	int a[MAX][MAX];

	int n;

	cin>>n;

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];

	int block=sqrt(n);

	inmt(a,n);

	cout<<"\nDong\n";

	for(int i=0;i<n;i++)
		cout<<ktdong(a,n,i)<<endl;

	cout<<"\nCot\n";

	for(int i=0;i<n;i++)
		cout<<ktcot(a,n,i)<<endl;

	cout<<"\nBlock\n";

	for(int i=0;i<n;i++)
		cout<<ktblock(a,n,block,i)<<endl;

}
*/



//HÌNH CHỮ NHẬT 6X6
/*
#include<iostream>
#include<stdio.h>

using namespace std;

#define MAX 20

void inmt(int a[][MAX],int r,int c){

	for(int i=0;i<r;i++){

		for(int j=0;j<c;j++)

			printf("%3d",a[i][j]);

		printf("\n");
	}
}

int ktdong(int a[][MAX],int row,int col,int k){

	for(int i=0;i<col;i++){

		if(a[k][i]!=0)

			for(int j=i+1;j<col;j++)

				if(a[k][i]==a[k][j])

					return 1;
	}

	return 0;
}

int ktcot(int a[][MAX],int row,int col,int k){

	for(int i=0;i<row;i++){

		if(a[i][k]!=0)

			for(int j=i+1;j<row;j++)

				if(a[i][k]==a[j][k])

					return 1;
	}

	return 0;
}

int ktblock(int a[][MAX],
			int row,
			int col,
			int blockR,
			int blockC,
			int k){

	int blockPerRow=col/blockC;

	int sr=(k/blockPerRow)*blockR;

	int sc=(k%blockPerRow)*blockC;

	int temp[MAX];

	int cnt=0;

	for(int i=sr;i<sr+blockR;i++)

		for(int j=sc;j<sc+blockC;j++)

			temp[cnt++]=a[i][j];

	for(int i=0;i<cnt;i++){

		if(temp[i]!=0)

			for(int j=i+1;j<cnt;j++)

				if(temp[i]==temp[j])

					return 1;
	}

	return 0;
}

int main(){

	int a[MAX][MAX];

	int row=6;

	int col=6;

	int blockR=2;

	int blockC=3;

	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			cin>>a[i][j];

	inmt(a,row,col);

	cout<<"\nDong\n";

	for(int i=0;i<row;i++)
		cout<<ktdong(a,row,col,i)<<endl;

	cout<<"\nCot\n";

	for(int i=0;i<col;i++)
		cout<<ktcot(a,row,col,i)<<endl;

	cout<<"\nBlock\n";

	int totalBlock=
		(row/blockR)*
		(col/blockC);

	for(int i=0;i<totalBlock;i++)

		cout<<ktblock(
			a,
			row,
			col,
			blockR,
			blockC,
			i
		)<<endl;
}
*/