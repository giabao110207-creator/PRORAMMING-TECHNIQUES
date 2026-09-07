// Week03_CardGames.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Họ và tên: Nguyễn Hoàng Gia Bảo 
MSSV: 25AD11003
Ngày cập nhật: 12/05/2007
Công dụng: 
*/


#include "stdio.h"
#include <time.h>
#include <iostream>
using namespace std;
#define MAX 52			//number of cards in a deck

//Khai báo cấu trúc 1 lá bài
typedef struct CARD {
	int shape;		//1: hearts, 2: diamonds, 3: clubs, 4: spades
	int number;		//1 --> 13: 11 = J, 12 = Q, 13 = K
};

//Biến toàn cục (global variables)
CARD deck[52];

//Khai báo các hàm xử lý
//1. Tạo bộ bài tây gồm 52 lá
void CreateDeck(CARD deck[52]);
//2. Xáo trộn thứ tự trong bộ bài (ngẫu nhiên)
void ShuffleDeck(CARD deck[52]);
//3. Chia bài cho n người chơi, mỗi người cầm k lá bài
void DealCards(CARD deck[52], CARD hands[MAX][MAX], int n, int k);
//4. Đếm nút bài cào: trả về số nút
//0 = bù, 10 = ba tây, 1-9 = số nút
int CountPoints(CARD b1, CARD b2, CARD b3);
//5. Xác định người chơi thắng cuộc?
//Trả về số lượng người thắng cuộc, stt của những người thắng, số nút cao nhất
int FindWinners(CARD hands[MAX][MAX], int n, int winners[], int& maxpoints);
//6. In bộ bài ra màn hình để quan sát
void PrintDeck(CARD deck[52]);
//7. In thông tin 1 lá bài ra màn hình
void PrintCard(CARD b);
//8. In tay bài ra màn hình để quan sát
void PrintHand(CARD hand[], int k);
//9. Tính số điểm của 1 tay bài theo trò chơi xì dzách
//Tay bài có từ 2 tới 5 lá
//Hàm trả về 23 nếu tay bài có đúng 2 quân A
//Hàm trả về 22 nếu tay bài có đúng 2 quân, trong đó có 1A và 1 hình (hoặc 10)
//Trường hợp còn lại quân hình tính 10, quân A có thể tính 1, 10 hoặc 11 sao cho có lợi nhất
//Nếu tổng số nút của các lá bài > 21, hàm trả về 0
//Ngược lại trả về tổng số nút của các lá bài
int BlackJack(CARD hand[], int k);
//10. Sắp xếp các lá bài trong tay bài tăng dần theo quy tắc bài "Tiến Lên miền Nam"
//Nhỏ nhất là quân 3 bích, lớn nhất là quân 2 cơ
void SortHand(CARD hand[], int k);
//11. Hàm kiểm tra xem 1 tay bài (gồm k lá) có chứa loại nào sau đây không
//Nếu có sảnh rồng (13 lá khác nút) trả về 6
//Nếu có 4 quân 2, trả về 5
//Nếu có 6 đôi, trả về 4
//Nếu có 4 đôi thông trả về 3
//Nếu có tứ quý (ko phải tứ quý 2) trả về 2
//Nếu có 3 đôi thông trả về 1
//Các trường hợp khác trả về 0
int CheckTienLen(CARD hand[], int k = 13);
//12. (Bài tập cộng điểm) bài Poker (5 lá) -- Xem trên trang LMS
int CheckPoker(CARD hand[], int k = 5);

