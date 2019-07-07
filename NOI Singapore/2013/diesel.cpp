/*
  NOI Singapore 2013 - Task Diesel
  Solution by Samyra Almeida
  .
  Note: dist[i][j] = the max weight of the truck with fuel of the begin to edge (i, j).
  
  I do a algorithm, very similar to dijkstra, but of maximum way. To go from the cell (x, y) to the neighboring cell (xx, yy):
    - Check that the weight of the truck to the cell (x, y) minus the amount of diesel to go to the cell (xx, yy) is greater 
    than the value of dist [xx] [yy], if so, update the value of dist [xx] [yy] and add in the priority queue.
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3+10;

struct pos
{
	int x, y, v;

	bool operator<(const pos& o) const
	{
		return v < o.v;
	}
};

int dx[] = {0, 0,  1};
int dy[] = {-1, 1, 0};

int n, m;
int mat[maxn][maxn], dist[maxn][maxn], vis[maxn][maxn];

void solve()
{
	memset(dist, -1, sizeof dist);
	priority_queue<pos> row;

	dist[1][1] = 33000;
	row.push({1, 1, 33000});

	while(!row.empty())
	{
		int x = row.top().x;
		int y = row.top().y;
		int v = row.top().v;
		row.pop();

		if(v < dist[x][y] || vis[x][y]) continue;

		vis[x][y] = 1;

		for(int i = 0 ; i < 3 ; ++i)
		{
			int xx = dx[i] + x;
			int yy = dy[i] + y;

			if(xx > 0 && xx <= n && yy > 0 && yy <= m)
			{	
				int k = 0;

				if(mat[x][y] < mat[xx][yy])
				{
					k = (mat[xx][yy] - mat[x][y])/100;
					k *= 4*(v/1000);
				}

				k += 10;

				if(v - k > dist[xx][yy] && v - k > 8000)
				{
					dist[xx][yy] = v - k;
					row.push({xx, yy, v - k});
				}
			}
		}
	}
}

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

	solve();

	int resp = dist[n][m] - 8000;

	if(resp < 0) cout << "-1\n";
	
	else if(resp == 0) cout << "0\n";

	else cout << resp << "\n";
}
