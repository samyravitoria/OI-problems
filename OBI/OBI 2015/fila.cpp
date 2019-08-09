/*
    OBI 2015 - P2 - Fase 2 - Fila
    
    Assunto: BIT, Segment Tree, busca na Segment Tree e busca na BIT em tempo logaritmo
    Complexidade: O((n+q)*log2(n+q))
    
    Solução por Samyra Almeida
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e7;

int n, q; 
int t[maxn], p[maxn], x[maxn], h[maxn], bit[maxn], seg[2*maxn];

int sum_bit(int idx)
{
	int sum = 0;

	for(int i = idx ; i > 0 ; i -= i&-i) sum += bit[i];

	return sum;
}

int upd_bit(int idx, int val)
{
	for(int i = idx ; i <= n+q ; i += i&-i) bit[i] += val;
}

int search_bit(int val)
{
	int resp = 0;

	for(int i = 30 ; i >= 0 ; --i)
	{
		int pot = (1<<i);

		if(resp + pot > n+q) continue;

		if(bit[resp + pot] <= val)
		{
			val -= bit[resp + pot];
			resp += pot;
		}
	}

	return (val == 0)? resp : -1;
}

void upd_seg(int idx, int val, int u = 1, int l = 1, int r = n+q)
{
	if(l == r) 
	{
		seg[u] = val;
		return;
	}

	int mid = (l+r)>>1;

	if(idx <= mid) upd_seg(idx, val, 2*u, l, mid);
	else upd_seg(idx, val, 2*u+1, mid+1, r);

	seg[u] = max(seg[2*u], seg[2*u+1]);
}

int search_seg(int idx, int val, int u = 1, int l = 1, int r = n+q)
{
	if(seg[u] <= val) return 0;
	
	if(l > idx) return 0;

	if(l == r) return l;

	int mid = (l+r)>>1;

	if(r > idx) return max(search_seg(idx, val, 2*u+1, mid+1, r), search_seg(idx, val, 2*u, l, mid));

	if(seg[2*u+1] > val) return search_seg(idx, val, 2*u+1, mid+1, r);

	return search_seg(idx, val, 2*u, l, mid);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n;

	for(int i = 0 ; i < n ; ++i)
	{
		cin >> x[i];
		p[i] = i;
	}

	cin >> q;

	for(int i = n ; i < n+q ; ++i) cin >> t[i] >> p[i] >> x[i];

	for(int i = 1 ; i <= n+q ; ++i) upd_bit(i, 1);

	for(int i = n+q-1 ; i >= 0 ; --i)
	{
		if(t[i] == 0)
		{
			p[i] = search_bit(p[i]) + 1;

			upd_bit(p[i], -1);
		}
		else p[i] = search_bit(p[i] - 1) + 1;
	}

	for(int i = 0 ; i < n+q ; ++i)
	{
		if(t[i] == 0)
		{
			h[p[i]] = x[i];

			upd_seg(p[i], x[i]);
			upd_bit(p[i], 1);
		}
		else cout << sum_bit(search_seg(p[i], h[p[i]] + x[i])) << '\n';
	}
}
