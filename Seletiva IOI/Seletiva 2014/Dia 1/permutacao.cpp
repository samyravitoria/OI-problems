// Seletiva 2014 - Dia 1 - Permutação
// Solution by Samyra Almeida

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6+10, inf = 0x3f3f3f3f;

int n;
int v1[maxn], v2[maxn], pfmin[maxn], pfmax[maxn], sfmin[maxn], sfmax[maxn];

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	memset(pfmin, 0, sizeof pfmin);
	memset(sfmin, 0, sizeof sfmin);
	memset(pfmax, inf, sizeof pfmax);
	memset(sfmax, inf, sizeof sfmax);

	cin >> n;

	for(int i = 1 ; i <= n ; ++i) cin >> v1[i];

	for(int i = 1 ; i < n ; ++i) cin >> v2[i];

	for(int i = 1 ; i <= n ; ++i)
	{
		pfmin[i + 1] = pfmin[i], pfmax[i + 1] = pfmax[i];

		if(v1[i] == v2[i]) pfmin[i + 1] = max(pfmin[i], v1[i]);
		else if(v1[i] - 1 == v2[i]) pfmax[i + 1] = min(pfmax[i], v1[i]);
		else pfmin[i + 1] = inf, pfmax[i + 1] = 0;
	}

	for(int i = n ; i >= 1 ; --i)
	{
		sfmin[i - 1] = sfmin[i], sfmax[i - 1] = sfmax[i];

		if(v1[i] == v2[i - 1]) sfmin[i - 1] = max(sfmin[i], v1[i]);
		else if(v1[i] - 1 == v2[i - 1]) sfmax[i - 1] = min(sfmax[i], v1[i]);
		else sfmin[i - 1] = inf, sfmax[i - 1] = 0;
	}

	vector<int> v;

	for(int i = 1 ; i <= n ; ++i)
	{
		if(pfmax[i] > v1[i] && v1[i] > pfmin[i] && sfmax[i] > v1[i] && v1[i] > sfmin[i]) v.push_back(v1[i]);
	}

	sort(v.begin(), v.end());

	for(int x: v) cout << x << " ";

	cout <<"\n";
}
