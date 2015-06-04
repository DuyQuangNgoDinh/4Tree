#include "BST.h"
#include <iostream>
using namespace std;

ref getNode(int key, int color, ref nil){
	ref p = new Node;
	p->key = key;
	p->color = color;
	p->left = p->right = p->parent = nil;
	return p;
}

bool operator== (Node a, Node b){
	return a.key == b.key && a.color == b.color;
}

bool operator!= (Node a, Node b){
	return !(a == b);
}

ref BST::_nil = new Node(true);
BST::BST(){
	_root = BST::_nil;
}
BST::BST(const ref node){
	_root = node;
}

BST& BST::operator= (const ref node){
	_root = node;
	return *this;
}

/* -------------------------------------------------- Rotate -------------------------------------------------- */
void BST::leftRotate(ref x){
	ref y = x->right;
	x->right = y->left;
	if(y->left != BST::_nil)
		y->left->parent = x;
	y->parent = x->parent;

	if(x->parent == BST::_nil)
		_root = y;
	else
		if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	y->left = x;
	x->parent = y;
}

void BST::rightRotate(ref x){
	ref y = x->left;
	x->left = y->right;
	if(y->right == BST::_nil)
		y->right->parent = x;
	y->parent = x->parent;

	if(x->parent == BST::_nil)
		_root = y;
	else
		if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	y->right = x;
	x->parent = y;
}

/* -------------------------------------------------- Insertion -------------------------------------------------- */
bool BST::findInsert(ref x){
		ref y = BST::_nil;
		ref z = _root;
		while(z != BST::_nil){
			y = z;
			if(x->key < z->key)
				z = z->left;
			else
				if(x->key > z->key)
					z = z->right;
				else return 0; // insert value is exist
		}
		x->parent = y;
		if(y == BST::_nil)
			_root = x;
		else
			if(x->key < y->key)
				y->left = x;
			else
				y->right = x;
		return 1; // has been insert successfully
	}

void BST::ins_FixUp(ref x){
	while(x->parent->color == RED)
		if(x->parent == x->parent->parent->left) // if parent of x is left node of grand parent of x
			ins_leftAdjust(x);
		else
			ins_rightAdjust(x);
	_root->color = BLACK;
}

void BST::ins_leftAdjust(ref &x){
	ref p = x->parent; // parent of node x
	ref g = p->parent; // grand parent of node x
	ref u = g->right; // uncle of node x
	if(u->color == RED){
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;
		x = g;
	}
	else{
		if(x == p->right){
			x = p;
			leftRotate(x);
		}
		p->color = BLACK;
		g->color = RED;
		rightRotate(g);
	}
}

void BST::ins_rightAdjust(ref &x){
	ref p = x->parent;
	ref g = p->parent;
	ref u = g->left;
	if(u->color == RED){
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;
		x = g;
	}
	else{
		if(x == p->left){
			x = p;
			rightRotate(x);
		}
		p->color = BLACK;
		g->color = RED;
		leftRotate(g);
	}
}

bool BST::insert(int key){
	ref x = getNode(key, RED, _nil);
	bool check = findInsert(x);
	if(!check) return 0; // do not need to insert because key is exist
	ins_FixUp(x);
	return 1;
}

/* -------------------------------------------------- Deletion -------------------------------------------------- */
ref BST::findDel(int key){
	ref z = _root;
	while(z != BST::_nil){
		if(key == z->key) return z;
		if(key < z->key)
			z = z->left;
		else
			z = z->right;
	}
	return NULL;
}

ref BST::TreeSuccessor(ref x){
	ref z = x->left;
	ref y = z;
	while(z->right != BST::_nil){
		y = z;
		z = z->right;
	}
	return y;
}

void BST::del_FixUp(ref x){
	while((x->color == BLACK) && (x != _root))
		if(x == x->parent->left)
			del_leftAdjust(x);
		else
			del_rightAdjust(x);
	x->color = BLACK;
}

void BST::del_leftAdjust(ref &x){
	ref p = x->parent;
	ref w = p->right;
	if(w->color == RED){
		w->color = BLACK;
		p->color = RED;
		leftRotate(p);
		//p = x->parent;
		w = p->right;
	}

	if((w->right->color == BLACK) && (w->left->color == BLACK)){
		w->color = RED;
		x = p;
	}
	else{
		if(w->right->color == BLACK){
			w->left->color = BLACK;
			w->color = RED;
			rightRotate(w);
			w = p->right;
		}
		w->color = p->color;
		p->color = BLACK;
		w->right->color = BLACK;
		leftRotate(p);
		x = _root;
	}
}

void BST::del_rightAdjust(ref &x){
	ref p = x->parent;
	ref w = p->left;
	if(w->color == RED){
		w->color = BLACK;
		p->color = RED;
		rightRotate(p);
		//p = x->parent;
		w = p->left;
	}

	if((w->right->color == BLACK) && (w->left->color == BLACK)){
		w->color = RED;
		x = p;
	}
	else{
		if(w->left->color == BLACK){
			w->right->color = BLACK;
			w->color = RED;
			leftRotate(w);
			w = p->left;
		}
		w->color = p->color;
		p->color = BLACK;
		w->left->color = BLACK;
		rightRotate(p);
		x = _root;
	}
}

bool BST::remove(int key){
	ref z = findDel(key);
	if(z == BST::_nil) return 0;
	ref y = (z->left == BST::_nil) || (z->right == BST::_nil) ? z : TreeSuccessor(z);
	ref x = y->left == BST::_nil ? y->right : y->left;
	// update some connections
	x->parent = y->parent;
	if(y->parent == BST::_nil)
		_root = x;
	else
		if(y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;

	if(y != z){ // y is a replacement Node
		z->key = y->key;
		z->color = y->color;
	}
	if(y->color == BLACK) // the Black height is changed
		del_FixUp(x);
	delete y;
	return true;
}

/* -------------------------------------------------- Visit -------------------------------------------------- */
void BST::PreOrder(void (*action)(ref&)){
	if(_root == BST::_nil) return;
	action(_root);
	BST tmp = _root->left;
	tmp.PreOrder(action);
	tmp = _root->right;
	tmp.PreOrder(action);
}

void BST::InOrder(void (*action)(ref&)){
	if(_root == BST::_nil) return;
	BST tmp = _root->left;
	tmp.InOrder(action);
	action(_root);
	tmp = _root->right;
	tmp.InOrder(action);
}

void BST::PostOrder(void (*action)(ref&)){
	if(_root == BST::_nil) return;
	BST tmp = _root->left;
	tmp.PostOrder(action);
	tmp = _root->right;
	tmp.PostOrder(action);
	action(_root);
}