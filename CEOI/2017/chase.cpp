/*
  CEOI 2017 - Task Chase
  Solving by Samyra Almeida
  
  First, I'll do the array vis[], where vis[u] = sum of the number of pigeons in the statues around u. And with a dfs I'll do the 
  dp[u][i] = the biggest difference between the children of u, the number of pigeons that are seen by Tom and Jerry from the root 
  (first statue of the way) to the u statue, still having i crumbs and dp2[u][i] = the second biggest difference, from a child other 
  than u, to the number of pigeons that are seen by Tom and Jerry from the root (first statue of the path) to the x statue, still 
  having i crumbs.
  Now, I'll a recursive funcion, very similar wiht dfs, that have 2 parameters rotate(u, f) where u is the actual tree root and f is 
  the u "father". First I'll check dp[u][i] is the best answer for all i in the range 1 ... k. 
    
*/
 
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
const int maxn = 1e5+10, maxk = 110;
 
int n, k;
ll dp[maxn][maxk], dp2[maxn][maxk], ant[maxn][maxk], ans, vis[maxn], vet[maxn];
 
vector <int> graph[maxn];
 
void dfs(int u, int f = 0)
{
	for(int v: graph[u])
	{	
		if(v == f) continue;
		dfs(v, u);
 
		for(int i = 1 ; i <= k ; ++i)
		{
			ll val = max(dp[v][i-1] + vis[v] - vet[u], dp[v][i]);
		
			if(val > dp[u][i]) dp2[u][i] = dp[u][i], dp[u][i] = val;
			else if(val > dp2[u][i]) dp2[u][i] = val;
		}
	}
}
 
void rotate(int u, int f = 0)
{
	for(int i = 1 ; i <= k ; ++i)
	{
		ans = max({ans, dp[u][i], dp[u][i-1] + vis[u]});
	}
 
	for(int v: graph[u])
	{
		if(v == f) continue;
 
		for(int i = 1 ; i <= k ; ++i)
		{
			ant[u][i] = dp[u][i];
			
			ll val = max(dp[v][i], dp[v][i-1] + vis[v] - vet[u]);
 
			if(val == dp[u][i])
			{
				dp[u][i] = dp2[u][i];
			}
		}
 
		for(int i = 1 ; i <= k ; ++i)
		{
			ll val = max(dp[u][i], dp[u][i-1] + vis[u] - vet[v]);
 
			if(val > dp[v][i]) dp2[v][i] = dp[v][i], dp[v][i] = val;
			else if(val > dp2[v][i]) dp2[v][i] = val;
		}
 
		rotate(v, u);
 
		for(int i = 1 ; i <= k ; ++i) dp[u][i] = ant[u][i];
	}
}
 
int main()
{
	cin >> n >> k;
 
	for(int i = 1 ; i <= n ; ++i) cin >> vet[i];
 
	for(int i = 1 ; i < n ; ++i)
	{
		int u, v;
		cin >> u >> v;
 
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
 
	for(int i = 1 ; i <= n ; ++i)
	{
		for(int v: graph[i])
		{
			vis[i] += vet[v];
		}
	}
 
	dfs(1);
	rotate(1);
 
	cout << ans << '\n';
}
