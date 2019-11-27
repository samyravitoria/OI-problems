// Seletiva 2015 - Dia 2 - Amigo Secreto
// Solution by Samyra Almeida

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 3e5+10;
const ll inf = 1e15;

struct S
{
	ll sum, M, m, a;
	
	bool operator<(const S& o) const
	{
		if(sum != o.sum) return sum < o.sum;
		return a < o.a;
	}

};

int n, s, v[maxn];

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> s;

	for(int i = 1 ; i <= n ; ++i) cin >> v[i];

	sort(v+1, v+n+1);

	ll sum = s*1LL;

	int last = n, M = v[n], m = v[n];

	for(int i = n - 1; i >= 1 ; --i)
	{
		ll v1 = (M - m + s)*1LL, v2 = (M - v[i])*1LL;
		if(v1 < v2) // se vale a pena fazer um novo saquinho
		{
			sum += v1;
			M = m = v[i];
		}
		else m = v[i];
	}

	cout << sum + M - m << '\n';
}
