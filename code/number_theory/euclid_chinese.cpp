#define ll long long
// Solve: x * a + y * b = gcd(a,b) | O(log n)
void euclid( ll a, ll b, ll &x, ll &y, ll &gcd ) {
	if( b ) euclid( b, a % b, y, x, gcd ), y -= x * ( a / b );
	else x = 1, y = 0, gcd = a;
}

// Chinese remainder, solves t = a mod m1 ; t = b mod m2 ; ans = t mod lcm( m1, m2 )
// O(log n)
bool chinese( ll a, ll b, ll m1, ll m2, ll &ans, ll &lcm ) {
	ll x, y, g, c = b - a;
	euclid( m1, m2, x, y, g );
	if( c % g ) return false;

	lcm = m1 / g * m2;
	ans = ( ( a + c / g * x % ( m2 / g ) * m1 ) % lcm + lcm ) % lcm;
	return true;
}


// Solve: a * x + b * y = c | O(log n)
bool euclidFind( ll a, ll b, ll c, ll &x0, ll &y0, ll &g ) {
	euclid( abs( a ), abs( b ), x0, y0, g );
	if( c % g ) return false;
	x0 *= c / g, y0 *= c / g;
	if( a < 0 ) x0 = -x0;
	if( b < 0 ) y0 = -y0;
	return true;
}

void shift( ll &x, ll &y, ll a, ll b, ll cnt ) {
	x += cnt * b;
	y -= cnt * a;
}

// Count all solutions in range | O(solutions * log n)
// it can be very slow
ll all( ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy ) {
	ll x, y, g;
	if( !find_any_solution( a, b, c, x, y, g ) ) return 0;
	a /= g, b /= g;
	ll sign_a = a > 0 ? +1 : -1;
	ll sign_b = b > 0 ? +1 : -1;
	shift( x, y, a, b, ( minx - x ) / b );
	if( x < minx ) shift( x, y, a, b, sign_b );
	if( x > maxx ) return 0;
	ll lx1 = x;
	shift( x, y, a, b, ( maxx - x ) / b );
	if( x > maxx ) shift( x, y, a, b, -sign_b );
	ll rx1 = x;
	shift( x, y, a, b, - ( miny - y ) / a );
	if( y < miny ) shift( x, y, a, b, -sign_a );
	if( y > maxy ) return 0;
	ll lx2 = x;
	shift( x, y, a, b, - ( maxy - y ) / a );
	if( y > maxy ) shift( x, y, a, b, sign_a );
	ll rx2 = x;
	if( lx2 > rx2 ) swap( lx2, rx2 );
	ll lx = max( lx1, lx2 );
	ll rx = min( rx1, rx2 );
	if( lx > rx ) return 0;
	return ( rx - lx ) / abs( b ) + 1;
}

