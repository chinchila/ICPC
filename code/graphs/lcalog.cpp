// To compute minimum just use the commented code | index 0
// O(log n) query | O(n log n) build
typedef pair<int,int> pii;
int parent[MAXN], level[MAXN], dist[MAXN];
int anc[MAXN][MAXLG];//, mnn[MAXM][30];
vector<pii> g[MAXN];

void dfs( int u ) {
	for( pii pv : g[u] ) {
		int v = pv.first, w = pv.second;
		if( v != parent[u] ) {
			parent[v] = u;
			level[v] = level[u] + 1;
			dist[v] = dist[u] + w;
			dfs( v );
		}
	}
}

void build() {
	parent[0] = level[0] = dist[0] = 0;
	dfs( 0 );
	for( int i = 0; i < n; ++i ) anc[i][0] = parent[i];//, mnn[i][0] = dist[i];
	for( int j = 1; j < MAXLG ; ++j )
		for( int i = 0; i < n; ++i ){
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
			//mnn[i][j] = min( mnn[i][j - 1], mnn[anc[i][j - 1]][j - 1] );
		}
}

//true if v is ancestor of u
bool is_ancestor( int u, int v ) {
	if( level[u] < level[v] ) return false;
	int d = level[u] - level[v];
	for( int i = 0 ; i < MAXLG ; ++i )
		if( d & (1<<i) ) u = anc[u][i];
	return u == v;
}

int lca( int u, int v ) {
	if( level[u] < level[v] ) swap( u, v );
	for( int i = MAXLG - 1; i >= 0; --i )
		if( level[u] - ( 1 << i ) >= level[v] )
			//mn = min( mn, mnn[u][i] ),
			u = anc[u][i];
	if( u == v ) return u; //return mn;
	for( int i = MAXLG - 1 ; i >= 0 ; --i )
		if( anc[u][i] != anc[v][i] )
			//mn = min( mn, min( mnn[u][i], mnn[v][i] ) ),
			u = anc[u][i], v = anc[v][i];
	return anc[u][0];
	//return min( mn, min( mnn[u][0], mnn[v][0] ) );
}
