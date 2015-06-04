/****************************************************
*	Tên: Ngô Đình Duy Quang							*
*	MSSV: 1312458									*
*	Bài tập: Xây dựng cây nhị phân tìm kiếm			*
*	Môn: Cấu trúc dữ liệu và giải thuật				*
*	Ngày: 16/11/2014								*
*****************************************************/

#include <iostream>
#include "CayNPTK.h"
using namespace std;

void showMenu(){
	cout << "-------------------- Hay lua chon 1 trong cac chuc nang sau --------------------\n";
	cout << "(1) Them 1 khoa." << endl;
	cout << "(2) Xoa 1 khoa." << endl;
	cout << "(3) Tim 1 khoa." << endl;
	cout << "(4) Duyet cay." << endl;
	cout << "(5) Thoat chuong trinh." << endl;
}

int main(){
	showMenu();
	NPTK tree;
	tree.run();
	return 0;
}