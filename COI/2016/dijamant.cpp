/*
  COI 2016 - Task Dijamant
  Solving by Samyra Almeida
  
  - For each new class K, use a map to check if class K is really a new class and the classes that class K inherits exists.
  - For check if the new class K form a diamond or not, I use a matrix mk[i][j] = 1 if i inherits j directly or indirectly. 
  So if two classes A and B, that K inherits directly, and A mk[A][B] = 0 and mk [B] [A] = 0, that is, A doesn't inherit B 
  and B doesn't inherit A and A and B inherit some class C, we have a diamond.
*/

#include <bits/stdc++.h>
 
using namespace std;
 
const int maxn = 1e3+10;
 
int n, N;
int nd, mk[maxn][maxn];
map<string, int> conv;
 
int main()
{
	cin >> n;
	N = n;
 
	while(N--)
	{
		string c, pt;
		cin >> c >> pt;
 
		set<string> II;
		vector<int> g;
 
		while(true)
		{
			string ss;
			cin >> ss;
 
			if(ss == ";") break;
 
			II.insert(ss);
		}
 
		if(conv.find(c) != conv.end())
		{
			cout << "greska\n";
			
			continue;
		}
		
		int ok = 0;
 
		conv[c] = ++nd;
 
		for(auto ii: II)
		{
			if(conv.find(ii) == conv.end())
			{
				ok = 1;
				break;
			}
 
			g.push_back(conv[ii]);
		}
 
		if(ok)
		{
			conv.erase(c);
			nd--;
			cout << "greska\n";
			
			continue;
		}
 
		for(int i = 0 ; i < g.size() ; ++i)
		{
			for(int j = i+1 ; j < g.size() ; ++j)
			{
				int a = g[i], b = g[j];
 
				if(mk[a][b] == 1 || mk[b][a] == 1) continue;
				
				for(int k = 1 ; k < nd ; ++k)
				{
					if(mk[a][k] == 1 && mk[b][k] == 1)
					{
						ok = 1;
						break;
					}
				}
			}
 
			if(ok) break;
		}
 
		if(ok)
		{
			nd--;
			conv.erase(c);
 
			cout << "greska\n";
			
			continue;
		}
 
		for(int u: g)
		{
			mk[nd][u] = 1;
 
			for(int i = 1 ; i < nd ; ++i)
				if(mk[u][i]) mk[nd][i] = 1;
		}
 
		cout << "ok\n";
	}
}
