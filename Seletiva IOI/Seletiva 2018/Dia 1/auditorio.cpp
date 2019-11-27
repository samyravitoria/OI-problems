// Seletiva 2018 - Dia 1 - Programa de Auditório
// Solution by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

const int maxn = 300, maxx = 62551;

int n, x, v[maxn], dp[maxn][maxx];

int main()
{
	cin >> n >> x;

	for(int i = 0 ; i < n ; ++i) cin >> v[i];

	dp[n - 1][x] = dp[n - 1][x - v[n - 1]] = 1;

	for(int i = n - 2 ; i >= 0 ; --i)
	{
		dp[i][x] = 1;

		for(int w = x ; w >= 0 ; --w)
		{
			dp[i][w] = dp[i + 1][w];

			if(w + v[i] <= x) dp[i][w] = max(dp[i][w], dp[i + 1][w + v[i]]);
		}
	}

	if(dp[0][0])
	{
		cout << "S\n";

		vector<int> ids;

		for(int w = 0, i = 0 ; w < x && i < n;)
		{
			while(i + 1 < n && dp[i + 1][w]) i++;
            
            w += v[i];
            
            ids.push_back(i);
		}

		for(int a: ids) cout << a << " ";
		cout << "\n";
	}
	else cout << "N\n";
}
