// cpar[i] stores parent of i | O(n) | index 0
int N;
vector<int> adj[MAXN];
int sz[MAXN];
int cpar[MAXN];
bool vis[MAXN];

void dfs( int n, int p = -1 ) {
	sz[n] = 1;
	for( int v : adj[n] ) if( v != p && !vis[v] ) dfs( v, n ), sz[n] += sz[v];
}

int centroid( int n ) {
	dfs( n );
	int num = sz[n];
	int p = -1;
	do {
		int nxt = -1;
		for( int v : adj[n] ) if( v != p && !vis[v] )
			if( 2 * sz[v] > num ) nxt = v;
		p = n, n = nxt;
	} while( ~n );
	return p;
}

void decomp( int n = 0, int p = -1 ) {
	int c = centroid( n );
	vis[c] = true;
	cpar[c] = p;
	for( int v : adj[c] ) if ( !vis[v] ) decomp( v, c );
}
