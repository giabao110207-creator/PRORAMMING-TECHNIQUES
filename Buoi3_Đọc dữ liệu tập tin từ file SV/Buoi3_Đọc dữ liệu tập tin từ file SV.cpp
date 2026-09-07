// Buoi3_Đọc dữ liệu tập tin từ file SV.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo
Mssv: 25AD11003
Ngaày cập nhật: 12/05/2026
Công dụng: Đọc dữ liệu từ tập tin Sv và xuất file
*/
#include <iostream>
#include <stdio.h >
using namespace std;
//khai báo cấu trúc
typedef struct {
	char mamh[15];
	char tenmh[50];
	int stc;
	float diem;
} MH; //thông tin môn hc
typedef struct {
	char mssv[10];
	char hoten[50];
	int tuoi;
	int somon;
	MH kq[100];		// mảng lưu những môn đã học
	int tongtc, tongtctl; //tổng tín chỉ, tổng tín chỉ tích lũy
	float dtbc, dtbtl; // điểm tb chung, điểm tb tích lũy
} SV; //thông tin sinh viên

//Khai báo các hàm thao tác
//1. Đọc dữ liệu từ file --> cấu trúc SV
//Đồng thời tính các thông số còn lại (tongtc,...)
void docfile(const char filename[], SV& s);
//2. In thông tin của 1 sinh viên ra màn hình
void insv(SV s);
//3. Ghi dữ liệu từ cấu trúc SV --> file (văn bản)
void ghifile(const char filename[], SV s);
//4. ghi dữ liệu từ cấu trúc SV ---> file y chang cấu trúc SV
void ghifile2(const char filename[], SV s);

