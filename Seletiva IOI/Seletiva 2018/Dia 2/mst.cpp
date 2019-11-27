// Seletiva 2018 - Dia 2 - Marcos Soluções Tecnológicas
// Solution by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10, maxm = 3e5+10;

typedef long long ll;

struct E
{
	int u, v, w;

	bool operator<(const E& o) const
	{
		return w < o.w;
	}

} ed[maxm];

struct node
{
	ll sum; int x;
} seg[4*maxn];/**/

int n, m, k, q, ft[maxn], rk[maxn];

int find(int u)
{
	if(ft[u] == u) return u;
	return ft[u] = find(ft[u]);
}

void join(int u, int v)
{
	if((u = find(u)) == (v = find(v))) return;

	if(rk[u] > rk[v]) swap(u, v);

	ft[u] = v;

	rk[v] += (rk[u] == rk[v]);
}

node join(node a, node b)
{
	return {a.sum + b.sum, a.x + b.x};
}

void upd(int p, int val, int u = 1, int l = 1, int r = maxn - 1)
{
	if(l == r) 
	{
		seg[u].sum += val;
		seg[u].x += (val < 0)? -1 : 1;

		return;
	}

	int mid = (l + r) >> 1;

	if(p <= mid) upd(p, val, 2*u, l, mid);
	else upd(p, val, 2*u+1, mid + 1, r);

	seg[u] = join(seg[2*u], seg[2*u+1]);
}

int kth(int k, int u = 1, int l = 1, int r = maxn - 1)
{
	if(seg[u].x == k) return seg[u].sum;

	if(l == r) return l*k;

	int mid = (l + r) >> 1;

	if(seg[2*u].x >= k) return kth(k, 2*u, l, mid);
	else return seg[2*u].sum + kth(k - seg[2*u].x, 2*u + 1, mid + 1, r);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> m >> k >> q;

	for(int i = 0 ; i < m ; ++i)
	{
		int a, b, c;
		cin >> a >> b >> c;

		ed[i] = {a, b, c};
	}

	for(int i = 1 ; i <= n ; ++i) ft[i] = i;

	sort(ed, ed+m);
		
	int qtd = 0;

	for(int i = 0 ; i < m ; ++i)
	{
		int u = ed[i].u, v = ed[i].v, w = ed[i].w;

		if(find(u) != find(v))
		{
			join(u, v);
			qtd++;
			upd(w, w);
		}
	}

	for(int i = 0 ; i < k ; ++i)
	{
		int x;
		cin >> x;
		upd(x, x);
	}

	cout << kth(qtd) << "\n";

	for(int i = 0 ; i < q ; ++i)
	{
		int type, c;
		cin >> type >> c;

		if(type == -1) upd(c, -c);
		else upd(c, c);

		cout << kth(qtd) << "\n";
	}

}
