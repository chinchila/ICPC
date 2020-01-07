// start d with INF, only works with unweighted
// run bfs on all vertices O(n*m)

int d[MAXN][MAXN];
int diam;
void bfs( int s ) {
	queue<int> q;
	q.push( s );
	d[s][s] = 0;
	while( !q.empty() ) {
		int u = q.front(); q.pop();
		for( int v : g[u] ) {
			if( d[s][v] == INF ){
				d[s][v] = d[v][s] = min( d[s][u] + 1, d[v][s] );
				diam = max( d[s][u], diam );
				q.push( v );
			}
		}
	}
}

// on tree O(n+m)
#define INF 0x3f3f3f3f
int vis[MAXN];
vector<int> g[MAXN];
int t = 1;

void dfs( int u, int c, int &mc, int &x ){
	vis[u] = t;
	c++;
	for( int v : g[u] ) {
		if( vis[v] != t ) {
			if( c >= mc ) mc = c, x = v;
			dfs( v, c, mc, x );
		}
	}
}

int diameter(){
	int diam = -INF, x = -1;
	dfs( 1, 0, diam, x );
	++t;
	dfs( x, 0, diam, x );
	return diam;
}
