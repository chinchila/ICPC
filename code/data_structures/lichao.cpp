// Query minimum on set of functions, do not forget lc_init() before use it
// Change f() as the function changes be carefull with qudractic funcions
// O(log n) query | O(n log n) build
typedef long long ll;
typedef pair<ll, ll> pll;
inline ll f( pll a, int x ) {
	return ( a.first * x * x ) + a.second;
}

#define MAXLC 1000000
#define INF (1ll<<60)
pll line[MAXLC << 1];

void lc_init( int lo=0, int hi=MAXLC, int node=0 ) {
	if (lo > hi || line[node].second == INF) return;
	line[node] = { 0, INF };
	int mid = (lo + hi) / 2;
	lc_init( lo, mid - 1, 2 * node + 1 );
	lc_init( mid + 1, hi, 2 * node + 2 );
}

void add_line( pll ln, int lo=0, int hi=MAXLC, int node=0 ) {
	int mid = ( lo + hi ) / 2;
	bool l = f( ln, lo ) < f( line[node], lo );
	bool m = f( ln, mid ) < f( line[node], mid );
	bool h = f( ln, hi ) < f( line[node], hi );
	if( m ) swap( line[node], ln );
	if( lo == hi || ln.second == INF ) return;
	else if( l != m ) add_line( ln, lo, mid - 1, 2 * node + 1 );
	else if( h != m ) add_line( ln, mid + 1, hi, 2 * node + 2 );
}

ll get( int x, int lo=0, int hi=MAXLC, int node=0 ) {
	int mid = ( lo + hi ) / 2;
	ll ret = f( line[node], x );
	if( x < mid ) ret = min( ret, get( x, lo, mid - 1, 2 * node + 1 ) );
	if( x > mid ) ret = min( ret, get( x, mid + 1, hi, 2 * node + 2 ) );
	return ret;
}

