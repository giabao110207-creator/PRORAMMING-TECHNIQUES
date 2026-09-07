// Buoi05_Ky Thuat Xu Li So Lon.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Ho va ten: Nguyen Hoang Gia Bao
MSSV: 25AD11003
Ngay cap nhat: 22/05/2026
Cong dung: Ky thuat xu li so lon
*/

#include <iostream>
#include <conio.h>

using namespace std;

//Khai báo hằng
#define MAXDIGITS 100 /* maximum length */
#define PLUS 1 /* positive sign bit */
#define MINUS -1 /* negative sign bit */

//Khai báo cấu trúc
typedef struct {
	char digits[MAXDIGITS]; /* the number */    
	int signbit; /* PLUS or MINUS */    //Duong hoac am
	int lastdigit; /*index of high-order digit*/     //Vi tri so cao nhat
}bignum;


//Khai báo hàm
void scan_bignum(bignum& n);     //Nhap so lon tu ban phim
void print_bignum(bignum n);     //In so lon ra man hinh
int kiemtra(char s[]);
void add_bignum(bignum a, bignum b, bignum &c);
void subtract_bignum(bignum a, bignum b, bignum &c);
int max(int a, int b);
void zero_justify(bignum& n);
int compare_bignum(bignum a, bignum b);
void digit_shift(bignum& n, int d);
void initialize_bignum(bignum& n);
void multiply_bignum(bignum a, bignum b, bignum c);
void int_to_bignum(int k, bignum& n);

void main()
{
	do {
		bignum a, b, c;
		int_to_bignum(1000, a);
		int_to_bignum(-500, b);
		add_bignum(a, b, c);
		cout << "a+b=";
		print_bignum(c);
		cout << endl;
		cout << "Nhap a:";
		scan_bignum(a);
	    cout << "Nhap b:";
		scan_bignum(b);
		cout << "So vua nhap:";
		print_bignum(a);
		cout << endl;
		cout << "Nhap b: ";
		scan_bignum(b);
        multiply_bignum(a, b, c);
		cout << "a*b=";
		print_bignum(c);
		cout << endl;
		subtract_bignum(a, b, c);
		cout << "a-b=";
		print_bignum(c);
		cout << endl;
		cout << "Nhan phim ESC de thoat...\n";
	} while (_getch() != 27);
}

//Một số hàm xử lý
void print_bignum(bignum n)
{
	int i;
	if (n.signbit == MINUS) cout << "-";
	for (i = n.lastdigit; i >= 0; i--)
		cout << int(n.digits[i]);
}

int kiemtra(char s[]) {
	//ktra ký tự đầu
	if (s[0] != '-' && !isdigit(s[0]))
		return 0;
	//ktra các ký tự tiếp theo
	int len = strlen(s);
	for (int i = 1; i < len; i++)
		if (!isdigit(s[i])) return 0;
	//không phát hiện vi phạm
	return 1;
}

void scan_bignum(bignum& n)
{
	//B1: Nhập chuỗi
	char temp[256];
	cin.getline(temp, 256);
	//B2: Kiểm tra
	if (!kiemtra(temp)) {	//không hợp lệ
		//gán bignum = 0
		n.signbit = PLUS;
		n.lastdigit = 0;
		n.digits[0] = 0;
	}
	else {		//hợp lệ. B3: chuyển thành số bignum
		        //xét 2 trường hợp
		if (temp[0] != '-') {	//số dương
			n.signbit = PLUS;
			n.lastdigit = strlen(temp) - 1;
			for (int i = 0; i <= n.lastdigit; i++)
				n.digits[i] = temp[n.lastdigit - i] - 48;
		}
		else {				//số âm
			n.signbit = MINUS;
			n.lastdigit = strlen(temp) - 2;
			for (int i = 0; i <= n.lastdigit; i++)
				n.digits[i] = temp[n.lastdigit + 1 - i] - 48;
		}
	}
}

void add_bignum(bignum a, bignum b, bignum &c)
{
	int carry; /* carry digit */
	int i; /* counter */
	//initialize_bignum(c);
	if (a.signbit == b.signbit) c.signbit = a.signbit;
	else {
		if (a.signbit == MINUS) {
			a.signbit = PLUS;
			subtract_bignum(b, a, c);
			a.signbit = MINUS;
		}
		else {
			b.signbit = PLUS;
			subtract_bignum(a, b, c);
			b.signbit = MINUS;
		}
		return;
	}
	c.lastdigit = max(a.lastdigit, b.lastdigit) + 1;
	//Dieu chinh -. dien them so 0 vao ben phai cua A va B
	for (i = a.lastdigit + 1; i <= c.lastdigit; i++)
		a.digits[i] = 0;
	for (i = b.lastdigit + 1; i <= c.lastdigit; i++)
		b.digits[i] = 0;
	//Tinh toan
	carry = 0;
	for (i = 0; i <= (c.lastdigit); i++) {
		c.digits[i] = (char)
			(carry + a.digits[i] + b.digits[i]) % 10;
		carry = (carry + a.digits[i] + b.digits[i]) / 10;
	}
		zero_justify(c);
}

