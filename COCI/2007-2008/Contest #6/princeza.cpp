/*
  COCI 2007/2008 Contest #6 - Task Princeza
  Solution by Samyra Almeida
  
  Solution
    - For each plant, I discover the two diagonals that pass through it d1 = x - y && d2 = x + y.
    - On maps s added all diagonals of type: x - y, and on map d added all diagonals of type x + y
    - For a plant in the coordinates (x, y): d1 = x - y, d2 = x + y. And I do : 
      - s[d1].insert({x,y}), d[d2].insert({x,y}), for all plants.
    - And for each movement I check the respective map and position
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5+10, inf = 2e9+10;

typedef pair<int, int> ii;

struct point
{
	int x, y, d1, d2;
} plants[maxn];

int n, k;
string jumps;

map<int, set<ii> > s, d;
map<ii, int> rec;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> k >> jumps;

	for(int i = 0 ; i < n ; ++i)
	{
		int x, y, d1, d2;
		cin >> x >> y;
		
		rec[{x, y}] = i;

		d1 = y - x;
		d2 = y + x;

		plants[i] = {x, y, d1, d2};
	}

	for(int i = 0 ; i < n ; ++i)
	{
		int d1 = plants[i].d1;
		int d2 = plants[i].d2;

		s[d1].insert({plants[i].x, plants[i].y});
		d[d2].insert({plants[i].x, plants[i].y});
	}

	int id = 0;

	for(char c: jumps)
	{
		int x = plants[id].x;
		int y = plants[id].y;
		int d1 = plants[id].d1;
		int d2 = plants[id].d2;

		if(c == 'A')
		{
			auto it = s[d1].find({x, y});
			
			it++;
			
			if(it != s[d1].end())
			{
				d[d2].erase({x, y});
				s[d1].erase({x, y});
				id = rec[{it->first, it->second}];
			}
		}
		else if(c == 'B')
		{
			auto it = d[d2].find({x, y});
			
			it++;
			
			if(it != d[d2].end())
			{
				s[d1].erase({x, y});
				d[d2].erase({x, y});
				id = rec[{it->first, it->second}];
			}
		}
		else if(c == 'C')
		{
			auto it = d[d2].find({x, y});
						
			if(it != d[d2].begin())
			{
				it--;
				d[d2].erase({x, y});
				s[d1].erase({x, y});

				id = rec[{it->first, it->second}];
			}
		}
		else
		{
			auto it = s[d1].find({x, y});
			
			if(it != s[d1].begin())
			{
				it--;
				s[d1].erase({x, y});
				d[d2].erase({x, y});
				id = rec[{it->first, it->second}];
			}
		}
	}

	cout << plants[id].x << ' ' << plants[id].y << '\n';
}
