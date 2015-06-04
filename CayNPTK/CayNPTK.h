/****************************************************
*	Tên: Ngô Đình Duy Quang							*
*	MSSV: 1312458									*
*	Bài tập: Xây dựng cây nhị phân tìm kiếm			*
*	Môn: Cấu trúc dữ liệu và giải thuật				*
*	Ngày: 16/11/2014								*
*****************************************************/

#ifndef _NPTK_H
#define _NPTK_H
#include <iostream>
#include <conio.h>
using namespace std;

typedef struct Node* ref;
struct Node{
	int key;
	ref left;
	ref right;
};

// pre-order travel
void PreOrder(ref root, void(*action)(ref&)){
	if(root == NULL) return;
	action(root);
	PreOrder(root->left, action);
	PreOrder(root->right, action);
}

// in-order travel
void InOrder(ref root, void(*action)(ref&)){
	if(root == NULL) return;
	InOrder(root->left, action);
	action(root);
	InOrder(root->right, action);
}

// post-order travel
void PostOrder(ref root, void(*action)(ref&)){
	if(root == NULL) return;
	PostOrder(root->left, action);
	PostOrder(root->right, action);
	action(root);
}

int choice(){
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	return choice;
}

void out(ref& p){
	cout << p->key << " ";
}

void freeNode(ref& p){
	if(p) delete p;
}

ref getNode(int key){
	ref p = new Node;
	p->key = key;
	p->left = p->right = NULL;
	return p;
}

class NPTK{
	ref _root;
	void delNode(ref& r, ref& p){
		ref tmp = r;
		ref prev = NULL;
		while(tmp->right){
			prev = tmp;
			tmp = tmp->right;
		}
		p->key = tmp->key;
		if(prev) prev->right = tmp->left;
		else p->left = tmp->left;
		p = tmp;
	}

public:
	NPTK(): _root(NULL) {}
	~NPTK(){
		travel(3, freeNode);
	}
	bool search(int key){
		ref p = _root;
		while(p){
			if(key == p->key)
				return 1;
			if(key > p->key)
				p = p->right;
			else
				p = p->left;
		}
		return 0;
	}

	void remove(int key){
		if(_root == NULL) return;
		ref p = _root;
		ref prev = NULL;
		while(p){
			if(p->key == key) break;
			if(p->key < key){
				prev = p;
				p = p->right;
			}
			else{
				prev = p;
				p = p->left;
			}
		}

		if(p){ // tồn tại nút có giá trị cần xóa
			if(prev != NULL){ // prev trỏ tới nút cha của p
				if(p->left == NULL)
					prev = p->right;
				else
					if(p->right == NULL)
						prev = p->left;
					else{ // p đang có hai nhánh
						delNode(p->left, p); // tìm lá phải nhất trên nhánh trái 
					}
				delete p;
			}
		}
	}

	void insert(int data){
		if(_root == NULL){
			_root = getNode(data);
			return;
		}
		ref p = _root;
		ref prev = NULL;
		while(p){
			if(p->key < data){
				prev = p;
				p = p->right;
			}
			else if(p->key > data){
				prev = p;
				p = p->left;
			}
			else return; // đã có nút có giá trị bằng data, không chèn thêm nữa
		}

		if(prev != NULL){
			ref tmp = getNode(data);
			if(prev->key < data) prev->right = tmp;
			else prev->left = tmp;
			return;
		}
	}

	void travel(int type, void(*action)(ref&)){
		switch(type){
		case 1:
			PreOrder(_root, action);
			break;
		case 2:
			InOrder(_root, action);
			break;
		case 3:
			PostOrder(_root, action);
		}
	}

	void run(){
		while (true){
			int value, type = choice();
			switch (type){
			case 1:
				cout << "Enter data: ";
				cin >> value;
				insert(value);
				break;
			case 2: 
				cout << "Enter data: ";
				cin >> value;
				remove(value); 
				break;
			case 3: 
				cout << "Enter data: ";
				cin >> value;
				cout << search(value) << endl;
				cout << "Press any key to continue!" << endl;
				getch();
				break;
			case 4:
				if(_root == NULL)
					cout << "Your tree is empty!";
				else{
					int t;
					cout << "View tree in 3 mode: " << endl;
					cout << "(1) PreOrder." << endl;
					cout << "(2) InOrder." << endl;
					cout << "(3) PostOrder." << endl;
					cout << "What mode do you want to view? "; cin >> t;
					travel(t, out);
				}
				cout << endl << "Press any key to continue" << endl;
				getch();
				break;
			case 5:
				return;
			default:
				cout << "Wrong key! Enter again!" << endl;
				cout << "Press any key to continue" << endl;
				getch();
			}
		}
	}
};
	
#endif