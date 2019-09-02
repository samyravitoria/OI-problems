/*
  IOI 2004 - Task Phidias
  
  Solution by IOI 2004
  
  Use Dynamic Programming:
  
  Let a(x, y) be the wasted area for a rectangle (x, y), 1 ≤ x ≤ W , 1 ≤ y ≤ H.
  Initially, put a(x, y) = xy, for all (x, y) except for the ones corresponding to needed plates, e.g. 
  x = wi and y = hi , 1 ≤ i ≤ N , for which we put a(x, y) = 0. For a plate (x, y) consider all vertical 
  cuts c = 1, 2, . . . , x − 1 and all horizontal cuts c = 1, 2, . . . , y − 1 and chose the cut producing 
  the minimum wasted area a(x, y) = a(c, y) + (x − c, y) or a(x, c) + a(x, y − c) for some c.
  
  Time Complexity: O(w*h*max(w, h))
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 610, inf = 0x3f3f3f3f;

int h, w, n, dp[maxn][maxn];

int main()
{
	cin >> w >> h >> n;

	memset(dp, inf, sizeof dp);

	for(int i = 0 ; i < n ; ++i)
	{
		int x, y;
		cin >> x >> y;

		dp[x][y] = 0;
	}

	for(int i = 1 ; i <= w ; ++i)
	{
		dp[i][0] = 0;
	}

	for(int j = 1 ; j <= h ; ++j)
	{
		dp[0][j] = 0;	
	}

	for(int i = 1 ; i <= w ; ++i)
	{
		for(int j = 1 ; j <= h ; ++j)
		{
			if(dp[i][j] != inf) continue;

			dp[i][j] = i*j;
		
			for(int c = 1 ; c <= i ; ++c)
			{
				dp[i][j] = min(dp[i][j], dp[c][j] + dp[i - c][j]);
			}

			for(int c = 1 ; c <= j ; ++c)
			{
				dp[i][j] = min(dp[i][j], dp[i][c] + dp[i][j - c]);
			}
		}
	}

	cout << dp[w][h] << '\n';
}
