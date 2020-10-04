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


//all maximum distance from vertice i in tree
int dfs1( int u, int p, vector<int> *g, int *dist){
    dist[u] = 0;
    for( int v : g[u] ) if( v != p ){
        dist[u] = max( dist[u], dfs1(v, u, g, dist)+1 );
    }
    return dist[u];
}

void dfs2( int u, int cima, int p, vector<int> *g, int *dist ){
    pair<int, int> b[2] = {{cima, p}, {0,u}};
    dist[u] = max(dist[u], cima);
    for( int v : g[u] ) if( v != p ){
        pair<int, int> l = {dist[v]+1, v};
        if( l > b[0] ) b[1] = b[0], b[0] = l;
        else if( l > b[1] ) b[1] = l;
    }
    for( int v : g[u] ) if( v != p ){
        int mx;
        if( b[0].second == v ) mx = max( cima, b[1].first );
        else mx = max( cima, b[0].first );
        dfs2( v, mx + 1, u, g, dist );
    }
}
//on main:
dfs1(1, -1, g, dist);
dfs2(1, 0, -1, g, dist);