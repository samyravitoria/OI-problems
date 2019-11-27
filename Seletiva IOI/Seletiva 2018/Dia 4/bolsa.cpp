// Seletiva 2018 - Dia 4 - Bolsa de Brinquedos
// Solution by Samyra Almeida

#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

const int maxn = 1e6+10, inf = 1e9+10;

typedef pair<int, int> ii;

int n, m, k, q, t[maxn], c[maxn], seg[4*maxn];
ii kras[maxn];

long long ans[maxn];

vector<int> pos[maxn], ee[maxn];
map<int, int> mk[maxn];

void upd(int p, int val, int u = 1, int l = 1, int r = n)
{
	if(l == r)
	{
		seg[u] = min(seg[u], val);

		return;
	}

	int mid = (l+r)>>1;

	if(p <= mid) upd(p, val, 2*u, l, mid);
	else upd(p, val, 2*u+1, mid + 1, r);

	seg[u] = min(seg[2*u], seg[2*u+1]);
}

int query(int a, int b, int u = 1, int l = 1, int r = n)
{
	if(b < l || r < a) return inf;

	if(a <= l && r <= b) return seg[u];

	int mid = (l+r) >> 1;

	return min(query(a, b, 2*u, l, mid), query(a, b, 2*u+1, mid + 1, r));
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> m >> k;

	for(int i = 1 ; i <= m ; ++i) cin >> c[i];

	for(int i = 1 ; i <= n ; ++i)
	{
		cin >> t[i];
		
		pos[t[i]].push_back(i);
		mk[t[i]][i] = pos[t[i]].size();
	}

	cin >> q;

	for(int i = 0 ; i < 4*maxn ; ++i) seg[i] = inf;

	for(int i = 0 ; i < q ; ++i)
	{
		cin >> kras[i].F >> kras[i].S;

		ee[kras[i].S].push_back(i);
		ans[i] = -1;
	}

	for(int i = 1 ; i <= n ; ++i)
	{
		if(mk[t[i]][i] >= k) upd(pos[t[i]][mk[t[i]][i] - k], c[t[i]]);

		for(int x: ee[i])
		{
			int l = kras[x].F, r = kras[x].S, a = query(l, r);

			if(a != inf) ans[x] = (1LL)*a*k;
		}
	}

	for(int i = 0 ; i < q ; ++i) cout << ans[i] << "\n";
}
