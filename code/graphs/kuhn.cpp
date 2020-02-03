// Maximum cardinality (bipartite matching) O(n^3) worst case
// if slow random_shuffle vertice orders.
// Apply it only on left set. indexed 1
vector<int> g[MAXN];
int vis[MAXN], ma[MAXN], mb[MAXM];
int n, x; // n is size of left set

bool dfs( int u ) {
	for( int v : g[u] ) if(vis[v] != x) {
		vis[v] = x;
		if( mb[v] == -1 || dfs( mb[v] ) ) {
			mb[v] = u, ma[u] = v;
			return 1;
		}
	}
	return 0;
}

int kuhn() {
	memset(ma, -1, sizeof(ma));
	memset(mb, -1, sizeof(mb));
	bool aux = 1;
	int ans = 0;
	while( aux ) {
		++x, aux = 0;
		for( int i = 1 ; i <= n ; ++i )
			if( ma[i] == -1 && dfs(i) ) ++ans, aux = 1;
	}
	return ans;
}

