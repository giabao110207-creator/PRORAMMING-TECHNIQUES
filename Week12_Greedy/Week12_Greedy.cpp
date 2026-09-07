// Week12_Greedy.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Ho va ten: Nguyen Hoang Gia Bao
MSSV: 25ad11003
Ngay cap nhat: 16/06/2026
Cong dung: bai toan cai tui
*/

#include <iostream>
using namespace std;

typedef struct MONDO {
    int w; // Khối luong
    int v; // giá trị
    int q; // số luong
};

//1. Đọc file dữ liệu
bool docfile(const char filename[], MONDO a[], int& n);

//2. In thông tin 1 món đồ
void InMondo(MONDO m);

//3. Sắp xếp các món đồ theo tiêu chí tham
// Sắp giảm dần theo giá trị --> ưu tiên chọn món có giá trị cao
void sort1(MONDO a[], int n);

// Sắp tăng dần theo khối luong --> ưu tiên chọn món nhẹ
void sort2(MONDO a[], int n);

// Sắp giảm dần theo "đơn giá" --> ưu tiên chọn món vừa nhẹ vừa có giá trị cao
void sort3(MONDO a[], int n);

// 4. Tham lam --> Chọn các món đồ sao cho có lợi nhất
// Hàm trả về tổng giá trị lấy đuoc
int thamlam(MONDO a[], int n, int w, int count[]);
//w. sức chứa tối đa của túi
//count []: mảng chứa số luong

int main() {
    MONDO a[100], b[100], c[100];
    int n;
    int count1[100];
    int count2[100];
    int count3[100];
    if (docfile("D:\CAITUI.txt", a, n)) {
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
            c[i] = a[i];
        }

        cout << "\n=== Cach 1: Uu tien gia tri cao nhat ===\n";
        sort1(a, n);
        int t1 = thamlam(a, n, 37, count1);

        for (int i = 0; i < n; i++) {
            InMondo(a[i]);
            cout << ": " << count1[i] << endl;
        }
        cout << "Tong gia tri = " << t1 << endl;

        cout << "\n=== Cach 2: Uu tien khoi luong nho nhat ===\n";
        sort2(b, n);
        int t2 = thamlam(b, n, 37, count2);

        for (int i = 0; i < n; i++) {
            InMondo(b[i]);
            cout << ": " << count2[i] << endl;
        }
        cout << "Tong gia tri = " << t2 << endl;

        cout << "\n=== Cach 3: Uu tien don gia cao nhat ===\n";
        sort3(c, n);
        int t3 = thamlam(c, n, 37, count3);

        for (int i = 0; i < n; i++) {
            InMondo(c[i]);
            cout << ": " << count3[i] << endl;
        }
        cout << "Tong gia tri = " << t3 << endl;
    }

    return 0;
}

//1. Đọc file dữ liệu
bool docfile(const char filename[], MONDO a[], int& n) {
    FILE* fp;
    fp = fopen(filename, "r");
    if (!fp) {
        cout << "Khong doc duoc file" << endl;
        return false;
    }
    // Đọc dữ liệu
    fscanf(fp, "%d", &n); // Số loại đồ vật
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d %d %d", &a[i].w, &a[i].v, &a[i].q);
    }
    fclose(fp);
    return true;
}

//2. In thông tin 1 món đồ
void InMondo(MONDO m) {
    cout << "(" << m.w << ", "
        << m.v << ", "
        << m.q << ")";
}

// Hàm phụ
void Hoanvi(MONDO& a, MONDO& b) {
    MONDO t = a;
    a = b;
    b = t;
}

//3. Sắp xếp các món đồ theo tiêu chí tham
// Sắp giảm dần theo giá trị --> ưu tiên chọn món có giá trị cao
void sort1(MONDO a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i].v < a[j].v) {
                Hoanvi(a[i], a[j]);
            }
        }
    }
}

// Sắp tăng dần theo khối luong --> ưu tiên chọn món nhẹ
void sort2(MONDO a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i].w > a[j].w) {
                Hoanvi(a[i], a[j]);
            }
        }
    }
}

// Sắp giảm dần theo "đơn giá" --> ưu tiên chọn món vừa nhẹ vừa có giá trị cao
void sort3(MONDO a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double dg1 = (double)a[i].v / a[i].w;
            double dg2 = (double)a[j].v / a[j].w;

            if (dg1 < dg2) {
                Hoanvi(a[i], a[j]);
            }
        }
    }
}


// 4. Tham lam --> Chọn các món đồ sao cho có lợi nhất
// Hàm trả về tổng giá trị lấy đuoc
int thamlam(MONDO a[], int n, int w, int count[]) {
    int tong = 0;   // tổng giá trị
    sort1(a, n);   //Sắp xếp danh sách đồ vật theo thứ tự ưu tiên giảm dần
    for (int i = 0; i < n; i++) {
        count[i] = w / a[i].w;  // Số đồ vật loại i mà có thể lấy
        tong += count[i] * a[i].v; // Giá trị lấy đuoc tăng lên
        w -= count[i] * a[i].w;     // Sức chứa còn lại của cái túi giảm xuống
    }
    return tong;
}

