#ifndef _BST_H
#define _BST_H

#define BLACK 1
#define RED 2

typedef struct Node* ref;
struct Node{
	int key;
	int color;
	ref parent;
	ref left;
	ref right;
	Node(){}
	Node(bool){
		key = -1;
		color = BLACK;
		parent = left = right = this;
	}
};

class BST{
	ref _root;
	static ref _nil;
	void leftRotate(ref x);
	void rightRotate(ref x);
	// method for insert
	bool findInsert(ref x);
	void ins_FixUp(ref x);
	void ins_leftAdjust(ref &x);
	void ins_rightAdjust(ref &x);

	// method for delete
	ref findDel(int key);
	ref TreeSuccessor(ref x);
	void del_FixUp(ref x);
	void del_leftAdjust(ref &x);
	void del_rightAdjust(ref &x);

public:
	BST();
	BST(const ref node);
	BST& operator= (const ref node);
	bool insert(int key);
	bool remove(int key);
	void PreOrder(void (*action)(ref&));
	void InOrder(void (*action)(ref&));
	void PostOrder(void (*action)(ref&));
};

#endif