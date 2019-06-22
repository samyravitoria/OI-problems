/*
  Solution by Samyra Almeida
  
  Let's do an LCA with a DFS and a sparse table and during DFS we will keep the distance from all nodes to the root.
  And for each of the Q queries, we will execute the following algorithm:
    - We add the distance between the first two cities in w (respose) and lca = LCA between them.
    - From the 3rd city, we add the distance between the LCA of the cities and the current city and update the LCA 
    between the LCA and the current city. In addition, we need to check if we do not add a few edges more than once, 
    by adding two vertices of the same subtree, we pass by sp (vector containing the cities that have already been 
    added) and create lca' = LCA more deeply between the current city and one of the cities that have already been 
    added. If lca' is different from LCA between all cities, it means that we add the distance from lca' to the LCA 
    twice then tiramps the distance between the lca' and LCA of w and add the current city to sp. Finally, let's 
    print the value of w.
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4+10, maxl = 20;

struct node
{
	int w, u;
};

int n, q, lv[maxn], dist[maxn], anc[maxn][maxl];

vector<node> graph[maxn];

void dfs(int u, int f)
{	
	lv[u] = lv[f] + 1;
	anc[u][0] = f;
	for(node a: graph[u])
	{
		int v = a.u;
		int w = a.w;

		if(v == f) continue;

		dist[v] = dist[u] + w;

		dfs(v, u);
	}
}

void table()
{
	memset(anc, -1, sizeof anc);

	dfs(0, 0);

	anc[0][0] = -1;
	
	for(int j = 1 ; j < maxl ; ++j)
	{
		for(int i = 0 ; i < n ; ++i)
		{
			if(anc[i][j-1] != -1)
			{
				anc[i][j] = anc[anc[i][j-1]][j-1];
			}
		}
	}
}

int LCA(int u, int v)
{
	if(lv[u] < lv[v]) swap(u, v);
	
	for(int i = maxl - 1 ; i >= 0 ; --i)
	{
		if(lv[u] - (1<<i) >= lv[v]) u = anc[u][i];
	}

	if(u == v) return u;

	for(int i = maxl - 1 ; i >= 0 ; --i)
	{
		if(anc[u][i] != anc[v][i] && anc[u][i] != -1 && anc[v][i] != -1)
		{
			u = anc[u][i];
			v = anc[v][i];
		}
	}

	return anc[u][0];
}

int main()
{
	cin >> n;

	for(int i = 1 ; i < n ; ++i)
	{
		int u, v, w;
		cin >> u >> v >> w;

		graph[u].push_back({w, v});
		graph[v].push_back({w, u});
	}

	table();

	cin >> q;

	for(int i = 0 ; i < q ; ++i)
	{
		int lca;
		
		cin >> lca;

		int w = 0;

		vector<int> sp;
		sp.push_back(lca);

		for(int j = 1 ; j < 5 ; ++j)
		{
			int u;
			cin >> u;

			w += dist[lca] + dist[u];

			lca = LCA(lca, u);
			
			w -= (dist[lca] + dist[lca]);
			
			if(j > 1)
			{
				int ll = lca;
				for(int v: sp)
				{
					int cc = LCA(u, v);
					if(ll != cc && lv[cc] > lv[ll]) ll = cc;
				}

				if(lca != ll) w -= dist[ll];
			}

			sp.push_back(u);
		}

		cout << w << "\n";
	}
}
