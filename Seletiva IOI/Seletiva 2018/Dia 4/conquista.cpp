// Seletiva 2018 - Dia 4 - Conquista
// Solution by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 3e3+1;
const ll inf = 1e9+10;
int n, m, mat[maxn][maxn];

int dp[maxn][maxn], pref[maxn], suf[maxn];

int main()
{
	cin >> n >> m;

	for(int i = 1 ; i <= n ; ++i) 
	{
		for(int j = 1 ; j <= m ; ++j)
		{
			cin >> mat[i][j];
		}
	}

	for(int i = 0 ; i < maxn ; ++i)
	{
		for(int j = 0 ; j < maxn ; ++j)
		{
			dp[i][j] = -inf;
		}

		pref[i] = suf[i] = -inf;
	}

	for(int i = 1 ; i <= m ; ++i) 
	{
		dp[1][i] = mat[1][i];
		if(i > 1) dp[1][i] += dp[1][i - 1];
	}

	for(int i = 2 ; i < n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
		{
			pref[j] = dp[i - 1][j];
			if(j > 1) pref[j] = max(pref[j], pref[j - 1]);

			pref[j] += mat[i][j];
		}

		for(int j = m ; j >= 1 ; --j)
		{
			suf[j] = dp[i - 1][j];

			if(j < m) suf[j] = max(suf[j + 1], suf[j]);

			suf[j] += mat[i][j];
		}
		
		for(int j = 1 ; j <= m ; ++j) dp[i][j] = max(pref[j], suf[j]);
	}

	for(int j = 1 ; j <= m && n > 1; ++j)
	{
		dp[n][j] = dp[n - 1][j];

		if(j > 1) dp[n][j] = max(dp[n][j], dp[n][j - 1]);

		dp[n][j] += mat[n][j];
	}

	cout << dp[n][m] << "\n";
}
