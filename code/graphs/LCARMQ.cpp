// O(1) query, O(n*log n) build | index 1 | rmqb( dfs() ) to run it
#define ll long long
#define pii pair<int, int>
int tim[MAXN]; // filled with invalid time (-1)
ll dist[MAXN]; // filled with 0
vector<vector<pii> > jmp;
vector<vector<pii> > g;
int n; //vertex count

vector<pii> dfs() {
	memset( tim, -1, sizeof( tim ) );
	vector<tuple<int, int, int, ll > > q;
	q.emplace_back( 1, 0, 0, 0 );
	vector<pii> ret;
	int T = 0, v, p, d;
	ll di;
	while( !q.empty() ) {
		tie( v, p, d, di ) = q.back(); q.pop_back();
		if( d ) ret.emplace_back( d, p );
		tim[v] = T++;
		dist[v] = di;
		for( auto& e : g[v] )
			if( e.first != p )
				q.emplace_back( e.first, v, d + 1, di + e.second );
	}
	return ret;
}

void rmqb( const vector<pii>& v ) {
	int n = v.size(), depth = 31 - __builtin_clz( n ) + 1;
	jmp.assign( depth + 1, v );
	for( int i = 0 ; i < depth ; ++i )
		for( int j = 0 ; j < n ; ++j )
			jmp[i+1][j] = min( jmp[i][j], jmp[i][min( n - 1, j + ( 1 << i ) )] );
}

pii rmqq( int a, int b ) {
	int dep = 31 - __builtin_clz( b - a );
	return min( jmp[dep][a], jmp[dep][b - ( 1 << dep )] );
}

int lca( int a, int b ) {
	if( a == b ) return a;
	a = tim[a], b = tim[b];
	return rmqq( min( a, b ), max( a, b ) ).second;
}

ll distance( int a, int b ) {
	int l = lca( a, b );
	return dist[a] + dist[b] - 2 * dist[l];
}