//Tru 2 so kieu bignum
void subtract_bignum(bignum a, bignum b, bignum& c){
	int borrow; /* anything borrowed? */
	int v; /* placeholder digit */
	int i; /* counter */
	if ((a.signbit == MINUS) || (b.signbit == MINUS)) {
		b.signbit = -1 * b.signbit;
		add_bignum(a, b, c);
		b.signbit = -1 * b.signbit;
		return;
	}
	if (compare_bignum(a, b) == PLUS) {
		subtract_bignum(b, a, c);
		c.signbit = MINUS;
		return;
	}
	c.lastdigit = max(a.lastdigit, b.lastdigit);
	//Dieu chinh -. dien them so 0 vao ben phai cua A va B
	for (i = a.lastdigit + 1; i <= c.lastdigit; i++)
		a.digits[i] = 0;
	for (i = b.lastdigit + 1; i <= c.lastdigit; i++)
		b.digits[i] = 0;
	borrow = 0;
		for (i = 0; i <= (c.lastdigit); i++) {
			v = (a.digits[i] - borrow - b.digits[i]);
			if (a.digits[i] > 0)
				borrow = 0;
			if (v < 0) {
				v = v + 10;
				borrow = 1;
			}
			c.digits[i] = (char)v % 10;
		}
	zero_justify(c);

}
//Ham tim so lon hon trong 2 so nguyen to
int max(int a, int b) {
	return (a > b) ? a : b;
}
//Ham loai bo nhung chu so 0 vo nghia trong 1 bignum
void zero_justify(bignum &n)
{
	while ((n.lastdigit > 0) && (n.digits[n.lastdigit] == 0))
		n.lastdigit--;
	if ((n.lastdigit == 0) && (n.digits[0] == 0))
		n.signbit = PLUS; /* hack to avoid -0 */
}

int compare_bignum(bignum a, bignum b)
{
	int i; /* counter */
	if ((a.signbit == MINUS) && (b.signbit == PLUS)) return(PLUS);
	if ((a.signbit == PLUS) && (b.signbit == MINUS)) return(MINUS);
	if (b.lastdigit > a.lastdigit) return (PLUS * a.signbit);
	if (a.lastdigit > b.lastdigit) return (MINUS * a.signbit);
	for (i = a.lastdigit; i >= 0; i--) {
		if (a.digits[i] > b.digits[i])
			return(MINUS * a.signbit);
		if (b.digits[i] > a.digits[i])
			return(PLUS * a.signbit);
	}
	return(0);
}

void multiply_bignum(bignum a, bignum b, bignum c)
{
	bignum row; /* represent shifted row */
	bignum tmp; /* placeholder bignum */
	int i, j; /* counters */
	initialize_bignum(c);
	row = a;
	for (i = 0; i <= b.lastdigit; i++) {
		for (j = 1; j <= b.digits[i]; j++) {
			add_bignum(c, row, tmp);
			c = tmp;
		}
		digit_shift(row, 1);
	}
	c.signbit = a.signbit * b.signbit;
	zero_justify(c);
}

void digit_shift(bignum &n, int d) /* multiply n by 10ˆd */
{
	int i; /* counter */
	if ((n.lastdigit == 0) && (n.digits[0] == 0)) return;
	for (i = n.lastdigit; i >= 0; i--)
		n.digits[i + d] = n.digits[i];
	for (i = 0; i < d; i++) n.digits[i] = 0;
	
		n.lastdigit = n.lastdigit + d;
}

//Chuyen tu so nguyen thanh so kieu bignum
void int_to_bignum(int k, bignum& n) {
	char temp[256];     //Chuoi chua so nguyen( sau khi chuyen )
	_itoa_s(k, temp, 10);   //Chuyen so thanh chuoi
	//Chuyen chuoi thanh bignum
	//xét 2 trường hợp
	if (temp[0] != '-') {	//số dương
		n.signbit = PLUS;
		n.lastdigit = strlen(temp) - 1;
		for (int i = 0; i <= n.lastdigit; i++)
			n.digits[i] = temp[n.lastdigit - i] - 48;
	}
	else {				//số âm
		n.signbit = MINUS;
		n.lastdigit = strlen(temp) - 2;
		for (int i = 0; i <= n.lastdigit; i++)
			n.digits[i] = temp[n.lastdigit + 1 - i] - 48;
	}
}
