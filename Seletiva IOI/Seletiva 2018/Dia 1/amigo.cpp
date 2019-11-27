// Seletiva 2018 - Dia 1 - Amigo Secreto
// Solution by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10, inf = 1e9+10;

typedef long long ll;

struct E
{
	int u, t;
} ed[maxn];

int n, grau[maxn], mk[maxn], ac[maxn], ae[maxn], dlt[maxn], mininum[maxn], mark[maxn];
vector<int > kras, cp[maxn], graph[maxn];

int vv, nc, comp[maxn];

bool find_begins(int u)
{
	mk[u] = 1;

	int v = ed[u].u;

	bool ok = false;

	if(mk[v] == 1)
	{
		vv = v;
		ok = true;
	}

	if(!ok && mk[v] == 0) ok = find_begins(v);

	if(grau[u] > 1 && ok) kras.push_back(u);

	if(vv == u) ok = false;

	mk[u] = 2;

	return ok;
}

void comps(int u)
{
	mk[u] = 1;
	comp[u] = nc;

	cp[nc].push_back(u);

	int v = ed[u].u;

	ac[v] = u, mininum[nc] = min(mininum[nc], ed[u].t);

	if(!mk[v]) comps(v);
}

int find_cicles(int u)
{
	mark[u] = 1;

	int v = ed[u].u;

	int ret = inf;

	if(mark[v] == 1 && mk[v] == 0) 
	{
		ret = ed[u].t;
	}

	if(mark[v] == 0 && ret == inf && mk[v] == 0) ret = find_cicles(v);

	if(ret != inf) ret = min(ret, ed[u].t);

	mark[u] = 2;

	return ret;
}


int main()
{	
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n;

	for(int i = 1 ; i <= n ; ++i)
	{
		cin >> ed[i].u >> ed[i].t;

		grau[ed[i].u]++;

		graph[ed[i].u].push_back(i);
	}

	for(int i = 1 ; i <= n ; ++i)
	{
		if(grau[i] > 1)
		{
			find_begins(i);
		}
	}

	memset(mk, 0, sizeof mk);

	for(int i = 0 ; i < maxn ; ++i) mininum[i] = inf;

	for(int x: kras)
	{
		if(!mk[x])
		{
			nc++;
			comps(x);
		}
	}

	ll ans = 0LL;
	
	for(int i = 1 ; i <= nc ; ++i)
	{
		for(int u: cp[i])
		{
			if(grau[u] <= 1) continue;

			int node = 0;

			for(int v: graph[u])
			{
				if(v == ac[u]) continue;

				node = (ed[v].t > ed[node].t)? v : node;

				ans += 1LL*ed[v].t;
			}

			ae[u] = node;

			ans -= 1LL*ed[node].t;
		}
	}

	for(int i = 1 ; i <= nc ; ++i)
	{
		if(cp[i].size() == 1)
		{
			ans += ed[cp[i][0]].t;

			continue;
		}

		ll best1 = 0LL, best2 = 0LL;

		for(int u: cp[i])
		{
			if(grau[u] <= 1) continue;

			ll b2 = best2 + min(((best2 > 0LL)? 1LL*ed[ae[u]].t : 1LL*inf), 1LL*ed[ac[u]].t);
			best2 = min(b2, best1 + 1LL*ed[ac[u]].t);

			best1 += 1LL*ed[ae[u]].t;
		}
		
		ans += min(best2, best1 + mininum[i]);
	}

	int qc = 0;
	ll rs = 0LL;
	for(int i = 1 ; i <= n ; ++i)
	{
		if(mark[i] == 0 && mk[i] == 0)
		{
			qc++;
			int a = find_cicles(i);
			if(a < inf) rs += 1LL*a;
		}
	}

	for(int i = 1 ; i <= n ; ++i)
	{
		if(mk[i] == 0 && grau[i] > 1)
		{	
			int node = 0;

			for(int u: graph[i])
			{
				node = (ed[u].t > ed[node].t)? u : node;

				ans += (1LL)*ed[u].t;
			}

			ans -= 1LL*ed[node].t;
		}
	}

	if(ans == 0 && qc == 1) cout << 0 << "\n";

	else cout << ans + rs << "\n";
}
