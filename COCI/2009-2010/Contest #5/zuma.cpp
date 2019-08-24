/*
  COCI 2009/2010 Contest #5 - Task Zuma
  
  For solving this problem, we'll use Dynamic Programming.
  The dp has three states (l, r, c), where dp [l] [r] [c] = minimum quantity of marbles that we need to 
  add to exclude the marbles of l, l + 1, ..., r- 1, r, having already added C copies of v[l] added at 
  the beginning of the sequence.
  
  We will have three cases for each state:
    - Add one element of the first marble in the begin of senquence: dp[l][r][c] = dp[l][r][c+1] + 1.
    - If c = k-1, we can delete all the marbles on the beginning of sequence including the first marble of 
    subsequence: dp[l][r][c] = dp[l+1][r][0].
    - In this case we try merging the v[l] to another marble v[j], if v[l] = v[j], and in this case we 
    do dp[l][r][c] = dp[l+1][j-1][0] + dp[j][r][min(k-1, c+1)].
  And the base cases of dp:
    - if l > r:  this is impossible and we return 0;
    - if l == r, for any c: we need k-c-1 marbles to delete this subsequence.
  
  Time Complexity: O(n*n*n*k)
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 110, inf = 0x3f3f3f3f;

int n, k, v[maxn], dp[maxn][maxn][10];

int solve(int l, int r, int c)
{
	if(l > r) return dp[l][r][c] = 0;
	if(l == r) return dp[l][r][c] = k - c - 1;
	if(dp[l][r][c] != -1) return dp[l][r][c];
	
	int resp = inf;

	if(c < k -1) resp = solve(l, r, c+1) + 1;
	if(c == k-1) resp = solve(l+1, r, 0);

	for(int i = l+1; i <= r ; ++i)
	{
		if(v[i] != v[l]) continue;
		resp = min(resp, solve(l+1, i-1, 0) + solve(i, r, min(k-1,c+1)));
	}

	return dp[l][r][c] = resp;
}

int main()
{
	cin >> n >> k;

	for(int i = 0 ; i < n ; ++i) cin >> v[i];
	memset(dp, -1, sizeof dp);
	cout << solve(0, n-1, 0) << '\n';

	return 0; 
}
