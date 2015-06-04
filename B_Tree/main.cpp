#include "B_Tree.h"

int main(){
	BTree b;
	int N = 20;
	for(int i = 0; i < N; i++)
		b.insert(i);
	b.Visit();
	cout << endl;
	b.remove(1);
	b.Visit();
	return 0;
}