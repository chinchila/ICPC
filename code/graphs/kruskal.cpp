// O(m log(m))
#define ll long long
struct edge {
	int u, v; ll w;
	edge( int _u, int _v, ll _w ) : u(_u),v(_v),w(_w) {}
	bool operator < ( const edge &o ) const {
		return w < o.w;
	}
};

vector<edge> edges;
int root[MAXN];
int n, m;

int find( int x ) { return ( x == root[x] ) ? x : root[x] = find( root[x] ); }

bool merge( int u, int v ){
	if( ( u = find( u ) ) == ( v = find( v ) ) ) return false;
	root[u] = v;
	return true;
}

ll kruskal()
{
	ll cost = 0;
	sort( edges.begin(), edges.end() );
	for( int i = 0 ; i <= n ; ++i ) root[i] = i;
	for( int i = 0 ; i < m ; ++i )
		if( merge( edges[i].u, edges[i].v ) ) cost += edges[i].w;
	return cost;
}

