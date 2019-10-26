// USACO 2016 February Contest, Platinum
// Solution by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e3+10;
const ll inf = 1e14+10;

int n, k, v[maxn], a[maxn], opt[maxn];
ll dp[maxn][10], pref[maxn];

void solve(int ap, int l = 1, int r = n)
{
    if(l > r) return;

    int mid = (l+r)>>1;

    for(int i = opt[l - 1] ; i <= min(opt[r + 1], mid) ; ++i)
    {
        if(dp[i][ap - 1] + (1LL*i*(pref[mid - 1] - pref[i - 1])) > dp[mid][ap])
        {
            dp[mid][ap] = dp[i][ap - 1] + (1LL*i*(pref[mid - 1] - pref[i - 1])), opt[mid] = i;
        }
    }

    solve(ap, l , mid - 1); solve(ap, mid + 1, r);
}

int main()
{
    freopen("cbarn.in", "r", stdin);
	freopen("cbarn.out", "w", stdout);

    scanf("%d %d", &n, &k);

    for(int i = 1 ; i <= n ; ++i) scanf("%d", &v[i]);

    ll ans = inf;

    for(int b = 1 ; b <= n ; ++b)
    {
        ll sum = 0LL;

        for(int i = 0 ; i < n ; ++i)
        {
            int id = b + i;

            if(id > n) id -= n;

            a[i + 1] = v[id];
            pref[i + 1] = pref[i] + v[id];
        }
        
        for(int i = 1 ; i <= n ; ++i) sum += 1LL*a[i]*i;

        for(int i = 1 ; i <= k ; ++i)
        {
            for(int j = 1 ; j <= n ; ++j)
            {
                dp[j][i] = -inf;
            }
        }

        opt[0] = 1;
        opt[n + 1] = n;
        
        dp[1][1] = 0;

        for(int i = 2 ; i <= k ; ++i) solve(i);

        for(int i = 1 ; i <= n ; ++i)
        {
            ans = min(ans, sum - dp[i][k] - (1LL*i*(pref[n] - pref[i - 1])));
        }
    }

    cout << ans << '\n';

    return 0;
}
