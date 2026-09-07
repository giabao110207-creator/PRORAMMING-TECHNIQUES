// Week05_Caro.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
MSSV: 25ad11003
Ngày cập nhật: 19/05/2026
Công dụng: Cờ caro
*/

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

#define MAX 20 // kích thước tối đa

// Khai báo nguyên mẫu hàm
//2. In ma trận (kích thuoc dxc)
void inmt(int a[][MAX], int d, int c);

//12. Đọc ma trận từ tập tin (văn bản)
bool docfile(const char* path, // tập tin dữ liệu
	int a[][MAX],	   // ma trận
	int& n);		   // kích thuoc ma trận

//Kiểm tra trạng thái ván cờ hợp lệ
//Hợp lệ trả về 1, nguoc lại trả về 0
int hople(int a[][MAX], int n);

// Kiểm tra xem có đuong 5 nào đi qua ô (d, c) hay không
int ktduong5(int a[][MAX], int n, int d, int c);

// Kiểm tra xem nguoi cầm quân K (k=0 hoặc k=1) có thắng ván cờ chưa
int checkwin(int m[][MAX], int n, int k);

//1. Tìm một ô khi đánh vào tạo đng 5 cho quân K
//Hàm trả về true nếu tìm thấy đc 1 ô thỏa điều kiện, nguoc lại trả về false
// (i,j) chứa vị trí của ô trống tìm đuoc nếu có, nguoc lại i = j = -1
bool timduong5(int a[][MAX], int n, int k, int& i, int& j);

// Đếm số đường thắng của quân k
int demduong5(int a[][MAX], int n, int k);

// Tìm nước chặn đối thủ
bool timnuocchan(int a[][MAX], int n, int doiThu,
	int& r, int& c);

// Liệt kê các ô trống
void lietkeNuocDi(int a[][MAX], int n);

// Tính điểm bàn cờ
int scoreBoard(int a[][MAX], int n, int k);

// Ghi kết quả ra file
void ghifile(const char* path,
	int a[][MAX],
	int n);

// Kiểm tra đầy bàn cờ
bool daybanco(int a[][MAX], int n);

int main() {
	int a[MAX][MAX];
	int n;
	const char* path = "/home/hunghaohan/Documents/Code 2026/kythuatlaptrinhbuoi4/caro.txt"; // Thay đường dẫn nếu cần

	if (docfile(path, a, n)) {
		cout << "Ma tran vua doc (" << n << "x" << n << "):\n";
		inmt(a, n, n);

		cout << "\n--- KIEM TRA HOP LE ---" << endl;
		if (hople(a, n) == 1) {
			cout << "=> Trang thai ban co HOP LE." << endl;
		}
		else {
			cout << "=> Trang thai ban co KHONG hop le!" << endl;
		}

		cout << "\n--- KIEM TRA NGUOI CHIEN THANG ---" << endl;
		int winner = checkwin(a, n, 5);
		if (winner != -1) {
			cout << "=> Nguoi choi [" << winner << "] da chien thang!" << endl;
		}
		else {
			cout << "=> Chua ai chien thang tren ban co." << endl;
		}

		cout << "\n--- TIM NUOC DI QUYET DINH (Tao duong 5) ---" << endl;
		int row, col;
		int player_to_check = 1; // Thử tìm nước đi thắng cho người chơi 1 (X)
		if (timduong5(a, n, player_to_check, row, col)) {
			cout << "=> Phat hien! Nguoi choi [" << player_to_check << "] danh vao o (" << row << ", " << col << ") se thang." << endl;
		}
		else {
			cout << "=> Nguoi choi [" << player_to_check << "] chua co nuoc nao danh 1 phat an ngay." << endl;
		}
		cout << "\n--- DEM SO DUONG THANG ---" << endl; 
		cout << "Player 1 co " << demduong5(a, n, 1) << " duong 5" << endl; 
		cout << "\n--- TIM NUOC CHAN DOI THU ---" << endl; 
		int r, c; 
		if (timnuocchan(a, n, 0, r, c)) { 
			cout << "Can chan tai (" << r << ", " << c << ")" << endl; }
		else { cout << "Khong can chan" << endl; } 
		cout << "\n--- LIET KE O TRONG ---" << endl; 
		lietkeNuocDi(a, n); 
		cout << "\n--- SCORE BOARD ---" << endl; 
		cout << "Score Player 1 = " << scoreBoard(a, n, 1) << endl; 
		cout << "\n--- KIEM TRA BAN DAY ---" << endl; if (daybanco(a, n)) { 
			cout << "Ban co day" << endl; }
		else { cout << "Ban co chua day" << endl; } 
		cout << "\n--- GHI FILE OUTPUT ---" << endl; 
		ghifile("output.txt", a, n); 
		cout << "Da ghi output.txt" << endl;
	}
	}

	return 0;
}

