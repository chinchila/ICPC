// Maximum cardinality (bipartite matching) O(n^3) worst case, if slow random_shuffle vertice orders.
// Apply it only on left set. indexed 1
vector<int> g[MAX_N];
int vis[MAX_N], b[MAX_N];
int n, x; // n is size of left set

bool dfs( int u )
{
	if( vis[u] == x ) return 0;
	vis[u] = x;
	for( int v : g[u] ) if( !b[v] || dfs( b[v] ) )
		return b[v] = u;
	return 0;
}
 
int kuhn()
{
	int ans = 0;
	for( int i = 1 ; i <= n ; ++i ) ++x, ans += dfs( i );
	return ans;
}

