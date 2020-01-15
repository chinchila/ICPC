// find k such that a^k = m mod(p), with p prime
// O(sqrt(n))
ll bb( ll a, ll m, ll p ) {
	unordered_map<ll, ll> mp;
	ll b = 1, an = a;
	while( b * b < p ) b++, an = ( an * a ) % p;
	ll bs = m;
	for( ll i = 0 ; i <= b ; ++i ) {
		mp[bs] = i;
		bs = ( bs * a ) % p;
	}
	ll gs = an;
	for( ll i = 1 ; i <= b ; ++i ) {
		if( mp.count( gs ) ) return ( b * i - mp[gs] );
		gs = ( gs * an ) % p;
	}
	return -1;
}

// bellow works for some C composite A^k = B mod C
// O(sqrt(n)), do not forget fastexp
#define ll long long
ll bb(ll A, ll B, ll C) {
	A %= C, B %= C;
	if(B == 1) return 0;
	ll k = 0;
	ll tmp = 1;
	for(int d = __gcd(A, C) ; d != 1 ; d = __gcd(A, C)) {
		if(B%d) return -1;
		B /= d, C /= d;
		tmp = tmp*(A/d)%C;
		++k;
		if(tmp == B) return k;
	}
	unordered_map<ll, int> mp;
	ll mul = B;
	ll m = sqrt(C);
	for(ll j = 0 ; j < m ; ++j)
		mp[mul] = j, mul = mul*A%C;
	ll am = fastexp(A, m, C);
	mul = tmp;
	for(ll j = 1 ; j <= m + 1 ; ++j) {
		mul = mul*am%C;
		if(mp.count(mul)) return j*m-mp[mul]+k;
	}
	return -1;
}