// 2. In ma trận
void inmt(int a[][MAX], int d, int c) {
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < c; j++) {
			cout.width(5);
			cout << a[i][j];
		}
		cout << endl;
	}
}

// 12. Đọc ma trận từ tập tin
bool docfile(const char* path, int a[][MAX], int& n) {
	FILE* f;
	f = fopen(path, "r");

	if (f == NULL) {
		cout << "Ko mo duoc tap tin! Vui long kiem tra lai duong dan: " << path << endl;
		return false;
	}

	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(f, "%d", &a[i][j]);
		}
	}
	fclose(f);
	return true;
}

// Kiểm tra trạng thái ván cờ hợp lệ
int hople(int a[][MAX], int n) {
	int dem1 = 0, dem0 = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (abs(a[i][j]) > 1) return 0;
			if (a[i][j] == 1) dem1++;
			if (a[i][j] == 0) dem0++;
		}
	if (abs(dem1 - dem0) > 1) return 0;
	return 1;
}

// Kiểm tra xem có đường 5 nào đi qua ô (d,c) hay ko
int ktduong5(int a[][MAX], int n, int d, int c) {
	if (a[d][c] == -1) return 0;

	// B1. Kiểm tra đường ngang
	int j1 = c;
	int j2 = c;
	while (j1 >= 0 && a[d][j1] == a[d][c]) j1--;
	while (j2 < n && a[d][j2] == a[d][c]) j2++;
	if (j2 - j1 - 1 >= 5) return 1; // Sửa == 5 thành >= 5 cho chắc chắn (Caro 5+ vẫn thắng)

	// B2. Kiểm tra đường dọc
	int i1 = d;
	int i2 = d;
	while (i1 >= 0 && a[i1][c] == a[d][c]) i1--;
	while (i2 < n && a[i2][c] == a[d][c]) i2++;
	if (i2 - i1 - 1 >= 5) return 1;

	// B3. Kiểm tra đường chéo chính
	i1 = i2 = d;
	j1 = j2 = c;
	while (i1 >= 0 && j1 >= 0 && a[i1][j1] == a[d][c]) { i1--; j1--; }
	while (i2 < n && j2 < n && a[i2][j2] == a[d][c]) { i2++; j2++; }
	if (i2 - i1 - 1 >= 5) return 1;

	// B4. Kiểm tra đường chéo phụ
	i1 = i2 = d;
	j1 = j2 = c;
	while (i1 >= 0 && j2 < n && a[i1][j2] == a[d][c]) { i1--; j2++; }
	while (i2 < n && j1 >= 0 && a[i2][j1] == a[d][c]) { i2++; j1--; }
	if (i2 - i1 - 1 >= 5) return 1;

	return 0;
}

