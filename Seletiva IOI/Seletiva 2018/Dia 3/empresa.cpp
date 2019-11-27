// Seletiva 2018 - Dia 3 - Empresa
// Solution by Samyra Almeida

#include <bits/stdc++.h>

#define F first
#define S second
#define int long long 

using namespace std;

const int maxn = 1e5+10;

typedef pair<int, int> ii;

int n, g[maxn], c[maxn], d[maxn], value[maxn], H, ft[maxn];
vector<int> graph[maxn];
vector<ii> h[maxn];

void dfs(int u)
{
	value[u] = 1;

	for(int v: graph[u])
	{
		d[v] = d[u] + 1;
		H = max(H, d[v]);

		h[d[v]].push_back({c[v], v});

		dfs(v);

		value[u] = max(value[v] + 1, value[u]);
	}
}

void bfs()
{
	for(int i = H ; i >= 1 ; --i)
	{
		sort(h[i].begin(), h[i].end());

		for(int j = 0 ; j < h[i].size() ; ++j)
		{
			int u = h[i][j].S;
			int tec = h[i][j].F;

			int x = (j > 0)? value[h[i][j - 1].S] + 1 : 0;

			value[u] = max({value[u], x});

			value[ft[u]] = max(value[ft[u]], value[u] + 1);
		}
	}
}

int32_t main()
{
	cin >> n;

	for(int i = 2 ; i <= n ; ++i)
	{
		cin >> g[i];

		graph[g[i]].push_back(i);
		ft[i] = g[i];
	}

	for(int i = 1; i <= n ; ++i) cin >> c[i];

	dfs(1);

	bfs();

	long long ans = 0LL;

	for(int i = 1 ; i <= n ; ++i)
	{
		 //cout << value[i] << "\n";
		 ans += value[i];

	}

	cout << ans << "\n";
} 
