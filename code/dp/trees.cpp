// Count sub tree
// dp[u][j] = # of different sub trees of size less than or equal to K.
// g[i] is childrens of i
vector<int> g[MAXN];
int dp[MAXN][MAXK], sub[MAXN], tmp[MAXK];
int k;
void dfs( int u ) {
	sub[u] = 1;
	dp[u][0] = dp[u][1] = 1;
	for( int v : g[u] ) {
		dfs( v );
		fill( tmp , tmp + k + 1 , 0 );
		for( int i = 1 ; i <= min( sub[u] , k ) ; ++i )
			for( int j = 0 ; j <= sub[v] && i + j <= k ; ++j )
				tmp[i + j] += dp[u][i] * dp[v][j];
		sub[u] += sub[v];
		for( int i = 0 ; i <= min( k , sub[u] ) ; ++i )
			dp[u][i] = tmp[i];
	}
}

//Longest path on DAG O(n+m), index 1

int dp[MAXN];

void dfs( int u ) {
	vis[u] = true;
	for( int v : g[u] ) {
		if( !vis[v] ) dfs( v );
		dp[u] = max( dp[u], 1+ dp[v] );
	}
}

int lp() {
	for( int i = 1 ; i <= n ; ++i ) if( !vis[i] ) dfs( i );
	int r = 0;
	for( int i = 1 ; i <= n ; ++i ) r = max( r, dp[i] );
	return r;
}

