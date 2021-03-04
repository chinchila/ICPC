// Matrix arithmetic
#define ll long long
typedef vector<ll> vec;
typedef vector<vec> mat;

const ll MOD = 1e9 + 7;
//O(n*m)
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
//O(n*m)
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

//O(n*m)
mat sub( mat a, mat b )
{
	int n = a.size(), m = a[0].size();
	for( int i = 0 ; i < n ; ++i )
		for( int j = 0 ; j < m ; ++j )
			a[i][j] = (a[i][j] - b[i][j]);
	return a;
}
//O(n*m)
template<typename T> mat mul( mat& a, T b )
{
	int n = a.size(), m = a[0].size();
	mat ret = zeros( n, m );
	for( int i = 0 ; i < n ; ++i )
		for( int j = 0 ; j < m ; ++j )
			ret[i][j] = b*a[i][j];
	return ret;
}
//Square of norm
//O(n) for vector n*m for matrix
template<typename T> T norm(mat &v1){
	T res(0);
	int n = v1.size(), m = v1[0].size();
	for(int i = 0 ; i < n ; ++i )
		for(int j = 0 ; j < m ; ++j )
			res += v1[i][j]*v1[i][j];
	return res;
}

//Find 2D lattice basis
//Polynomial time, if you need it it will pass
template<typename T> T gauss(mat v1, mat v2){
    while(1) {
        if(norm<T>(v2) < norm<T>(v1)) swap(v1,v2);
		T a = mul(v1,v2)[0][0], b = mul(v1,v1)[0][0];
        auto mr = divmod(a, b);
        if(mr.first == 0) return v1[0][0];
        v2 = sub(v2, mul(v1, mr.first));
	}
}
// Example: find g from f*h = g mod q
// f and g both smaller than sqrt(q/2) holds
// this gives us f*h = q*k+g
// with h about the same size of q
// and k about the same size of f and g
// thus f*[h, 1] + (-k)*[q, 1] = [g, f-k]
// now we can solve the Closest vector problem
scanf(" %s %s", q_s, h_s);
bint q(q_s), h(h_s);
mat m_q = zeros(2, 1);
m_q[0][0] = q;
m_q[1][0] = bint(1);
mat m_h = zeros(2, 1);
m_h[0][0] = h;
m_h[1][0] = bint(1);
bint g_met = gauss<bint>(m_q, m_h);
cout << g_met%q << endl;

//O(n*m)
mat transpose(mat a){
	int n = a.size(), m = a[0].size();
	mat ret = zeros( m, n );
	for( int i = 0 ; i < n ; ++i )
		for( int j = 0 ; j < m ; ++j )
			ret[j][i] = a[i][j];
	return ret;
}
