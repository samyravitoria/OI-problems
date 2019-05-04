// IOI 2012 - Ideal City
// Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

const ll maxn = 1e5+10, mod = 1e9;

struct point{
	ll x, y;
} p[maxn];

ll n, idnode, sub[maxn];
ll qtd[maxn], vis[maxn];
ll resp = 0LL;
map<ii, ll> mp, ck;
vector<ll> graphX[maxn], graphY[maxn];

bool ordX(point a, point b)
{
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}
bool ordY(point a, point b)
{
	if(a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

ll solveX(ll u)
{
	vis[u] = 1;
	
	for(auto v: graphX[u])
	{
		if(vis[v] == 1) continue;

		sub[v] = solveX(v);
		sub[u] += sub[v];

		resp = (resp + (sub[v])*1LL*(n - sub[v])%mod)%mod;
	}

	sub[u] += qtd[u];
	return sub[u];
}
ll solveY(ll u)
{
	vis[u] = 1;
	
	for(auto v: graphY[u])
	{
		if(vis[v]) continue;

		sub[v] = solveY(v);
		sub[u] += sub[v];

		resp = (resp + (sub[v])*1LL*(n - sub[v])%mod)%mod;
	}
	sub[u] += qtd[u];
	return sub[u];
}

int main()
{
	scanf("%lld", &n);

	for(ll i = 1 ; i <= n ; ++i)
	{
		scanf("%lld %lld", &p[i].x, &p[i].y);
		ck[ii(p[i].x, p[i].y)] = 1;
	}

	sort(p + 1, p + n + 1, ordX);

	for(ll i = 1 ; i <= n ; ++i)
	{
		if(p[i].x == p[i - 1].x && p[i].y == p[i - 1].y + 1)
		{
			mp[ii(p[i].x, p[i].y)] = idnode;
			qtd[idnode]++;
		}else{
			idnode++;
			qtd[idnode] = 1;
			mp[ii(p[i].x, p[i].y)] = idnode;
		}
	}

	for(ll i = 1 ; i <= n ; ++i)
	{
		if(ck[ii(p[i].x + 1, p[i].y)] == 1)
		{
			ll u = mp[ii(p[i].x, p[i].y)];
			ll v = mp[ii(p[i].x + 1, p[i].y)];
			
			graphX[u].push_back(v);
		}
		if(ck[ii(p[i].x - 1, p[i].y)] == 1)
		{
			ll u = mp[ii(p[i].x, p[i].y)];
			ll v = mp[ii(p[i].x - 1, p[i].y)];

			graphX[u].push_back(v);
		}
	}
	
	solveX(1);

	sort(p + 1, p + n + 1, ordY);

	memset(qtd, 0LL, sizeof qtd);
	memset(vis, 0LL, sizeof vis);
	memset(sub, 0LL, sizeof sub);

	idnode = 0LL;
	mp.clear();

	for(ll i = 1 ; i <= n ; ++i)
	{
		if(p[i].y == p[i - 1].y && p[i].x == p[i - 1].x + 1)
		{
			mp[ii(p[i].x, p[i].y)] = idnode;
			qtd[idnode]++;
		}else{
			qtd[++idnode] = 1;
			mp[ii(p[i].x, p[i].y)] = idnode;
		}
	}

	for(ll i = 1 ; i <= n ; ++i)
	{
		if(ck[ii(p[i].x, p[i].y + 1)] == 1)
		{
			graphY[mp[ii(p[i].x, p[i].y)]].push_back(mp[ii(p[i].x, p[i].y + 1)]);
		}
		if(ck[ii(p[i].x, p[i].y - 1)] == 1)
		{
			graphY[mp[ii(p[i].x, p[i].y)]].push_back(mp[ii(p[i].x, p[i].y - 1)]);
		}
	}
		
	solveY(1);

	printf("%lld\n", resp);
}
