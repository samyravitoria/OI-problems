// USACO 2017 December Contest Gold - Barn Painting
// Samyra Almeida

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll maxn = 1e5+10, mod = 1e9+7;

ll n, k;
ll color[maxn];
vector<ll> graph[maxn];
ll dp[maxn][5];

ll solve(ll u, ll C, ll f)
{
	if(dp[u][C] != -1) return dp[u][C];
	
	ll r = 1LL;
	
	for(auto v: graph[u])
	{
		if(f == v) continue;
		ll p = 0;
		if(C == color[v]) return 0;
		else
		{	
			if(color[v] != -1) p = solve(v, color[v], u);
			else
				for(ll i = 1 ; i <= 3 ; ++i)
					if(C != i) p = (p + solve(v, i, u))%mod;
		}
		r *= p;
		r %= mod;		
	}

	return dp[u][C] = r%mod;
}


main()
{
	FILE *fin = fopen ("barnpainting.in", "r");
	FILE *fout = fopen("barnpainting.out", "w");
	
	fscanf(fin, "%lld %lld", &n, &k);

	for(ll i = 1 ; i < n ; ++i)
	{
		ll u, v;
		fscanf(fin, "%lld %lld", &u, &v);

		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	memset(color, -1, sizeof color);
	memset(dp, -1, sizeof dp);
	
	for(ll i = 0 ; i < k ; ++i)
	{
		ll node;
		fscanf(fin, "%lld %lld", &node, &color[node]);
	}
	
	ll rp = 0LL;

	if(color[1] != -1) rp = solve(1LL, color[1], 0LL);
	else
		for(ll i = 1 ; i <= 3 ; ++i) 
			rp = (rp + solve(1LL, i, 0LL)%mod)%mod;
	
	fprintf(fout, "%lld\n", rp%mod);
}
