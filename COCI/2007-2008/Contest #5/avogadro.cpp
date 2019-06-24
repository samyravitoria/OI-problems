/*
  COCI 2007/2008 Contest #5 - Task Avogadro
  Solution by Samyra Almeida
   
  During the reading, we will define the value of the matrix num[][], where num[i][j] = quantity of times j has appeared on 
  the i-th line of the table and vector qtd[], where qtd[x] = quantity of times the x value appeared in the table. Then, we 
  will assemble the vector col [], where col [j] contains all the columns as the number j appears.
  
  After that, we go through table num, and if num[i][j] = 0 means that the value j does not appear in row i of the Luka table 
  then we add the value j to the queue row.
  
  In the queue, we have all the values that should be erased from the table and, as we know in which columns each value appears, 
  just delete them from the table. In order not to delete the same column more than once, we check if it has already been deleted, 
  otherwise we make del++ (number of columns deleted) and we go through its lines excluding the values that are there, if in any 
  moment a value is totally excluded of a line, we add it to the queue.
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn =1e5+10;

int n, m[5][maxn], num[5][maxn], qtd[maxn], in[maxn], er[maxn];

vector<int> col[maxn];

int main()
{
	cin >> n;
	
	for(int i = 1 ; i < 4 ; ++i)
	{
		for(int j = 1 ; j <= n ; ++j)
		{
			cin >> m[i][j];
			num[i][m[i][j]]++;
			qtd[m[i][j]]++;
		}
	}

	for(int j = 1 ; j <= n ; ++j)
	{
		vector<int> vs;

		for(int i = 1 ; i < 4 ; ++i) vs.push_back(m[i][j]);

		sort(vs.begin(), vs.end());

		int last = -1;

		for(auto x: vs)
		{
			if(x != last)
			{
				col[x].push_back(j);
				last = x;
			}
		}
	}
	
	queue<int> row;

	for(int i = 1 ; i < 4 ; ++i)
	{
		for(int j = 1 ; j <= n ; ++j)
		{
			if(num[i][j] == 0 && in[j] == 0)
			{
				row.push(j);
        			in[j] = 1;
 			}
		}
	}

	int del = 0;

	while(!row.empty())
	{
		int val = row.front();
		row.pop();

		if(qtd[val] == 0) continue;

		for(auto u: col[val])
		{
			if(er[u] == 1) continue;
			er[u] = 1;
			del++;

			for(int i = 1 ; i < 4 ; ++i)
			{
				num[i][m[i][u]]--;
				qtd[m[i][u]]--;

				if(num[i][m[i][u]] == 0 && qtd[m[i][u]] > 0 && in[m[i][u]] == 0)
				{
					row.push(m[i][u]);
					in[m[i][u]] = 1;
				}
			}
		}
	}

	cout << del << "\n";
	
	return 0;
}
