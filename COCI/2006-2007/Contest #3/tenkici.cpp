/*
  COCI 2006/2007 Contest #3 - Task Tenkici
  Solution by Samyra Almeida
  
  Note that each tank will move at most N² times (N movements in rows and N movements in columns).
  I divide the moviments in two tipes: in rows(X) and columns(Y). As we have N tanks, we'll have 
  at maximum N³ moviments.
  Some notes:
    - m[][] = battlefield (grade).
  In Rows:
    - I will move from line 1 to N-1 and at each grid position if there is a tank in position (i, j) and 
    position (i + 1, j) is empty and if there are more than i tanks in the first row i (to verify this, 
    we will use a BIT where the query (i) = sum of the number of tanks of the first lines i of the grid) 
    will move the tank to the position (i + 1, j) and I add movement to the resp vector and do movs++ 
    (total number of moves). Otherwise, we do nothing and continue the algorithm. Let's repeat this 
    algorithm N times as explained above.
    - Let's run the same algorithm above but now from line N to line 2 and if there is a tank at position 
    (i, j) and position (i-1, j) is empty and there is more than N - i + 1 tanks from line N to line i (to 
    check this, we will do: query (N) - query (i-1) = number of tanks from the N-th line to i-th line) move 
    tank to position (i-1, j) and I add movement to the resp vector and do movs++ (total number of moves). 
    Let's repeat this algorithm N times as explained above.
  In Colunms:
    - The algorithm is analogous for moving the tanks between the columns.
    
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
