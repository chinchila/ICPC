// do not forget fastexp on numeric_fundamentals.cpp
// be careful to use mulmod when n and p are big.
#define ll long long
bool modsqrt( ll n, ll p, ll &root1, ll &root2 ){
	ll q = p - 1;
	ll ss = 0;
	ll z = 2;
	ll c, r, t, m;

	if( fastexp(n, (p - 1) / 2, p) != 1 ){
		root1 = 0;
		root2 = 0;
		return false;
	}

	while ((q & 1) == 0)
		ss += 1, q >>= 1;
 
	if( ss == 1 ){
		root1 = fastexp(n, (p + 1) / 4, p);
        root2 = p - root1;
		return true;
	}
 
	while( fastexp(z, (p - 1) / 2, p) != p - 1 )
		++z;
 
	c = fastexp(z, q, p);
	r = fastexp(n, (q + 1) / 2, p);
	t = fastexp(n, q, p);
	m = ss;
 
	while( true ){
		ll i = 0, zz = t;
		ll b = c, e;
		if (t == 1) {
            root1 = r;
            root2 = p - r;
			return true;
		}
		while (zz != 1 && i < (m - 1))
			zz = mulmod(zz, zz, p), ++i;
		e = m - i - 1;
		while( e > 0 )
			b = mulmod(b, b, p), --e;
		r = mulmod(r, b, p);
		c = mulmod(b, b, p);
		t = mulmod(t, c, p);
		m = i;
	}
}