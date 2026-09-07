// Tuan06_CL2_MineSweeper.cpp : Defines the entry point for the console application.
// Họ và tên: Nguyễn Hoàng Gia Bảo
// MSSV: 25AD11003
// Chương trình 1: Trò chơi MINESWEEPER

#include <stdio.h>
#include <iostream>
using namespace std;
#include <time.h>

#define MAX 20

//Khai báo hàmh
//2. In ma trận (kích thước dxc)
void inmt(int a[][MAX], int d, int c);
//Hàm phát sinh số ngẫu nhiên từ 0 đến n-1
int random(int n)
{
	int a = rand();
	return a % n;
}
//Hàm đặt những quả mìn vào vị trí ngẫu nhiên trong bãi mìn
void datmin(int a[][MAX], int n, int somin);
//Hàm tính toán giá trị các ô còn lại trong bãi mìn
void tinhsomin(int a[][MAX], int n);
//6.Viết hàm tìm vị trí của ô xung quanh có nhiều mìn nhất
//trả về số mìn nhiều nhất
//các tham số d và c lưu dòng,cột của ô tìm được
int timmax(int a[][MAX], int n, int& d, int& c);
//7*.Viết hàm tìm vùng kxk có ít mìn nhất (k cho trước)
int timmin(int a[][MAX], int n, int k, int& d, int& c);
//8**.Viết hàm cho biết vùng chứa những số 0 liền kề lớn
//nhất gồm bao nhiêu ô.
int timvung0(int a[][MAX], int n);
//9. Lưu bãi mìn lên file văn bản
void luufile(int a[][MAX], int n, int somin, char filename[]);
//10. Đọc dữ liệu từ tập tin, kiểm tra dữ liệu có hợp lệ không
int docfile(int a[][MAX], int& n, int& somin, char filename[]);

int main()
{
	int a[MAX][MAX];		//"bãi mìn"
	int n;					//kích thước
	int somin;				//số mìn

	srand(time(NULL));
	//nhập kích thước (>=5 và <=MAX)
	do {
		cout << "Nhap kich thuoc (tu 5 den " << MAX << "):";
		cin >> n;
	} while (n<5 || n>MAX);
	//nhập số mìn (<=1/4 số ô)
	do {
		cout << "Nhap kich thuoc (tu 1 den " << n * n / 4 << "):";
		cin >> somin;
	} while (somin<1 || somin>n * n / 4);
	datmin(a, n, somin);
	tinhsomin(a, n);
	inmt(a, n, n);
	//tìm vùng có ít mìn nhất
	int d, c;
	int m = timmin(a, n, 4, d, c);
	cout << m << endl << "(" << d << "," << c << ")" << endl;
	cout << timvung0(a, n) << endl;

	luufile(a, n, somin, "C:\Users\ADMIN\Documents\MIN.txt");

	int b[MAX][MAX];
	int n2, somin2;
	if (docfile(b, n2, somin2, "C:\Users\ADMIN\Documents\MIN.txt")) {
		cout << "Bai min doc tu file:\n";
		inmt(b, n2, n2);
	}

	return 0;
}

//2. In ma trận (kích thước dxc)
void inmt(int a[][MAX], int d, int c)
{
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			cout.width(5);		//gióng thẳng cột
			cout << a[i][j];
		}
		cout << endl;			//hết 1 dòng của ma trận
	}
}

//Hàm đặt những quả mìn vào vị trí ngẫu nhiên trong bãi mìn
void datmin(int a[][MAX], int n, int somin)
{
	int i, j;
	//khởi gán
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i][j] = 0;
	//đặt mìn
	while (somin > 0) {
		i = random(n);
		j = random(n);
		if (a[i][j] == 0) {
			a[i][j] = -1;
			somin--;
		}
	}
}

//Hàm tính toán giá trị các ô còn lại trong bãi mìn
void tinhsomin(int a[][MAX], int n)
{
	int i, j, k, l, dem;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (a[i][j] == 0)			//chỉ xét những ô ko có mìn
			{
				dem = 0;
				for (k = i - 1; k <= i + 1; k++)
					for (l = j - 1; l <= j + 1; l++)
						if (k >= 0 && k < n && l >= 0 && l < n &&
							(k != i || l != j) && a[k][l] == -1)
							dem++;
				a[i][j] = dem;		//lưu lại số mìn xung quanh
			}
}

