#include "B_Tree.h"

BTree::BTree(const ref& a){
	_root = a;
}

/* -------------------------------------------------- Insertion -------------------------------------------------- */
void add(int r, ref a, bool &h, item &u, item &v){
	int i;
	if(a->m < nn){ // page is not full
		a->m ++;
		h = false;
		for(i = a->m; i >= r + 2; i--)
			a->e[i] = a->e[i - 1];
		a->e[r + 1] = u;
	}
	else{ // page a is full
		ref b = new page;
		if(r <= n){
			if(r == n)
				v = u;
			else{
				v = a->e[n];
				for(i = n; i >= r + 2; i--)
					a->e[i] = a->e[i - 1];
				a->e[r + 1] = u;
			}
			for(i = 1; i <= n; i++)
				b->e[i] = a->e[i + n];
		}
		else{
			r -= n;
			v = a->e[n + 1];
			for(i = 1; i <= r - 1; ++i)
				b->e[i] = a->e[i + n + 1];
			b->e[r] = u;
			for(i = r + 1; i <= n; ++i)
				b->e[i] = a->e[i + n];
		}
		a->m = b->m = n;
		b->e[0].p = v.p;
		v.p = b;
	}
}
void searchAdd(int x, ref a, bool &h, item& v){
	int r;
	ref q;
	item u;
	if(a == NULL){
		h = true;
		v.key = x;
		v.count = 1;
		v.p = NULL;
	}
	else{
		a->e[0].key = x; // sentinel
		for(r = a->m; a->e[r].key > x; r--);
		if(r && a->e[r].key == x){ // exist
			a->e[r].count++;
			h = false;
		}
		else{
			q = a->e[r].p;
			searchAdd(x, q, h, u);
			if(h) // a is pointing to a leaf-node
				add(r, a, h, u, v);
		}
	}
}

void BTree::insert(int key){
	ref q;
	bool h;
	item u;
	searchAdd(key, _root, h, u);
	if(h){
		q = _root;
		_root = new page;
		_root->m = 1;
		_root->e[0].p = q;
		_root->e[1] = u;
	}
}

/* -------------------------------------------------- Deletion -------------------------------------------------- */
void balance(ref c, ref a, int s, bool &h){
	int mc = c->m;
	ref b;
	int k, mb, i;
	if(s < mc){
		s++;
		b = c->e[s].p;
		mb = b->m;
		k = (mb - n + 1) / 2; // so phan tu chuyen giao
		a->e[n] = c->e[s]; // take element from parent node
		a->e[n].p = b->e[0].p;
		if(k > 0){
			for(i = 1; i < k; ++i)
				a->e[n + i] = b->e[i];
			c->e[s] = b->e[k];
			c->e[s].p = b;
			b->e[0].p = b->e[k].p;
			mb -= k;
			for(i = 1; i <= mb; ++i)
				b->e[i] = b->e[i + k];
			b->m = mb;
			a->m = (n - 1) + k;
			h = false;
		}
		else{
			for(i = 1; i <= n; ++i)
				a->e[n + i] = b->e[i];
			for(i = s; i <= mc - 1; ++i)
				c->e[i] = c->e[i + 1];
			a->m = nn;
			c->m = mc - 1;
			delete b;
		}
	}
	else{ // s = mc
		if(s == 1)
			b = c->e[0].p;
		else
			b = c->e[s - 1].p;
		mb = b->m + 1;
		k = (mb - n) / 2; // so phan tu chuyen giao
		if(k > 0){
			for(i = n - 1; i >= 1; --i)
				a->e[i + k] = a->e[i];
			a->e[k] = c->e[s];
			a->e[k].p = a->e[0].p;
			mb -= k;
			for(i = k - 1; i >= 1; --i)
				a->e[i] = b->e[i + mb];
			a->e[0].p = b->e[mb].p;
			c->e[s] = b->e[mb];
			c->e[s].p = a;
			b->m = mb - 1;
			a->m = (n - 1) + k;
			h = false;
		}
		else{
			b->e[mb] = c->e[s];
			b->e[mb].p = a->e[0].p;
			for(i = 1; i < n; ++i)
				b->e[i + mb] = a->e[i];
			b->m = nn;
			c->m = mc - 1;
			delete a;
		}
	}
}
void del(ref a, ref p, int r, bool &h){
	ref q = p->e[p->m].p;
	if(q){
		del(a, q, r, h);
		if(h)
			balance(p, q, p->m, h);
	}
	else{
		p->e[p->m].p = a->e[r].p;
		a->e[r] = p->e[p->m];
		p->m--;
		h = p->m < n;
	}
}
void searchDel(int x, ref a, bool &h){
	int r;
	ref q;
	if(a == NULL)
		h = false;
	else{
		a->e[0].key = x;
		for(r = a->m; a->e[r].key > x; r--);
		if(r == 0)
			q = a->e[0].p;
		else
			if(r && a->e[r].key == x)
				q = a->e[r - 1].p;
			else
				q = a->e[r].p;
		if(r && a->e[r].key == x){
			if(q == NULL){ // leaf page
				a->m--;
				h = a->m < n;
				for(int i = r; i <= a->m; i++)
					a->e[i] = a->e[i + 1];
			}
			else{
				del(a, q, r, h);
				if(h)
					balance(a, q, r - 1, h);
			}
		}
		else{
			searchDel(x, q, h);
			if(h) balance(a, q, r, h);
		}
	}
}

void BTree::remove(int key){
	bool h;
	searchDel(key, _root, h);
	if(h){
		if(_root->m == 0){
			ref q = _root;
			_root = q->e[0].p;
			delete q;
		}
	}
}

void BTree::Visit(){
	for(int i = 0; i < _root->m; i++)
		cout << _root->e[i + 1].key << " ";
	for(int i = 0; i <= _root->m; i++){
		BTree tmp = _root->e[i].p;
		if(tmp._root == NULL) continue;
		tmp.Visit();
	}
}