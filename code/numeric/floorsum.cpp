// calculate sum i=0 to n-1 (floor( (a*i + b) / m ) )
// O( log (n+ m + a + b) ) ?
#define ll long long
ll floor_sum(ll n, ll m, ll a, ll b){
	ll ans = 0;
	if (a >= m) {
		ans += (n - 1) * n * (a / m) / 2;
		a %= m;
	}
	if (b >= m) {
		ans += n * (b / m);
		b %= m;
	}
	ll yMax = (a * n + b) / m;
	ll xMax = yMax * m - b;
	if (yMax == 0ll) return ans;
	ans += (n - (xMax + a - 1) / a) * yMax;
	ans += floor_sum(yMax, a, m, (a - xMax % a) % a);
	return ans;
}
