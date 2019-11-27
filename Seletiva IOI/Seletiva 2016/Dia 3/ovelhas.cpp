// Seletiva 2016 - Dia 3 - Ovelhas
// Solution by Samyra Almeida

#include <bits/stdc++.h>
#define F first
#define S second

using namespace std;

const int maxn = 1e5+10, inf = 1e9+10;

typedef long long ll;
typedef pair<int, int> ii;

int n, q;
ii qr[maxn], p[maxn];
ll A;
vector<ii> ch;

bool col(ii &a, ii &b, ii &c)
{
	return (1LL*(b.S - a.S)*(c.F - b.F) == 1LL*(c.S - b.S)*(b.F - a.F));
}

ll cross(ii o, ii a, ii b)
{
	return 1LL*(a.F - o.F)*(b.S - o.S) - 1LL*(a.S - o.S)*(b.F - o.F);
}

void convexhull()
{
	if(n == 1) 
	{
		ch.push_back(p[1]);

		return;
	}

	int k = 0;

	vector<ii> h(2*n);

	sort(p + 1, p + n + 1);

	for(int i = 1 ; i <= n ; ++i)
	{
		while(k >= 2 && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
		
		h[k++] = p[i];
	}

	for(int i = n - 1, t = k ; i >= 1 ; --i)
	{
		while(k >= t + 1 && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--;
		
		h[k++] = p[i];
	}

	h.resize(k - 1);

	reverse(h.begin(), h.end());

	ch = h;
}

/*
void area() // msm ideia para poligonos concavos tuntis
{
	for(int i = 2 ; i < ch.size() ; ++i) A += abs(cross(ch[0], ch[i - 1], ch[i]));

	A >>= 1;
}
*/

int check(ii x)
{
	int ans = 1, ini = 1, fim = ch.size() - 2, mid;

	while(ini <= fim)
	{
		mid = (ini + fim) >> 1;

		if(cross(ch[0], x, ch[mid]) > 0) 
		{
			ans = mid;
			ini = mid + 1;
		}
		else fim = mid - 1;
	}

	ll a = abs(cross(ch[0], ch[ans], ch[ans + 1]));
	ll a1 = abs(cross(ch[0], x, ch[ans]));
	ll a2 = abs(cross(ch[0], x, ch[ans + 1]));
	ll a3 = abs(cross(x, ch[ans + 1], ch[ans]));

	return (a == (a1 + a2 + a3));
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> q;

	bool ok = true;

	for(int i = 1 ; i <= n ; ++i)
	{
		int x, y;
		cin >> x >> y;

		p[i] = {x, y};

		if(i >= 3 && ok) ok = col(p[1], p[2], p[i]);
	}

	sort(p+1, p+n+1);

	for(int i = 0 ; i < q ; ++i) cin >> qr[i].F >> qr[i].S;

	int qtd = 0;

	if(ok)
	{
		for(int i = 0 ; i < q ; ++i)
			if(p[1] < qr[i] && qr[i] < p[n] && col(p[1], qr[i], p[n])) qtd++;
	}
	else
	{
		convexhull();
		
		//for(ii x: ch) cout << x.F << " " << x.S << "\n";

		//area();

		for(int i = 0 ; i < q ; ++i)
		{
			qtd += check(qr[i]);
		}

		//cout << A << '\n';
	}

	cout << qtd << '\n';
}
