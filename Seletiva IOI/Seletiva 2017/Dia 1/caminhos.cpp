// Seletiva 2017 - Dia 1 - Caminhos Mínimos
// Solution by Samyra Almeida

#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

const int maxn = 1e4+10, inf = 0x3f3f3f3f;
const ll minf = 1e14;

struct node
{
	ll w;
	int d, u;

	bool operator<(const node& o) const
	{
		if(w != o.w) return w > o.w;
		else return d > o.d;
	}
};

int n, m, mark[maxn], h[maxn];
bool vis[maxn];
vector<ii> graph[maxn];

void bfs(int u)
{
	queue<ii> fl;

	fl.push({0, 1});

	while(!fl.empty())
	{
		int u = fl.front().S;
		int d = fl.front().F;

		fl.pop();

		if(mark[u]) continue;

		mark[u] = 1;
		h[u] = d;

		for(ii x: graph[u])
		{
			int v = x.F;

			if(mark[v]) continue;

			fl.push({d + 1, v});
		}
	}
}

li dt[maxn];
node ed[2*maxn];

bool dijkstra(int k)
{
	for(int i = 0 ; i < maxn ; ++i)
	{
		dt[i] = {minf, inf};
		vis[i] = 0;
	}

	vector<ii> g[maxn];

	for(int i = 0 ; i < m ; ++i)
	{
		g[ed[i].w].push_back({ed[i].d, ed[i].u + k});
		g[ed[i].d].push_back({ed[i].w, ed[i].u + k});
	}

	dt[1] = {0, 0};

	priority_queue<node> pq;

	pq.push({0, 0, 1});

	while(!pq.empty())
	{
		ll w = pq.top().w;
		int d = pq.top().d;
		int u = pq.top().u;

		pq.pop();

		if(w > dt[u].F || vis[u]) continue;

		vis[u] = 1;

		for(ii x: g[u])
		{
			int v = x.F;
			ll W = 1LL*x.S + w;

			if(W > dt[v].F) continue;

			if(W < dt[v].F) dt[v] = {W, d + 1};
			else if(W == dt[v].F && dt[v].S > d + 1) dt[v].S = d + 1;

			pq.push({dt[v].F, dt[v].S, v});
		}
	}

	for(int i = 1 ; i <= n ; ++i)
	{
		if(h[i] != dt[i].S) return false;
	}

	return true;
}

int search()
{
	int ans = -1, ini = 0, fim = 1e9, mid;

	while(ini <= fim)
	{
		mid = (ini + fim) >> 1;
	
		if(dijkstra(mid))
		{
			ans = mid;
			fim = mid - 1;
		}
		else ini = mid + 1;
	}

	return ans;
}

int main()
{
	ios::sync_with_stdio(false); cout.tie(nullptr); cout.tie(nullptr);

	cin >> n >> m;

	for(int i = 0 ; i < m ; ++i)
	{
		int u, v, w;

		cin >> u >> v >> w;

		ed[i] = {u, v, w};

		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}

	bfs(1);

	cout << search() << '\n';
}
