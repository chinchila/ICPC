#define ll long long
//O(log n)
ll gcd( ll a, ll b ) {
	return b ? gcd( b, a % b ) : a;
}
//O(log n)
ll lcm( ll a, ll b ) {
	return a * ( b / gcd( a, b ) );
}
//O(log n)
ll mulmod( ll a, ll b, ll m ) {
	ll r = 0 ;
	for( a %= m ; b ; b >>= 1, a = ( a * 2 ) % m )
		if( b & 1 ) r = ( r + a ) % m;
	return r;
}

//O(1)?
typedef long double ld;
ll mulmod( ll a, ll b, ll m ) {
	ll q = (ld) a * (ld) b / (ld) m;
	ll r = a * b - q * m;
	return ( r + m ) % m;
}

ull mulmod(ull a, ull b, ull M) {
	ll ret = a * b - M * (ull)(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

// a^b mod m | O(log b)
ll fastexp( ll a, ll b, ll m ) {
	ll r = 1;
	for( a %= m ; b ; b >>= 1, a = mulmod(a, a, m) )
		if( b & 1 ) r = mulmod(r, a, m);
	return r;
}

// x^e | O(log e)
ll fexp(ll x, ll e) {
	ll ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

// Multiplicative Inverse
ll inv( ll a, ll m ){
	ll x, y, g;
	euclid(a, m, x, y, g);
	if(g != 1) return -1;
	return (x%m + m) % m;
}
// All inverses
ll inv[MAXN];
inv[1] = 1;
for( int i = 2 ; i < MOD ; ++i )
	inv[i] = (MOD - (MOD/i)*inv[MOD%i]%MOD)%MOD;

//O(sqrt(n))
vector<int> allDivisors( int n ) {
	vector<int> f;
	for( int i = 1 ; i <= (int)sqrt( n ) ; ++i ) {
		if( n % i == 0 ) {
			if( n / i == i ) f.push_back( i );
			else f.push_back( i ), f.push_back( n / i );
		}
	}
	return f;
}

// Recurrence using matriz
// h[i+2] = a1*h[i+1] + a0*h[i]
// [ h[i] h[i-1] ] = [ h[1] h[0] ] * [ a1 1 ] ^ (i - 1)[ a0 0 ]

// Fibonacci in logarithm time
// f(2*k) = f(k)*(2*f(k + 1) - f(k))
// f(2*k + 1) = f(k)^2 + f(k + 1)^2

// Catalan
// Cn = (2n)! / ((n+1)! * n!)
// 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, 208012, 742900, 2674440
cat[n] = (2*(2*n-1)/(n+1)) * cat[n-1]

// Stirling
// S(n, 1) = S(n, n) = 1
// S(n, k) = k*S(n-1, k) + S(n-1, k-1)

// Burnside's Lemma
// Counts the number of equivalence classes in a set.
// Let G be a group of operations acting on a set X. The number of equivalence classes given those operations |X/G| satisfies:
//
// |X/G| = 1/|G| * sum(I(g)) for each g in G
//
// Being I(g) the number of fixed points given the operation g.

