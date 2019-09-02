/*
  IOI 2004 - Task Farmer  
  Solution by Samyra Almeida
  
  Solution:
      This problems is very similar to knapsack problem. 
      Note that always is better to use the filds than to use the strips, with this the dp can have 3 values:
        - dp[i][j] = 1, if I can set the j value using of 1 to i and ,for all fields k that I use to sum, I use completely 
        the cypress trees of field k.
        - dp[i][j] = 0, if I can set the value of j using 1 to i and all the fields I used to compose the sum j, I used only 
        part of the cypress trees in a single field.
        - dp[i][j] = -1, if the state was not calculate.
      After I'll check if dp[i][Q] = 1, the answer is Q, if the dp[i][Q] = 0 else if the answer is Q-1 else I do a greedy 
      algotithm to completely the cypress trees with the strips.
      
      The only problme with the solution is the matrix dp, because the i <= 2000 and j <= 150000 and it's impossible crate a 
      matriz with the these dimentions, for solve this I use memory trick.
  
  Time Complexity: O(m*q)
*/

#include <bits/stdc++.h>

using namespace std;

const int maxq = 1.5e5+10, maxn = 2e3+10;

int q, m, k, c[maxn], l[maxn], dp[maxq][2];

int main()
{
	cin >> q >> m >> k;

	for(int i = 1 ; i <= m ; ++i) cin >> c[i];

	for(int i = 1 ; i <= k ; ++i) cin >> l[i];

	memset(dp, -1, sizeof dp);

	dp[0][0] = dp[0][1] = 1;

	for(int i = 1 ; i <= m ; ++i)
	{
		for(int j = 1 ; j <= q ; ++j)
		{
			if(j < c[i]) dp[j][1] = max(dp[j][0], 0);
			else if(j == c[i]) dp[j][1] = 1;
			else dp[j][1] = max(dp[j][0], dp[j - c[i]][0]);
		}

		for(int j = 0 ; j <= q ; ++j) dp[j][0] = dp[j][1];
	}
	
	if(dp[q][1] == 0) cout << q - 1 << "\n";

	else if(dp[q][1] == 1) cout << q << '\n';

	else
	{	
		int id = -1;

		for(int i = q - 1; i >= 0 ; --i) 
		{
			if(dp[i][1] > -1)
			{
				id = i;
				break;
			}
		}

		sort(l+1, l+k+1);

		int resp = id;

		if(dp[id][1] == 0) resp--;
		
		int rest = q - id;

		for(int i = k ; i >= 1 && rest; --i)
		{
			resp += min(rest, l[i]) - 1;
			rest -= min(rest, l[i]);
		}

		cout << resp << '\n';
	}
}
