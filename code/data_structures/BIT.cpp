// Query range: query( r ) - query( l -1 ) | index 1 | O(log n)
#define ll long long
struct BIT {
	ll b[MAXN]={};
	ll sum( int x ) {
		ll r = 0;
		for(x += 2 ; x ; x -= x & -x ) r += b[x];
		return r;
	}
	void upd( int x, ll v ) {
		for(x += 2 ; x < MAXN ; x += x & -x ) b[x] += v;
	}
};
struct BITRange {
	BIT a,b;
	ll sum( int x ) {
		return a.sum( x ) * x + b.sum( x );
	}
	ll query( int l, int r ) { 
		return sum( r ) - sum( l - 1 ); 
	} 
	void update( int l, int r, ll v ) {
		a.upd( l, v ), a.upd( r + 1, -v );
		b.upd( l, -v*( l - 1 ) ), b.upd( r + 1, v * r );
	}
};
