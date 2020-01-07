// find k such that a^k = m mod(p)
// O(sqrt(n))
#define ll long long
ll bb( ll a, ll m, ll p ) {
	unordered_map<ll, ll> babystep;
	ll b = 1, an = a;
	while( b * b < p ) b++, an = ( an * a ) % p;
	ll bstep = m;
	for( ll i = 0 ; i <= b ; ++i ) {
		babystep[bstep] = i;
		bstep = ( bstep * a ) % p;
	}
	ll gstep = an;
	for( ll i = 1 ; i <= b ; ++i ) {
		if( babystep.count( gstep ) ) return ( b * i - babystep[gstep] );
		gstep = ( gstep * an ) % p;
	}
	return -1;
}
