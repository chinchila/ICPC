// do not forget fastexp
// some numbers that have primitive root:
// 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 13, 14, 17, 18, 19, 22, 23, 25, 26, 27, 29
// O(n) eu acho
#define ll long long

ll root( ll p ) {
	ll n = p-1;
	vector<ll> fact;
	for( int i = 2 ; i * i <= n ; ++i ) if( n % i == 0 ) {
		fact.push_back( i );
		while( n % i == 0 ) n /= i;
	}
	if( n > 1 ) fact.push_back( n );
	for( int res = 2 ; res <= p ; ++res ) {
		bool ok = true;
		for( size_t i = 0 ; i < fact.size() && ok ; ++i )
			ok &= fastexp( res, ( p - 1 ) / fact[i], p ) != 1;
		if( ok )  return res;
	}
	return -1;
}

