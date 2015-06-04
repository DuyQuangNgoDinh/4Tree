#include "BST.h"
#include <iostream>
using namespace std;

void print(ref& a){
	cout << a->key << " ";	
}

int main(void){
	BST t;
	int N = 10;
	for(int i = 0; i < N; i++)
		t.insert(i);
	t.PostOrder(print);
	cout << endl;
	return 0;
}