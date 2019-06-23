/*
  COCI 2009/2010 Contest #2 - Task Vuk
  Solution by Samyra Almeida
  
  First, we will assemble the vector distp [], where distp [u] = the shortest distance from u to a tree. To calculate 
  the minimum distance of a tree on the ideal route, we run a algorithm similar to a BFS. To calculate the minimum 
  distance of a tree on the ideal route, we run a algorithm similar to a BFS.
  
  Knowing this, we will use a priority_queue that will hold position (i, j) and the shortest distance to a tree in the 
  path from Vjekoslav's position to position (i, j).
  
  Because priority_queue stores the values in descending order, we can guarantee that when we process a given position 
  (x, y) for the first time, this is the shortest distance of a tree in the ideal route for (x, y), so we will store 
  this distance in dist[x][y].
  
  Then we will add a neighbor (xx, yy) from (x, y) to priority_queue to dist[xx][yy] < min(dist[x][y], distp[xx][yy]), 
  that is, the minimum distance of a tree in the path to the position (xx, yy) is less than the minimum distance between 
  a tree in the path to (x, y) and distp[xx][yy]. Finally, if the position of Vjekoslav's hut is (a, b) simply print the 
  value of dist [a] [b].
*/

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int maxn = 510, inf = 999999999;

typedef pair<int, int>  pii;
typedef pair<int, pii>  piii;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int n, m, distp[maxn][maxn], vis[maxn][maxn], dist[maxn][maxn];
char mat[maxn][maxn];
pii V, J;

void build()
{
  memset(vis, 0, sizeof vis);

  queue<piii> row;

  for(int i = 1 ; i <= n ; ++i)
  {
    for(int j = 1 ; j <= m ; ++j)
    {
      if(mat[i][j] == '+')
      {
        distp[i][j] = 0;
        row.push(piii(0, pii(i, j)));
      }
      else distp[i][j] = inf;
    }
  }

  while(!row.empty())
  {
    int d = row.front().F;
    int x = row.front().S.F;
    int y = row.front().S.S;
    row.pop();

    if(d > distp[x][y] || vis[x][y] == 1) continue;
   
    vis[x][y] = 1;

    for(int i = 0 ; i < 4 ; ++i)
    {
      int xx = x + dx[i];
      int yy = y + dy[i];

      if(xx > 0 && xx <= n && yy > 0  && yy <= m && d + 1 < distp[xx][yy])
      {
        distp[xx][yy] = (d + 1);

        row.push(piii(d+1, pii(xx, yy)));
      }
    }
  }
}

int solve(pii V)
{
  memset(vis, 0, sizeof vis);

  for(int i = 1 ; i <= n ; ++i)
  {
    for(int j = 1 ; j <= m ; ++j)
    {
      dist[i][j] = -inf;
    }
  }

  dist[V.F][V.S] = distp[V.F][V.S];

  priority_queue<piii> row;

  row.push(piii(distp[V.F][V.S], pii(V.F, V.S)));

  while(!row.empty())
  {
    int d = row.top().F;
    int x = row.top().S.F;
    int y = row.top().S.S;
    row.pop();

    if(d < dist[x][y] || vis[x][y]) continue;

    for(int i = 0 ; i < 4 ; ++i)
    {
      int xx = x + dx[i];
      int yy = y + dy[i];

      if(xx > 0 && xx <= n && yy > 0 && yy <= m && dist[xx][yy] < min(dist[x][y], distp[xx][yy]))
      {
        dist[xx][yy] = max(min(dist[x][y], distp[xx][yy]), dist[xx][yy]);
        row.push(piii(dist[xx][yy], pii(xx, yy)));
      }
    }
  }

  return dist[J.F][J.S];
}

void debug()
{
  for(int i = 1 ; i <= n ; ++i)
  {
    for(int j = 1 ; j <= m ; ++j)
    {
      cout << distp[i][j] << " \n" [j == m];
    }
  }

  cout << "\n";

  for(int i = 1 ; i <= n ; ++i)
  {
    for(int j = 1 ; j <= m ; ++j)
    {
      cout << dist[i][j] << " \n" [j == m];
    }
  }
}

int main()
{
	cin >> n >> m;
	
	memset(mat, '#', sizeof mat);

	for(int i = 1 ; i <= n ; ++i)
	{
		for(int j = 1 ; j <= m ; ++j)
		{
			cin >> mat[i][j];

			if(mat[i][j] == 'V') V = {i, j};
			if(mat[i][j] == 'J') J = {i, j};
		}
	}

	build();

	cout << solve(V) << '\n';
}
