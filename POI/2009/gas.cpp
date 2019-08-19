/*
    POI 2009 - Task Fire Extinguishers (gas)
    
    Notes:
        - qtd[u][i] = number of nodes in u subtree that are at a distance of i corridors of u and were not covered by any extinguisher
        - rest[u][i] = number of nodes, which are at most i corridors of u, which can still be covered.
	
    Solution: 
        - To calculate qtd[u][i], for each i between 1 and k, let's do qtd[u][i] + = qtd[v][i-1], for every v belonging to the 
        subtree of u, because the nodes that were at a distance x-1 from my son is at a distance x from me.
		
        - Then, if qtd[u][k] > 0, we need to add extinguishers to this node, so we add the required number of extinguishers 
        to cover the qtd[u][k] nodes. And we added to the rest[u][k] the amount of nodes that can still be covered by these 
        extinguishers.
		
        - So if qtd[u][k] > 0, we need to add fire extinguishers to this node, then variable add will get the number of 
        extinguishers needed to cover the qtd[u][k] nodes, remember that to do resp += add.
		
        - Then we add to the rest[u][k] += add * s, ie the number of nodes that can be covered and that are at most K corridors 
        away from node u.
		
        - Finally, in dfs, for each level i between 0 and k, we try to cover the qtd[u][i] with the rest[u][i].
		
        - And then, for every level i between 0 and k-1, we try to cover the qtd[u][i] nodes with the rest[u][i + 1], that is, 
        with the nodes that can still be covered and are one more distance from the corridor.

        - Finally, after sending an error message, some of which are not at most corridors of node R(root), to do that we just 
        do a loop in i, where i varies from Kkto 0, and for each interaction we do:
            * r + = rest[R][i], and if qtd[R][i] > r, we need to add more extinguishers to node R, so we do the same as in DFS,
            after of if, we do r - = qtd[R][i].
			
        - After the loop, just print the variable resp.

    Topic: DP in tree

    Solved by Samyra Almeida
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n, s, k;
ll qtd[maxn][30], rest[maxn][30], resp;

vector<int> graph[maxn];

void dfs(int u, int f)
{
	for(int v: graph[u])
	{
		if(v == f) continue;

		dfs(v, u);

		for(int i = 0 ; i < k ; ++i) qtd[u][i+1] += qtd[v][i];
		
		for(int i = k ; i >= 1 ; --i) rest[u][i-1] += rest[v][i];
	}

	qtd[u][0]++;

	ll add = qtd[u][k]/s;

	if(qtd[u][k]%s > 0)	add++;

	resp += add;
		
	rest[u][k] += add*s;
		
	for(int i = 0 ; i <= k ; ++i) 
	{
		ll dif = min(qtd[u][i], rest[u][i]);

		qtd[u][i] -= dif; rest[u][i] -= dif;
	}

	for(int i = 0 ; i < k ; ++i) 
	{
		ll dif = min(qtd[u][i], rest[u][i+1]);

		qtd[u][i] -= dif; rest[u][i+1] -= dif;
	}

}

int main()
{
	cin >> n >> s >> k;

	for(int i = 1 ; i < n ; ++i)
	{
		int u, v;
		cin >> u >> v;

		graph[v].push_back(u);
		graph[u].push_back(v);
	}

	dfs(1, 0);

	ll r = 0LL;

	for(int i = k ; i >= 0 ; --i)
	{
		r += rest[1][i];
		
		if(r < qtd[1][i])
		{
			ll add = (qtd[1][i] - r)/s;

			if((qtd[1][i] - r)%s) add++;

			resp += add;

			r += add*s;
		}

		r -= qtd[1][i];
	}

	cout << resp << "\n";
}
