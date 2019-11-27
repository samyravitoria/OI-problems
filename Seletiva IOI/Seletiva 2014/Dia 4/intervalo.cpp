// Seletiva 2014 - Dia 4 - Intervalo
// Solution by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10;

typedef long long ll;

struct node
{
	int v, w, sz;
	ll sum;

	node *l, *r;

	node(int value)
	{
		l = r = nullptr;
		v = value, w = rand(), sz = 1, sum = 1LL*value;
	}
};

typedef node *& prnode;
typedef node * pnode;

ll sum(pnode t) {return (t)? t->sum : 0;}
int sz(pnode t) {return (t)? t->sz : 0;}

void op(pnode t)
{
	if(t)
	{
		t->sum = sum(t->l) + sum(t->r) + 1LL*t->v;
		t->sz = sz(t->l) + sz(t->r) + 1;
	}
}

void split(pnode t, prnode l, prnode r, int pos, int add = 0)
{
	if(!t)
	{
		l = r = nullptr; 
		return;
	}

	//refresh(t);

	int p = add + sz(t->l);

	if(p >= pos) split(t->l, l, t->l, pos, add), r = t;
	else split(t->r, t->r, r, pos, p + 1) , l = t;

	op(t);
}

void merge(prnode t, pnode l, pnode r)
{
	//refresh(l); refresh(r);

	if(!l || !r) t = (l)? l : r;
	else if(l->w > r->w) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;

	op(t);
}

void insert(prnode t, int pos, int value)
{
	pnode t1, t2, aux;
	t1 = t2 = nullptr;

	aux = new node(value);

	split(t, t1, t2, pos);
	merge(t1, t1, aux);
	merge(t, t1, t2);
}

ll query(pnode t, int l, int r)
{
	pnode t1 = nullptr, t2 = nullptr, t3 = nullptr;

	split(t, t1, t2, r + 1);
	split(t1, t1, t3, l);

	ll ans = t3->sum;

	merge(t1, t1, t3);
	merge(t, t1, t2);

	return ans;
}

int n, q;

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n;

	pnode tree = nullptr;

	for(int i = 0 ; i < n ; ++i)
	{
		int x;
		cin >> x;

		insert(tree, i, x);
	}

	cin >> q;

	for(int i = 0 ; i < q ; ++i)
	{
		char c; int l, r;

		cin >> c >> l >> r;

		if(c == 'I') insert(tree, l, r);
		else cout << query(tree, l - 1, r - 1) << '\n';
	}
}
