/****************************************************
*	Tên: Ngô Đình Duy Quang							*
*	MSSV: 1312458									*
*	Bài tập: Xây dựng cây AVL						*
*	Môn: Cấu trúc dữ liệu và giải thuật				*
*	Ngày: 16/11/2014								*
*****************************************************/

#ifndef _AVL_H
#define _AVL_H
#include <iostream>
#include <conio.h>
using namespace std;

typedef struct Node* ref;
struct Node{
	int key;
	int bal;
	ref left;
	ref right;
};

class AVL{
	ref _root;
	void rotateRR(ref &p); // rotate Right-Right
	void rotateLL(ref &p); // rotate Left-Left
	void rotateLR(ref &p); // rotate Left-Right
	void rotateRL(ref &p); // rotate Right-Left
	int balanceLeft(ref& p);
	int balanceRight(ref& p);
	int searchAdd(ref& x, int key);
public:
	AVL(): _root(NULL) {}
	AVL(const ref& a);
	AVL& operator= (const ref& a);
	void insert(int key);
	void remove(int key);
	void PreOrder(void (*action)(ref& x));
	void InOrder(void (*action)(ref& x));
	void PostOrder(void (*action)(ref& x));
};
#endif