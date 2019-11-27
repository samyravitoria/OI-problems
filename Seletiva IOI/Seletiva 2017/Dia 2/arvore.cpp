// Seletiva 2017 - Dia 2 - Árvore
// Solution by Samyra Almeida

#include <bits/stdc++.h>
     
using namespace std;
     
const int maxn=5e5+10, maxl=20;
     
struct Node{
   	
   	int v;
   	Node *l, *r;
    
   	Node(){
   		l = r = NULL;
   		v=0;
   	}
};
Node *version[maxn];
     
int t, n, m, num[maxn];
int anc[maxn][maxl];
int s[maxn], lv[maxn];
     
vector<int> graph[maxn];
map<int, int> back;

void compress(){

	map<int, int> M;
	vector<int> V;

	for(int i=1;i<=n;++i){
		V.push_back(num[i]);
	}

	sort(V.begin(), V.end());
	int aux=0;
	for(int i=0;i<V.size();++i){
		if(M.find(V[i])==M.end()){
			M[V[i]]=++aux;
			back[aux]=V[i];
		}
	}
	for(int i=1;i<=n;++i){
		num[i]=M[num[i]];
	}
}

void build(Node *node, int l, int r){
   	if( l == r ) return;
    
   	int mid=(l+r)>>1;
    
   	node->l = new Node(); node->r = new Node();
    
   	build(node->l, l, mid);
   	build(node->r, mid+1, r);
}
    
void upd(Node *prev, Node *node, int l, int r, int pos){
   	if( l == r ){
   		node->v = prev->v+1;
   		return;
   	}
   	int mid = (l+r)>>1;
	     
   	if(pos<=mid){
     
   		node->r = prev->r;
   		if( node->l == NULL ) node->l = new Node();
    
   		upd(prev->l, node->l, l, mid, pos);
   	}else{
   		node->l = prev->l;
    
   		if( node->r == NULL ) node->r = new Node();
    
   		upd(prev->r, node->r, mid+1, r, pos);
   	}
    
   	node->v = node->l->v + node->r->v;
}


int kth(Node *prev, Node *node1, Node *node2, Node *node3, int l, int r, int k){
   	if( l == r ) return l;
    
   	int mid=(l+r)>>1;
    
   	int x=(node1->l->v + node2->l->v - prev->l->v - node3->l->v);
    
   	if(x>=k) return kth(prev->l, node1->l, node2->l, node3->l, l, mid, k);
   	else return kth(prev->r, node1->r, node2->r, node3->r, mid+1, r, k-x);
}
     
void dfs(int u, int f){
   	s[u]=++t;   	
   	
    version[t] = new Node();
   	upd(version[s[f]], version[s[u]], 1, n, num[u]);

   	for(int v: graph[u]){
    	if(v==f) continue;

   		anc[v][0]=u;
   		
   		lv[v]=lv[u]+1;
   		
   		dfs(v, u);
   	}
}

void build_lca(){
	
	for(int j=1;j<maxl;++j){
   		for(int i=1;i<=n;++i){
   			if(anc[i][j-1]!=-1){
   				anc[i][j]=anc[anc[i][j-1]][j-1];
   			}
   		}
   	}
}

int LCA(int u, int v){
   	if(lv[u]<lv[v]) swap(u, v);
    
   	for(int i=maxl-1;i>=0;--i){
   		if(lv[u]-(1<<i)>=lv[v]){
   			u=anc[u][i];
   		}
   	}
    
   	if(u==v) return u;
    
  	for(int i=maxl-1;i>=0;--i){
   		if(anc[v][i]!=-1 && anc[v][i]!=anc[u][i] && anc[u][i]!=-1){
   			u=anc[u][i];
   			v=anc[v][i];
   		}
   	}
    
   	return anc[u][0];
}
    
int main(){
   	
	ios::sync_with_stdio(false); cin.tie(0);

   	scanf("%d%d", &n, &m);
   	version[0] = new Node();
   	build(version[0], 1, n);
    
   	for(int i=1;i<=n;++i){
   		scanf("%d", &num[i]);
   	}
    
   	for(int i=1;i<n;++i){
   		int u, v;
   		scanf("%d%d", &u, &v);
    
   		graph[u].push_back(v);
   		graph[v].push_back(u);
   	}
    
    compress();

    memset(anc, -1, sizeof anc);

	anc[1][0]=0;

	dfs(1, 0);
    build_lca();
    
   	for(int i=1;i<=m;++i){
    
   		int x, y, k;
   		scanf("%d%d%d", &k, &x, &y);
    
   		int kra=LCA(x, y);
   		printf("%d\n" , back[kth(version[s[kra]], version[s[x]], version[s[y]], version[s[anc[kra][0]]], 1, n, k)]);
   	}

  	return 0;
}
