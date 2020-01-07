// Matrix arithmetic
#define ll long long
typedef vector<ll> vec;
typedef vector<vec> mat;

const ll MOD = 1e9 + 7;
//O(n^2)
mat zeros( int n, int m )
{
	return mat( n, vec( m ) );
}
//O(n^2)
mat id( int n )
{
	mat ret = zeros( n, n );
	for( int i = 0 ; i < n ; ++i ) ret[i][i] = 1;
	return ret;
}
//O(n^2)
mat add( mat a, const mat& b )
{
	int n = a.size(), m = a[0].size();
	for( int i = 0 ; i < n ; ++i )
		for( int j = 0 ; j < m ; ++j )
			a[i][j] = (a[i][j] + b[i][j]) % MOD;
	return a;
}
//O(n^3)
mat mul( const mat& a, const mat& b )
{
	int n = a.size(), m = a[0].size(), k = b[0].size();
	mat ret = zeros( n, k );
	for( int i = 0 ; i < n ; ++i )
		for( int j = 0 ; j < k ; ++j )
			for( int p = 0 ; p < m ; ++p )
				ret[i][j] = (ret[i][j] + a[i][p] * b[p][j]) % MOD;
	return ret;
}
//O(log n)
mat pow( const mat& a, ll p )
{
	if( p == 0 ) return id( a.size() );
	mat ret = pow( mul( a, a ), p >> 1 );
	if( p & 1 ) ret = mul( ret, a );
	return ret;
}

