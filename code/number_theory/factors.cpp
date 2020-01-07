// Prime factors (up to 9*10^13. For greater see Pollard Rho) | O(sqrt( n ))
// sieve( sqrt( n ) ); to get all primes until sqrt(n)
vector<int> factors;
int ind=0, pf = pr[0];
while( pf * pf <= n ) {
	while( n%pf == 0 ) n /= pf, factors.push_back( pf );
	pf = pr[++ind];
}
if( n != 1 ) factors.push_back( n );

vector<ll> divisors( ll n) {
	vector<ll> v;
	for( ll i = 1 ; i <= sqrt( n ) ; ++i ){
		if( n % i == 0 ) {
			if( n / i == i ) v.push_back( i );
			else v.push_back( i ), v.push_back( n/i );
		}
	}
	return v;
}


