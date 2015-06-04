/****************************************************
*	Tên: Ngô Đình Duy Quang							*
*	MSSV: 1312458									*
*	Bài tập: Xây dựng cây nhị phân tìm kiếm			*
*	Môn: Cấu trúc dữ liệu và giải thuật				*
*	Ngày: 16/11/2014								*
*****************************************************/

#include "AVL.h"

void print(ref& x){
	cout << x->key << " ";
}

int main(){
	AVL tree;
	int N = 10;
	for(int i = 0; i < N; i++)
		tree.insert(i);
	tree.PreOrder(print);
	tree.remove(7);
	cout << endl;
	tree.PreOrder(print);
	return 0;
}