int main()
{
	CARD hands[MAX][MAX];
	int n = 4, k = 13;
	srand((unsigned)time(NULL));		//generate a different set of random numbers each time
	CreateDeck(deck);
	ShuffleDeck(deck);
	//PrintDeck(deck);
	DealCards(deck, hands, n, k);

	PrintHand(hands[0], k);              //In tay bài của người chơi số 0
		cout << "========\n";
		SortHand(hands[0], k);
		PrintHand(hands[0], k);
		cout << "========\n";

		int result = CheckTienLen(hands[0], k);

		cout << "Loai bai: ";

		switch (result) {
		case 6:
			cout << "Sanh rong";
			break;
		case 5:
			cout << "4 quan 2";
			break;
		case 4:
			cout << "6 doi";
			break;
		case 3:
			cout << "4 doi thong";
			break;
		case 2:
			cout << "Tu quy";
			break;
		case 1:
			cout << "3 doi thong";
			break;
		default:
			cout << "Khong co bo dac biet";
		}
		cout << endl;
		/*
	for (int i = 0; i < n; i++) {
		cout << "=========\nPlayer #" << i + 1 << endl;
		PrintHand(hands[i], k);
		cout << "Points: " << CountPoints(hands[i][0], hands[i][1], hands[i][2]) << endl;
	}

	//Find winners
	int winners[MAX], max, num;
	num = FindWinners(hands, n, winners, max);
	cout << "Number of winners: " << num << endl;
	cout << "Winners' point: " << max << endl;
	cout << "List of winner(s):" << endl;
	for (int i = 0; i < num; i++)
		cout << "#" << winners[i] + 1 << "\t";
	cout << endl;*/
	return 0;
}

//Function definitions
//1. Tạo bộ bài tây gồm 52 lá
void CreateDeck(CARD deck[52])
{
	int n = 0;			//current card
	for (int shape = 1; shape <= 4; shape++)
		for (int num = 1; num <= 13; num++)
		{
			deck[n].shape = shape;
			deck[n].number = num;
			n++;
		}
}
//Function that gives a random number from 0 to n-1
int Random(int n) {
	return rand() % n;
}
//Function that swaps the content of 2 cards
void Swap(CARD& a, CARD& b) {
	CARD t = a;
	a = b;
	b = t;
}

