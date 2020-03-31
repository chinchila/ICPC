// Computes the lagrange polynomial interpolation
#define ll long long

ll ifat[MAXK],fat[MAXK];

class LagrangePoly {
public:
	LagrangePoly(vector<ll> _a) {
		y = _a;
		den.resize(y.size());
		int n = (int) y.size();
		for(int i = 0; i < n; i++) {
			y[i] = (y[i] % MOD + MOD) % MOD;
			den[i] = ifat[n - i - 1] * ifat[i] % MOD;
			if((n - i - 1) % 2 == 1) {
				den[i] = (MOD - den[i]) % MOD;
			}
		}
	}

	ll getVal(ll x) {
		int n = y.size();
		x %= MOD;
		if(x < n) return y[(int)x];
		vector<ll> l, r;
		l.resize(n);
		l[0] = 1;
		for(int i = 1; i < n; i++)
			l[i] = l[i - 1] * (x - (i - 1) + MOD) % MOD;
		r.resize(n);
		r[n - 1] = 1;
		for(int i = n - 2; i >= 0; i--)
			r[i] = r[i + 1] * (x - (i + 1) + MOD) % MOD;
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			ll coef = l[i] * r[i] % MOD;
			ans = (ans + coef * y[i] % MOD * den[i]) % MOD;
		}
		return ans;
	}
	
private:
	vector<ll> y, den;
};

ll fastexp(ll x, ll e) {
	ll ans = 1;
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

// in main
fat[0] = ifat[0] = 1;
for(int i = 1; i < MAXK; i++) {
	fat[i] = (fat[i - 1] * i) % MOD;
	ifat[i] = fastexp(fat[i], MOD - 2)%MOD;
}
