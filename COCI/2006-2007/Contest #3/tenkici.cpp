/*
  Solution by Samyra Almeida
  
  Note that each tank will move at most N² times (N movements in rows and N movements in columns).
  
  Time Complexity: O(n³*log2(n))
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 510;

struct R
{
	int id;
	char type;
};

int n, bit[maxn];
int m[maxn][maxn];
int qc[maxn], qr[maxn];

long long movs;

vector<R> resp;

int query(int p)
{
	int sum = 0;

	while(p > 0)
	{
		sum += bit[p];
		p -= (p & -p);
	}

	return sum;
}

void upd(int p, int val)
{
	while(p <= n)
	{
		bit[p] += val;
		p += (p & -p);
	}
}

void solveX()
{
	for(int k = 1 ; k <= n ; ++k)
	{
		for(int i = 1 ; i < n ; ++i)
		{	
			if(qr[i] == 0) continue;

			for(int j = 1 ; j <= n ; ++j)
			{
				if(m[i][j] != 0 && m[i+1][j] == 0 && query(i) > i)
				{
					resp.push_back({m[i][j], 'D'});
					m[i+1][j] = m[i][j];
					m[i][j] = 0;					
					upd(i, -1);
					upd(i+1, 1);
					
					qr[i]--;
					qr[i+1]++;
					movs++;
				}
			}
		}
	}

	for(int k = 1 ; k <= n ; ++k)
	{
		for(int i = n ; i > 1 ; --i)
		{	
			if(qr[i] == 0) continue;

			for(int j = 1 ; j <= n ; ++j)
			{
				if(m[i][j] != 0 && m[i-1][j] == 0 && query(n) - query(i-1) > n - i + 1)
				{
					resp.push_back({m[i][j], 'U'});
					m[i-1][j] = m[i][j];
					m[i][j] = 0;
					upd(i, -1);
					upd(i-1, 1);
					
					qr[i]--;
					qr[i-1]++;
					movs++;
				}
			}
		}
	}	
}

void solveY()
{
	for(int k = 1 ; k <= n ; ++k)
	{
		for(int j = 1 ; j < n ; ++j)
		{
			if(qc[j] == 0) continue;

			for(int i = 1 ; i <= n ; ++i)
			{
				if(m[i][j+1] == 0 && m[i][j] != 0 && query(j) > j)
				{
					resp.push_back({m[i][j], 'R'});

					m[i][j+1] = m[i][j];
					m[i][j] = 0;

					upd(j, -1);
					upd(j+1, 1);

					qc[j]--;
					qc[j+1]++;
					movs++;
				}
			}
		}
	}

	for(int k = 1 ; k <= n ; ++k)
	{
		for(int j = n ; j > 1 ; --j)
		{
			if(qc[j] == 0) continue;
			for(int i = 1 ; i <= n ; ++i)
			{
				if(m[i][j-1] == 0 && m[i][j] != 0 && query(n) - query(j-1) > n - j + 1)
				{
					resp.push_back({m[i][j], 'L'});

					m[i][j-1] = m[i][j];
					m[i][j] = 0;

					upd(j, -1);
					upd(j-1, 1);

					qc[j]--;
					qc[j-1]++;
					movs++;
				}
			}
		}
	}
}

bool check()
{
	for(int i = 1 ; i <= n ; ++i) 
		if(qr[i] != 1 || qc[i] != 1)
			return false;

	return true;
}

int main()
{
	cin >> n;

	for(int i = 1 ; i <= n ; ++i)
	{
		int r, c;
		cin >> r >> c;

		m[r][c] = i;

		qr[r]++;
		qc[c]++;
	}

	memset(bit, 0, sizeof bit);

	for(int i = 1 ; i <= n ; ++i)
	{
		if(qr[i] > 0 ) upd(i, qr[i]);
	}

	solveX();
	
	
	memset(bit, 0, sizeof bit);

	for(int i = 1 ; i <= n ; ++i)
	{
		if(qc[i] > 0 ) upd(i, qc[i]);
	}

	solveY();

	cout << movs << '\n';

	for(auto u: resp)
	{
		int id = u.id;
		char type = u.type;

		cout << id << ' ' << type << '\n';
	}
}