//2. Xáo trộn thứ tự trong bộ bài (ngẫu nhiên)
void ShuffleDeck(CARD deck[52])
{
	//Swap at least 30 times, at most 52 times between two cards
	int no = 30 + Random(23);
	for (int i = 0; i < no; i++) {
		int v1 = Random(52);
		int v2 = Random(52);
		if (v1 != v2) Swap(deck[v1], deck[v2]);
	}

}
//3. Chia bài cho n người chơi, mỗi người cầm k lá bài
void DealCards(CARD deck[52], CARD hands[MAX][MAX], int n, int k)
{
	int v = 0;					//position in the deck
	for (int j = 0; j < k; j++)
		for (int i = 0; i < n; i++)
			hands[i][j] = deck[v++];
}
//4. Đếm nút bài cào: trả về số nút
//0 = bù, 10 = ba tây, 1-9 = số nút
int CountPoints(CARD b1, CARD b2, CARD b3)
{
	if (b1.number > 10 && b2.number > 10 && b3.number > 10)		//All figures
		return 10;
	if (b1.number > 10) b1.number = 10;
	if (b2.number > 10) b2.number = 10;
	if (b3.number > 10) b3.number = 10;
	return (b1.number + b2.number + b3.number) % 10;
}
//5. Xác định người chơi thắng cuộc?
//Trả về số lượng người thắng cuộc, stt của những người thắng, số nút cao nhất
int FindWinners(CARD hands[MAX][MAX], int n, int winners[], int& maxpoints)
{
	int count = 0;			//number of winners
	maxpoints = -1;
	//traverse all the players' hands
	for (int i = 0; i < n; i++)
	{
		int pts = CountPoints(hands[i][0], hands[i][1], hands[i][2]);
		if (pts > maxpoints) {				//we have one new winner
			maxpoints = pts;
			count = 1;
			winners[0] = i;
		}
		else if (pts == maxpoints) {		//we have one more winner
			winners[count++] = i;
		}
	}
	return count;
}
//6. In bộ bài ra màn hình để quan sát
void PrintDeck(CARD deck[52])
{
	for (int i = 0; i < MAX; i++) {
		PrintCard(deck[i]);
		cout << endl;
	}
}
//7. In thông tin 1 lá bài ra màn hình
void PrintCard(CARD b)
{
	char t1[] = { 'J', 'Q', 'K' };
	if (b.number == 1) cout << "A";
	else if (b.number > 10) cout << t1[b.number - 11];
	else cout << b.number;
	char t2[][20] = { ""," heart", " diamond", " club", " spade" };
	cout << t2[b.shape];
}
//8. In tay bài ra màn hình để quan sát
void PrintHand(CARD hand[], int k)
{
	for (int i = 0; i < k; i++) {
		PrintCard(hand[i]);
		cout << endl;
	}
}
//9. Tính số điểm của 1 tay bài theo trò chơi xì dzách
//Tay bài có từ 2 tới 5 lá
//Hàm trả về 23 nếu tay bài có đúng 2 quân A
//Hàm trả về 22 nếu tay bài có đúng 2 quân, trong đó có 1A và 1 hình (hoặc 10)
//Trường hợp còn lại quân hình tính 10, quân A có thể tính 1, 10 hoặc 11 sao cho có lợi nhất
//Nếu tổng số nút của các lá bài > 21, hàm trả về 0
//Ngược lại trả về tổng số nút của các lá bài
int BlackJack(CARD hand[], int k) {
	CARD t[MAX];     //Mảng tạm
	memcpy(t, hand, k * sizeof(CARD));     //tạo bản photocopy
	//Đổi tất cả quân hình trong tay bài thành quân 10 (tính 10 điểm )
	for (int i = 0; i < k; i++)
	if (t[i].number > 10) t[i].number = 10;
	//Xử lí tính điểm 
	if (k == 2) {   //tay bài có 2 lá
		if (t[0].number == 1  && t[1].number == 1) return 24;
	}
	return 0;
}
//10. Sắp xếp các lá bài trong tay bài tăng dần theo quy tắc bài "Tiến Lên miền Nam"
//Nhỏ nhất là quân 3 bích, lớn nhất là quân 2 cơ
void SortHand(CARD hand[], int k) {
	//B1. Đổi toàn bộ quan A và quân 2 (nếu có) thành 14 và 15
	for (int i = 0; i < k; i++) {
		if (hand[i].number < 3) hand[i].number += 13;
	}
	//B2. Sắp tay bài tăng dần theo nút, nếu bằng nút thì giảm theo chất
	for (int i = 0; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			if ((hand[i].number > hand[j].number) ||
				(hand[i].number == hand[j].number) && (hand[i].shape < hand[j].shape))
				swap(hand[i], hand[j]);
		}
	}
	//B3. Phục hồi lại quân A và 2 (nếu có)
	for (int i = 0; i < k; i++) {
		if (hand[i].number > 13) hand[i].number -= 13;
	}
}
//11. Hàm kiểm tra xem 1 tay bài (gồm k lá) có chứa loại nào sau đây không
//Nếu có sảnh rồng (13 lá khác nút) trả về 6
//Nếu có 4 quân 2, trả về 5
//Nếu có 6 đôi, trả về 4
//Nếu có 4 đôi thông trả về 3
//Nếu có tứ quý (ko phải tứ quý 2) trả về 2
//Nếu có 3 đôi thông trả về 1
//Các trường hợp khác trả về 0
int CheckTienLen(CARD hand[], int k)
{
	int count[16] = { 0 };

	// Đếm số lượng từng nút bài
	for (int i = 0; i < k; i++) {
		int num = hand[i].number;

		// Đổi A -> 14, 2 -> 15 để tiện xử lí
		if (num == 1) num = 14;
		else if (num == 2) num = 15;

		count[num]++;
	}

	// ===== 1. Sảnh rồng =====
	// Có đủ từ 3 -> A (13 lá khác nhau)
	bool sanhRong = true;
	for (int i = 3; i <= 15; i++) {
		if (count[i] != 1) {
			sanhRong = false;
			break;
		}
	}
	if (sanhRong) return 6;

	// ===== 2. 4 quân 2 =====
	if (count[15] == 4) return 5;

	// ===== 3. 6 đôi =====
	int pairs = 0;
	for (int i = 3; i <= 15; i++) {
		if (count[i] >= 2) pairs++;
	}
	if (pairs >= 6) return 4;

	// ===== 4. 4 đôi thông =====
	for (int i = 3; i <= 11; i++) {
		if (count[i] >= 2 &&
			count[i + 1] >= 2 &&
			count[i + 2] >= 2 &&
			count[i + 3] >= 2)
			return 3;
	}

	// ===== 5. Tứ quý (không tính tứ quý 2) =====
	for (int i = 3; i <= 14; i++) {
		if (count[i] == 4)
			return 2;
	}

	// ===== 6. 3 đôi thông =====
	for (int i = 3; i <= 12; i++) {
		if (count[i] >= 2 &&
			count[i + 1] >= 2 &&
			count[i + 2] >= 2)
			return 1;
	}

	return 0;
}