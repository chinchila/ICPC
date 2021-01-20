// numeros coprimos menores ou iguais a n
// O(sqrt(n))
int phi(int n) {
	int result = n;
	for( int i = 2 ; i * i <= n ; ++i ){
		if( n % i == 0 ){
			while( n % i == 0 ) n /= i;
			result -= result / i;
		}
	}
	if( n > 1 ) result -= result / n;
    return result;
}
// Compute array with all phi until N
// O(n*?) it is not so slow, check if its better to
// O(k*sqrt(n)) or this | this one was faster on SPOJ
// Better use linear sieve for this
int phi[MAXN];
void totient( int N ) {
	for( int i = 1 ; i < N ; ++i)  phi[i]=i;
	for( int i = 2 ; i < N ; i += 2 ) phi[i] >>= 1;
	for( int j = 3 ; j < N ; j += 2 ) if( phi[j]==j ) {
		--phi[j];
		for( int i = 2 * j ; i < N ; i += j ) phi[i] = phi[i] / j * ( j - 1 );
	}
}

// Carmichael function
// smallest m such that a^m = 1 mod n
ll carmichael( ll n ){
	if( n == 1 ) return 1;
	map<ll, int> v;
	ll res = -1;
	fator(n, v);
	for( auto fac : v ){
		ll p = fac.first, r = fac.second;
		ll phi = fastexp(p, r-1, n)*(p-1);
		if( p == 2 && r >= 3 ) phi /= 2;
		if(res == -1) res = phi;
		else res = lcm(res, phi);
	}
	return res;
}