int main()
{
	SV a;
	docfile("E:/SV.TXT", a);
	insv(a);
	ghifile("E:/OUTPUT1.TXT", a);
	ghifile2("E:/OUTPUT2.TXT", a);
	return 0;
}
//1. Đọc dữ liệu từ file --> cấu trúc SV
//Đồng thời tính các thông số còn lại (tongtc,...)
void docfile(const char filename[], SV& s)
{
	char tempt[100];	// chuỗi tạm, chứa nội dung k cần
	FILE* fp;
	//1. mở file
	fopen_s(&fp, filename, "rt");
	if (fp == NULL) {
		cout << "K mo dc tap tin!\n";
		return;
	}
	//2. đọc dữ liệu
	fgets(s.mssv, 10, fp);		//đọc mã số sinh viên
	s.mssv[strlen(s.mssv) - 1] = '\0'; // =0, ='\0' cũng được
	fgets(s.hoten, 50, fp);		//đọc họ tên
	s.hoten[strlen(s.hoten) - 1] = '\0';
	//đọc tuổi và số môn
	fscanf_s(fp, "%d", &s.tuoi);
	fscanf_s(fp, "%d", &s.somon);
	// đọc thông tin các môn học
	for (int i = 0; i < s.somon; i++)
	{
		//bỏ qua dòng chứa toàn dấu *
		fgets(tempt, 100, fp); // bỏ qua cái xuống dòng ( ví dụ từ 3 đến ****** nó sẽ có cái xuống dòng, thì nó đọc đc \n nên bỏ qua \n trc)
		fgets(tempt, 100, fp); // lúc này cái này mới bỏ qua dấu *****
		//đọc lấy mã môn học
		fgets(s.kq[i].mamh, 15, fp);
		s.kq[i].mamh[strlen(s.kq[i].mamh) - 1] = '\0';
		//đọc lấy tên môn học
		fgets(s.kq[i].tenmh, 50, fp);
		s.kq[i].tenmh[strlen(s.kq[i].tenmh) - 1] = '\0';
		//đọc lấy số tín chỉ và điểm
		fscanf_s(fp, "%d", &s.kq[i].stc);
		fscanf_s(fp, "%f", &s.kq[i].diem);
	}
	//3. close
	fclose(fp);
	int tong = 0, tongtl = 0;
	float td = 0, tdtl = 0;
	for (int i = 0; i < s.somon; i++)
	{
		tong += s.kq[i].stc;
		td += s.kq[i].stc * s.kq[i].diem;

		if (s.kq[i].diem >= 5.0) {
			tongtl += s.kq[i].stc;
			tdtl += s.kq[i].stc * s.kq[i].diem;
		}
	}

	s.tongtc = tong;
	s.tongtctl = tongtl;
	s.dtbc = td / tong;
	s.dtbtl = tdtl / tongtl;

}
//2. In thông tin của 1 sinh viên ra màn hình
void insv(SV s)
{
	printf("Ma so SV  : %s\n", s.mssv);
	printf("Ho va ten : %s\n", s.hoten);
	printf("Tuoi      : %d\n", s.tuoi);
	printf("So mon    : %d\n", s.somon);
	printf("Tong TC   : %d\n", s.tongtc);
	printf("Tong TCTL : %d\n", s.tongtctl);
	printf("Diem TBC  : %.1f\n", s.dtbc);
	printf("Diem TBTL : %.1f\n", s.dtbtl);

	if (s.somon > 0)
	{
		printf("===============================================================\n");
		printf("%-12s%-32s%4s%10s\n", "Ma MH", "Ten MH", "SoTC", "Diem");
		printf("===============================================================\n");

		for (int i = 0; i < s.somon; i++)
		{
			printf("%-12s%-32s%4d%10.1f\n",
				s.kq[i].mamh,
				s.kq[i].tenmh,
				s.kq[i].stc,
				s.kq[i].diem);
		}
		printf("===============================================================\n");
	}
	else if (s.somon == 0)
	{
		// Xử lý logic hợp lệ: Chưa học môn nào
		printf("---------------------------------------------------------------\n");
		printf("=> Sinh vien nay chua co du lieu mon hoc.\n");
		printf("---------------------------------------------------------------\n");
	}
	else
	{
		// Xử lý ngoại lệ (Exception): Số môn âm
		printf("---------------------------------------------------------------\n");
		printf("[LOI DU LIEU] So luong mon hoc khong the la so am (%d)!\n", s.somon);
		printf("Vui long kiem tra lai tap tin SV.TXT.\n");
		printf("---------------------------------------------------------------\n");
	}

}
//3. Ghi dữ liệu từ cấu trúc SV --> file (văn bản)
void ghifile(const char filename[], SV s)
{
	char tempt[100];	// chuỗi tạm, chứa nội dung k cần
	FILE* fp;
	//1. mở file
	fopen_s(&fp, filename, "wt");
	if (fp == NULL) {
		cout << "K mo dc tap tin!\n";
		return;
	}
	//2. ghi dữ liệu
	fprintf(fp, "Ma so SV  : %s\n", s.mssv);
	fprintf(fp, "Ho va ten : %s\n", s.hoten);
	fprintf(fp, "Tuoi      : %d\n", s.tuoi);
	fprintf(fp, "So mon    : %d\n", s.somon);
	fprintf(fp, "Tong TC   : %d\n", s.tongtc);
	fprintf(fp, "Tong TCTL : %d\n", s.tongtctl);
	fprintf(fp, "Diem TBC  : %f\n", s.dtbc);
	fprintf(fp, "Diem TBTL : %f\n", s.dtbtl);
	//3. ghi bảng vào
	if (s.somon > 0)
	{
		fprintf(fp, "===============================================================\n");
		fprintf(fp, "%-12s%-32s%4s%10s\n", "Ma MH", "Ten MH", "SoTC", "Diem");
		fprintf(fp, "===============================================================\n");

		for (int i = 0; i < s.somon; i++)
		{
			fprintf(fp, "%-12s%-32s%4d%10.1f\n",
				s.kq[i].mamh,
				s.kq[i].tenmh,
				s.kq[i].stc,
				s.kq[i].diem);
		}
		fprintf(fp, "===============================================================\n");
	}
	else if (s.somon == 0)
	{
		// Xử lý logic hợp lệ: Chưa học môn nào
		fprintf(fp, "---------------------------------------------------------------\n");
		fprintf(fp, "=> Sinh vien nay chua co du lieu mon hoc.\n");
		fprintf(fp, "---------------------------------------------------------------\n");
	}
	else
	{
		// Xử lý ngoại lệ (Exception): Số môn âm
		fprintf(fp, "---------------------------------------------------------------\n");
		fprintf(fp, "[LOI DU LIEU] So luong mon hoc khong the la so am (%d)!\n", s.somon);
		fprintf(fp, "Vui long kiem tra lai tap tin SV.TXT.\n");
		fprintf(fp, "---------------------------------------------------------------\n");
	}
	//4. close
	fclose(fp);
}
void ghifile2(const char filename[], SV s)
{
	FILE* fp;
	fopen_s(&fp, filename, "wt");
	if (fp == NULL) return;

	// Ghi đúng thứ tự như file SV.TXT mẫu
	fprintf(fp, "%s\n", s.mssv);
	fprintf(fp, "%s\n", s.hoten);
	fprintf(fp, "%d\n%d\n", s.tuoi, s.somon);

	for (int i = 0; i < s.somon; i++)
	{
		fprintf(fp, "**********\n"); // Dòng phân cách giữa các môn
		fprintf(fp, "%s\n", s.kq[i].mamh);
		fprintf(fp, "%s\n", s.kq[i].tenmh);
		fprintf(fp, "%d %.1f\n", s.kq[i].stc, s.kq[i].diem);
	}
	fclose(fp);
}
