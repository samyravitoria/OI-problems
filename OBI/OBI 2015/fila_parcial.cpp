/* 
	OBI 2015 - P2 - Fase 2 - Fila
	Solução para a parcial (40 pontos)

 	Primeiramente, montamos a seg com todos os participantes que ja estão na fila. Vale lembrar que nessa parcial NENHUM novo parcipante entrará 
 	na fila, logo podemo ignorar todas as operações do tipo 0.

 	E para as operações do tipo 1, realizaremos uma busca na seg, quando consultarmos um intervalo onde r > p (o final é maior que a posição do 
 	partipante) chamamos a busca para as duas metades da seg e retornamos o MAX entre elas ou seja o partipante mais a direita que satisfaz as 
 	condições da op.
 	Se não, checamos se a seg[dir] > val, se for chamamos a função para metade da direita, caso contrario chamamos para a metade da esquerda.

 	Assunto: Busca na Seg 
	Complexidade: O(n*log2(n))
 	
 	Solução by Samyra Almeida
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 6e5+10;

typedef long long ll;

int n, q;
ll v[maxn], seg[4*maxn];

void buildSeg(int u, int l, int r)
{
	if(l == r) 
	{
		seg[u] = v[l];
		return;
	}

	int mid = (l+r) >> 1, esq = u+u, dir = u+u + 1;

	buildSeg(esq, l, mid); buildSeg(dir, mid+1, r);

	seg[u] = max(seg[dir], seg[esq]);
}

int searchSeg(int u, int l, int r, int p, ll val)
{
	if(seg[u] <= val) return 0;

	if(l > p) return 0;

	if(l == r) return l;

	int mid = (l+r) >> 1, esq = u+u, dir = u+u + 1;

	if(r > p) return max(searchSeg(dir, mid+1, r, p, val), searchSeg(esq, l, mid, p, val));

	if(seg[dir] > val) return searchSeg(dir, mid+1, r, p, val);

	return searchSeg(esq, l, mid, p, val);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n;

	for(int i = 1 ; i <= n ; ++i) cin >> v[i];

	buildSeg(1, 1, n);

	cin >> q;

	for(int i = 0 ; i < q ; ++i)
	{
		int id, pos, x;
		cin >> id >> pos >> x;

		if(id == 0) continue;

		cout << searchSeg(1, 1, n, pos, x+v[pos]) << "\n";
	}
}
