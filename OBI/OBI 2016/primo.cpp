/*
    OBI 2016 - P2 - Fase 2 - Quase Primo
    
    Assunto: Princípio da Inclusão-Exclusão
    Complexidade: Não sei, sei que passa
    
    Solução por Samyra Almeida
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, k, vet[45], resp;

void solve(int p, int qtd, ll val)
{
	if(val > n) return;

	if(p == k+1)
	{
		if(qtd%2) resp += n/val;
		else resp -= n/val;
		return;
	}

	solve(p+1, qtd+1, val*vet[p]);
	solve(p+1, qtd, val);
}

int32_t main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> k;
	
	for(ll i = 1 ; i <= k ; ++i) cin >> vet[i];
	
	solve(1LL, 1LL, 1LL);

	cout << resp << "\n";
}
