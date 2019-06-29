/*
    CEOI 2017 - Task Chase
    Solving by Samyra Almeida
  
    Some notes: 
        - vet[u] = number of pigeons in the u statue.
    	
        - vis[u] = sum of the number of pigeons in the statues around u.
    	
        - Each statue is a node of a tree and a way between two statues is a edge.
  	
    I'll do a dynamic programming, in the follow way:
        - dp[u][i] = maximum difference of the number of pigeons that are seen by Tom and Jerry from the root (first statue of the way) 
	to the u statue, still having i crumbs, between the childrem of u.
    	
        - dp2[u][i] = second maximum difference (of a different node than dp[u][i]) of the number of pigeons that are seen by 
	Tom and Jerry from the root (first statue of the way) to the u statue, still having i crumbs, between the childrem of u.
    	
        - the dp's have 2 cases (for all i in range 1 to k), to a node v (child of u): 
			
            - if dp[u][i] < max(dp[v][i], dp[v][i] + vis[v] - vet[u]):
                update the dp2[u][i] = dp[u][i] and dp[u][i] = max(dp[v][i], dp[v][i] + vis[v] - vet[u]).
			
            - else if dp2[u][i] < max(dp[v][i], dp[v][i] + vis[v] - vet[u]):
                update the dp2[u][i] = max(dp[v][i], dp[v][i] + vis[v] - vet[u]).
	
    *To do the dp's we use a DFS in the tree, but for check the answer is necessary do all nodes as root with runs in O(n*n) 
    and this solution will receive TLE.
		
    So, rotate the tree in a smart way is the solution. But, how? Think a bit about it!
        - For all node u, do the your children v as root (for all i in range 1 to k): 
            - If the dp[u][i] == max(dp[v][i], dp[v][i-1] + vis[v] - vet[u]) the dp[u][i] depend of v:
                So, updade the dp[u][i] to dp2[u][i].
					
            - After, update de dp and dp2 of v, because now u is a children of v (for all i in range 1 to k): 
                - if dp[v][i] < max(dp[u][i], dp[u][i] + vis[u] - vet[v]):
                    update the dp2[u][i] = dp[u][i] and dp[u][i] = max(dp[u][i], dp[u][i] + vis[u] - vet[v]).
			
            - else if dp2[u][i] < max(dp[u][i], dp[u][i] + vis[u] - vet[v]):
                update the dp2[u][i] = max(dp[u][i], dp[u][i] + vis[u] - vet[v]).
		  	
            *To runs the above algorithm do a function much similar to DFS in a tree, and for give the answer, in the top of 
	    the function before go through the children of u, do (for all i in range 1 to k): 
		
            - Do it: ans = max({ans, dp[u][i], dp[u][i-1] + vis[u]}), in the other words, the maximum between the previus 
	    answer, the maximum difference of the number of pigeons that are seen by Tom and Jerry from the u to the some 
	    node v in the subtree of u still having i crumbs and the maximum difference of the number of pigeons that are 
	    seen by Tom and Jerry from the u to the some node v in the subtree of u still having i-1 crumbs (dropped a 
	    crumb in the u).
		
    To finish, just print the ans.
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
