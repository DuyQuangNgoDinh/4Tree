#ifndef _B_TREE_H
#define _B_TREE_H
#include <iostream>
using namespace std;

const int n = 2;
const int nn = 2 * n;

typedef struct page* ref;
struct item{
	int key;
	int count;
	ref p;
};

struct page{
	int m; // number of key in this page
	item e[nn + 1];
};

class BTree{
	ref _root;
public:
	BTree(): _root(NULL){}
	BTree(const ref& a);
	void insert(int key);
	void remove(int key);
	void Visit();
};
#endif