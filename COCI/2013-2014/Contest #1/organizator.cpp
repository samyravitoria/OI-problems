/*
  COCI 2013/2014 Contest #1 - Task Organizator
  Solution by Samyra Almeida
  
  The array v[] contains the number of members in each club and and we will create the vector qtd[] in such a way that: 
  qtd[i] = number of clubs that have participants.
  
  First, sort the array v[] and do an funcion solve() that returns the maximum possible number of finalists. In solve 
  we'll do: for each x in range 1 ... 2e6  we'll go through all the multiples i of x between x and v[n-1] (club with 
  the largest number of participants), and if qtd [i]> 0, we add qtd [i] to tot (number of clubs that can participate 
  in the contest if the size of the team equals x) and x * qtd [i] to num (number of finalists if size of time equals 
  x). And at the end of this last loop (x ... v [n-1]) we check if tot> = 2, that is, if team size is valid, we do 
  r = max (r, num), that is, r receives the maximum number of finalists that have already been calculated and the number
  of finalists if the size of the team equals x. After going through all possible team sizes, we return the value of r. 
  Finally, we print the value that solve() returns.
  
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 2e6+10;

int n, v[maxn], qtd[maxn];

ll solve()
{
	ll r = 0LL;

	for(int u = 1 ; u < maxn ; ++u)
	{	
		ll num = 0LL;
		int tot = 0;
		for(int i = u ; i <= v[n-1] ; i += u)
		{
			if(qtd[i] > 0)
			{
				tot += qtd[i];
				num += (1LL)*u*qtd[i];
			}
		}

		if(tot > 1)
		{
			r = max(r, num);
		}
	}

	return r;
}

int main()
{
	cin >> n;

	for(int i = 0 ; i < n ; ++i)	
	{
		cin >> v[i];

		qtd[v[i]]++;
	}
	sort(v, v+n);
	
	cout << solve() << '\n';

}