//6.Viết hàm tìm vị trí của ô xung quanh có nhiều mìn nhất
//trả về số mìn nhiều nhất
//các tham số d và c lưu dòng,cột của ô tìm được
int timmax(int a[][MAX], int n, int& d, int& c)
{
	int max = a[0][0];
	d = c = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (max < a[i][j]) {
				max = a[i][j];
				d = i;
				c = j;
			}
	return max;
}
//7*.Viết hàm tìm vùng kxk có ít mìn nhất (k cho trước)
int timmin(int a[][MAX], int n, int k, int& d, int& c) {
	int i, j, dem, l, m;
	int min = k * k;
	d = c = 0;						//cập nhật lại sau
	if (k<0 || k>n) return -1;		//lỗi, ko hợp lệ
	for (i = 0; i <= n - k; i++)	//duyệt tất cả các khối kxk
		for (j = 0; j <= n - k; j++)
		{
			//bắt đầu đếm số mìn trong vùng kxk, góc trái trên (i,j)
			dem = 0;
			for (l = 0; l < k; l++)
				for (m = 0; m < k; m++)
					if (a[i + l][j + m] == -1) dem++;
			if (dem < min) {
				min = dem;
				d = i;
				c = j;
			}
		}
	return min;
}
//8**.Viết hàm cho biết vùng chứa những số 0 liền kề lớn
//nhất gồm bao nhiêu ô.
//Bổ túc: Hàm đệ quy dùng để loang trên ma trận
int dem0(int a[][MAX], int n, int d, int c) {
	int plus = 0;
	int count = 0;
	if (a[d][c] == 0) {
		plus = 1;
		a[d][c] = -2;
	}
	//xét 8 ô xung quanh ô (d,c)
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			if (a[d + i][c + j] == 0)		//nếu là số 0 thì gọi đệ quy để loang
				count = dem0(a, n, d + i, c + j);
	return count + plus;
}

int timvung0(int a[][MAX], int n)
{
	int max = 0;
	int temp = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 0)
				temp = dem0(a, n, i, j);
			if (max < temp) max = temp;
		}
	return max;
}
//9. Lưu bãi mìn lên file văn bản
void luufile(int a[][MAX], int n, int somin, char filename[]) {
	FILE* fp;
	fp = fopen(filename, "wt");
	if (!fp) {
		cout << "Khong mo duoc file!" << endl;
		return;
	}
	//9.1 lưu n và số mìn để biết kích thuoc
	fprintf(fp, "%d %d\n", n, somin);
	// Lưu từng dòng của bãi mìn
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fprintf(fp, "%4d ", a[i][j]);
		}
		fprintf(fp, "\n");
	}
	// Đóng file
	fclose(fp);
	cout << "Da luu bai min vao file: " << filename << endl;
}
//10. Đọc dữ liệu từ tập tin, kiểm tra dữ liệu có hợp lệ không
int docfile(int a[][MAX], int& n, int& somin, char filename[]) {
	FILE* fp;
	fp = fopen(filename, "rt");
	if (!fp) {
		cout << "Khong mo duoc file!" << endl;
		return 0;
	}

	// Đọc n và số mìn
	fscanf(fp, "%d %d", &n, &somin);
	if (n<5 || n>MAX) {
		cout << "Kich thuoc khong hop le" << endl;
		fclose(fp);
		return 0;
	}
	if (somin < 1 || somin > n * n / 4) {
		cout << "So min khong hop le (1 den " << n * n / 4 << ")" << endl;
		fclose(fp);
		return 0;
	}

	// Đọc ma trận
	int demMin = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			fscanf(fp, "%d", &a[i][j]);

			// Kiểm tra từng ô: chỉ được là -1, hoặc 0..8
			if (a[i][j] < -1 || a[i][j] > 8) {
				cout << "Loi: gia tri o [" << i << "][" << j
					<< "] = " << a[i][j] << " khong hop le!\n";
				fclose(fp);
				return 0;
			}
			if (a[i][j] == -1) demMin++;
		}

	// Kiểm tra số mìn đọc được có khớp với somin không
	if (demMin != somin) {
		cout << "Loi: so min trong file (" << demMin
			<< ") khong khop voi tieu de (" << somin << ")!\n";
		fclose(fp);
		return 0;
	}

	fclose(fp);
	cout << "Doc file thanh cong! n=" << n << ", somin=" << somin << "\n";
	return 1;
}


