// OBI 2015 - Fila 
// Solution with Treap
// Solved by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

struct node
{
	node *l, *r;
	int v, w, M, sz;

	node(int vv)
	{
		l = r = nullptr;
		v = M = vv, w = rand(),sz = 1;
	}
};

typedef node * pnode;
typedef node *& prnode;

int n, q;

int sz(pnode t){return (t)? t->sz : 0;}
int M(pnode t){return (t)? t->M : 0;}

void op(pnode t)
{
	if(t)
	{
		t->sz = sz(t->l) + sz(t->r) + 1;	
		t->M = max({M(t->l), M(t->r), t->v});	
	}
}

void split(pnode t, prnode l, prnode r, int pos, int add = 0)
{
	if(!t)
	{
		l = r = nullptr;
		return;
	}

	int p = add + sz(t->l);

	if(p >= pos) split(t->l, l, t->l, pos, add), r = t;
	else split(t->r, t->r, r, pos, p + 1), l = t;

	op(t);
}

void merge(prnode t, pnode l, pnode r)
{
	if(!l || !r) t = (l)? l : r;
	else if(l->w > r->w) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;

	op(t);
}

void insert(prnode t, int pos, int v)
{
	pnode t1 = nullptr, t2 = nullptr, aux = new node(v);

	split(t, t1, t2, pos);
	merge(t1, t1, aux);
	merge(t, t1, t2);
}

int search(pnode t, int pos, int add = 0)
{
	if(!t) return 0;

	int px = add + sz(t->l);
	//cout << px << " " << t->v << "\n";
	if(px == pos) return t->v;
	else if(px > pos) return search(t->l, pos, add);
	else return search(t->r, pos, px + 1);
}

void output(pnode t, int add = 0)
{
	if(!t) return;

	int p = add + sz(t->l);

	output(t->l, add);
	cout << t->v << " " << t->M << " " << sz(t) << '\n';
	output(t->r, add + sz(t->l) + 1);
}

int query(pnode t, int v, int add = 0)
{
	if(!t) return -1;
	if(t->M <= v) return -1;

	int px = add + sz(t->l);

	//cout << px << " " << t->M << "\n";

	if(!t->l && !t->r) return px;

	if(t->r && t->r->M > v) return query(t->r, v, px + 1);
	if(t->v > v) return px;
	if(t->l && t->l->M > v) return query(t->l, v, add);

	return -1;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> n;

	pnode treap = nullptr;

	for(int i = 0 ; i < n ; ++i)
	{
		int x;
		cin >> x;

		insert(treap, i, x);
	}

	cin >> q;

	for(int i = 0 ; i < q ; ++i)
	{
		int type, j, x;
		cin >> type >> j >> x;

		if(type)
		{
			pnode t1 = nullptr, t2 = nullptr;

			int h = search(treap, j - 1);

			split(treap, t1, t2, j - 1);

			cout << query(t1, x + h) + 1 << "\n";

			merge(treap, t1, t2);
		}
		else insert(treap, j, x);
	}

	return 0;
}
