/*
  COCI 2006/2007 Contest #4 - Task Jogurt
  
  To extend a tree from n levels to a tree of n + 1 we will perform the following algorithm: 
  - At the beginning the root contains the number 1 and to form the subtrees multiply the tree by two and make two copies 
  of it, one for the subtree of the right and the other to the left. Thus, the property within the subtrees is maintained, 
  but now the subtrees just contain even numbers and the tree has two copies of the even numbers (one in each subtree). To 
  solve this, simply add 1 to all the leaves of the right subtree and 1 to all the non-leaves nodes of the left subtree. 
  This solves the problem because in the end the tree has 1 copy of each number. And the property is maintained for the root 
  because we add 2 ^ n in the right subtree and   (2 ^ 0 + 2 ^ 1 + ... + 2 ^ (n-1)) = 2 ^ n-1 in the left subtree. To make 
  the tree, simply run the following algorithm for each of the M levels.
  
  Link for Editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/COCI/official/2007/contest4_solutions
*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = (1<<15);

int n;
int tree[maxn], h[maxn], tot;

void solve(int x)
{
	for(int i = tot ; i > 0 ; --i)
	{
		tree[i] = tree[tot + i] = tree[i-1]*2;
		h[i] = h[tot + i] = h[i-1] + 1;
	}

	for(int i = 1 ; i <= tot+tot ; ++i)
	{
		if((x == h[i])^(i<=tot)) tree[i]++;
	}

	tot = tot+tot+1;
}

int main()
{
	cin >> n;

	tree[0] = 1;
	h[0] = 0;
	tot = 1;

	for(int i = 1 ; i < n ; ++i)
	{
		solve(i);
	}

	for(int i = 0 ; i < tot ; ++i)
	{
		cout << tree[i] << " \n"[i == tot-1];
	}

	return 0;
}
