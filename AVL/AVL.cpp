#include "AVL.h"

AVL::AVL(const ref& a){
	_root = a;
}

AVL& AVL::operator= (const ref& a){
	_root = a;
	return *this;
}

ref getNode(int key){
	ref p = new Node;
	p->bal = 0;
	p->key = key;
	p->left = p->right = NULL;
	return p;
}

/* -------------------------------------------------- Rotate -------------------------------------------------- */
void AVL::rotateLL(ref &p){
	ref p1 = p->left;
	p->left = p1->right;
	p1->right = p;
	// update the balance index
	if(p1->bal == 0){
		p->bal  = -1;
		p1->bal =  1;
	}
	else
		p1->bal = p->bal = 0;  
	p = p1;
}
void AVL::rotateRR(ref &p){
	ref p1 = p->right;
	p->right = p1->left;
	p1->left = p;
	if(p1->bal == 0){
		p->bal = 1;
		p1->bal = -1;
	}
	else
		p->bal = p1->bal = 0; // all node is balanced
	p = p1;
}
void AVL::rotateLR(ref &p){
	ref p1 = p->left;
	ref p2 = p1->right;
	p->left = p2->right;
	p2->right = p;
	p1->right = p2->left;
	p2->left = p1;
	switch(p2->bal){
	case -1:
		p->bal = 1;
		p1->bal = 0;
		break;
	case 0:
		p->bal = p1->bal = 0; break;
	case 1:
		p->bal = 0;
		p1->bal = -1;
	}
	p2->bal = 0;
	p = p2;
}
void AVL::rotateRL(ref &p){
	ref p1 = p->right;
	ref p2 = p1->left;
	p->right = p2->left;
	p2->left = p;
	p1->left = p2->right;
	p2->right = p1;
	switch(p2->bal){
	case 1:
		p->bal = -1;
		p1->bal = 0;
		break;
	case 0:
		p->bal = p1->bal = 0; break;
	case -1:
		p->bal = 0;
		p1->bal = 1;
	}
	p2->bal = 0;
	p = p2;
}
int AVL::balanceLeft(ref& p){
	ref p1 = p->left;
	switch(p1->bal){
	case -1: rotateLL(p); return 2;
	case 0: rotateLL(p); return 1;
	case 1: rotateLR(p); return 2;
	}
	return 0;
}
int AVL::balanceRight(ref& p){
	ref p1 = p->right;
	switch(p1->bal){
	case -1: rotateRL(p); return 2;
	case 0: rotateRR(p); return 1;
	case 1: rotateRR(p); return 2;
	}
	return 0;
}

/* -------------------------------------------------- Insertion -------------------------------------------------- */
int AVL::searchAdd(ref &x, int key){
	int res;
	if(x){
		if(x->key == key) return false;
		if(key < x->key){
			res = searchAdd(x->left, key);
			if(res < 2) return res;
			switch(x->bal){
			case 1: x->bal = 0; return 1;
			case 0: x->bal = -1; return 2;
			case -1: balanceLeft(x); return 1;
			}
		}
		else{ // key >= x->key
			res = searchAdd(x->right, key);
			if(res < 2) return res;
			switch(x->bal){
			case -1: x->bal = 0; return 1;
			case 0: x->bal = 1; return 2;
			case 1: balanceRight(x); return 1;
			}
		}
	}
	x = new Node;
	if(x == NULL) return -1; // do not have enough memory
	x->key = key;
	x->bal = 0;
	x->left = x->right = NULL;
	return 2;
}

void AVL::insert(int key){
	searchAdd(_root, key);
}

/* -------------------------------------------------- Deletion -------------------------------------------------- */
void balance1(ref &p, int &h) {
	ref p1, p2;
	int b1, b2;
	switch(p->bal){
	case -1: p->bal = 0; break;
	case 0:
		p->bal = 1;
		h = 0;
		break;
	case 1:
		p1 = p->right;
		b1 = p1->bal;
		if(b1 >= 0){ // RR
			p->right = p1->left;
			p1->left = p;
			// update balance index
			if(b1 == 0){
				p->bal = 1;
				p1->bal = -1;
				h = 0;
			}
			else{
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else { // RL
			p2 = p1->left;
			b2 = p2->bal;
			p1->left = p2->right;
			p2->right = p1;
			p->right = p2->left;
			p2->left = p;
			if(b2 == 1)
				p->bal = -1;
			else
				p->bal = 0;
			if(b2 == -1)
				p1->bal = 1;
			else
				p1->bal = 0;
			p = p2;
			p2->bal = 0;
		}
	}
}
void balance2(ref &p, int &h){
	ref p1, p2;
	int b1, b2;
	switch (p->bal) {
	case 1:
		p->bal = 0;
		break;
	case 0:
		p->bal = -1;
		h = 0;
		break;
	case -1:
		p1 = p->left;
		b1 = p1->bal;
		if (b1 <= 0) { // LL
			p->left = p1->right;
			p1->right = p;
			if (b1 == 0) {
				p->bal = -1;
				p1->bal = 1;
				h = 0;
			}
			else {
				p->bal = 0;
				p1->bal = 0;
			}
			p = p1;
		}
		else { // LR
			p2 = p1->right;
			b2 = p2->bal;
			p1->right = p2->left;
			p2->left = p1;
			p->left = p2->right;
			p2->right = p;
			if (b2 == -1) p->bal = 1;
			else p->bal = 0;
			if (b2 == 1) p1->bal = -1;
			else p1->bal = 0;
			p = p2;
			p2->bal = 0;
		}
	}
}
void del(ref &q, ref &r, int &h){
	if(r->right){
		del(q, r->right, h);
		if(h) balance2(r, h);
	}
	else{
		q->key = r->key;
		q = r;
		r = r->left;
		h = 1;
	}
}
void searchDelete(int x, ref &p, int &h) {
	ref q;
	if (p == NULL) // Không có
		h = 0;
	else
		if (x < p->key) {
			searchDelete(x, p->left, h);
			if (h)
				balance1(p, h);
		}
		else
			if (x > p->key) {
				searchDelete(x, p->right, h);
				if (h)
					balance2(p, h);
			}
			else {
				q = p;
				if (q->right == NULL) {
					p = q->left;
					h = 1;
				}
				else
					if (q->left == NULL) {
						p = q->right;
						h = 1;
					}
					else {
						del(q, p->left, h);
						if (h)
							balance1(p, h);
					}
					delete q;
			}
}

void AVL::remove(int key){
	int h;
	searchDelete(key, _root, h);
}

/* -------------------------------------------------- Visit -------------------------------------------------- */
void AVL::PreOrder(void (*action)(ref& x)){
	if(_root == NULL) return;
	action(_root);
	AVL tmp = _root->left;
	tmp.PreOrder(action);
	tmp = _root->right;
	tmp.PreOrder(action);
}

void AVL::InOrder(void (*action)(ref& x)){
	if(_root == NULL) return;
	AVL tmp = _root->left;
	tmp.InOrder(action);
	action(_root);
	tmp = _root->right;
	tmp.InOrder(action);
}

void AVL::PostOrder(void (*action)(ref& x)){
	if(_root == NULL) return;
	AVL tmp = _root->left;
	tmp.PostOrder(action);
	tmp = _root->right;
	tmp.PostOrder(action);
	action(_root);
}