// Checkwin: Trả về người thắng (1 hoặc 0), nếu chưa có ai thắng trả về -1
int checkwin(int m[][MAX], int n, int k) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (m[i][j] == -1) continue; // Sửa 0 thành -1 để bỏ qua ô trống
			int player = m[i][j];

			// Check horizontal
			if (j + k <= n) {
				bool win = true;
				for (int x = 1; x < k; x++) {
					if (m[i][j + x] != player) { win = false; break; }
				}
				if (win) return player;
			}
			// Check vertical
			if (i + k <= n) {
				bool win = true;
				for (int x = 1; x < k; x++) {
					if (m[i + x][j] != player) { win = false; break; }
				}
				if (win) return player;
			}
			// Check diagonal
			if (i + k <= n && j + k <= n) {
				bool win = true;
				for (int x = 1; x < k; x++) {
					if (m[i + x][j + x] != player) { win = false; break; }
				}
				if (win) return player;
			}
			// Check anti-diagonal
			if (i + k <= n && (j - k + 1) >= 0) { // Đã chuẩn hóa lại điều kiện chống tràn mảng
				bool win = true;
				for (int x = 1; x < k; x++) {
					if (m[i + x][j - x] != player) { win = false; break; }
				}
				if (win) return player;
			}
		}
	}
	return -1; // -1 đại diện cho việc chưa ai thắng
}

// Tìm 1 ô trống mà đánh vào sẽ tạo đường 5 cho quân k
bool timduong5(int a[][MAX], int n, int k, int& i, int& j) {
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			// Nếu gặp ô trống
			if (a[row][col] == -1) {
				// Giả vờ đánh quân k vào ô này
				a[row][col] = k;

				// Kiểm tra xem nước cờ này có tạo thành đường 5 hay không
				if (ktduong5(a, n, row, col) == 1) {
					// Nếu có, lưu lại tọa độ và khôi phục ô trống
					i = row;
					j = col;
					a[row][col] = -1;
					return true; // Dừng việc tìm kiếm và báo thành công
				}

				// Khôi phục lại ô trống nếu đánh vào không thắng
				a[row][col] = -1;
			}
		}
	}

	// Nếu chạy hết bàn cờ mà không tìm được
	i = -1;
	j = -1;
	return false;
}
// Đếm số đường thắng của quân k
int demduong5(int a[][MAX], int n, int k) {
	int dem = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != k)
				continue;
			// ngang
			if (j + 4 < n) {
				bool ok = true;
				for (int x = 1; x < 5; x++) {
					if (a[i][j + x] != k) {
						ok = false;
						break;
					}
				}
				if (ok)
					dem++;
			}
			// doc
			if (i + 4 < n) {
				bool ok = true;
				for (int x = 1; x < 5; x++) {
					if (a[i + x][j] != k) {
						ok = false;
						break;
					}
				}
				if (ok)
					dem++;
			}
		}
	}
	return dem;
}
// Tìm nước chặn đối thủ
bool timnuocchan(int a[][MAX],int n,int doiThu,int& r,int& c) {
	return timduong5(
		a,
		n,
		doiThu,
		r,
		c
	);

}
// Liệt kê các ô trống
void lietkeNuocDi(int a[][MAX], int n) { 
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			if (a[i][j] == -1) 
				cout << "(" << i << "," << j << ") "; 
	cout << endl; }
// Tính điểm bàn cờ
int scoreBoard(int a[][MAX], int n, int k) { 
	int score = 0; 
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			if (a[i][j] == k) score += 10; 
	return score; }
// Ghi kết quả ra file
const char* path, int a[][MAX], int n ){ 
	FILE* f; 
	f = fopen(path, "w"); 
	if (f == NULL) 
		return; 
	fprintf(f, "%d\n", n); 
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) { 
			fprintf(f, "%d ", 
				a[i][j]); } 
		fprintf(f, "\n"); } 
	fclose(f); }
// Kiểm tra đầy bàn cờ
bool daybanco(int a[][MAX], int n) { 
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			if (a[i][j] == -1) 
				return false; 
	return true; }