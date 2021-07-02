// Query range: query( r ) - query( l -1 ) | index 1 | O(log n)
#define ll long long
struct BIT {
	ll b[MAXN]={};
	ll sum( int x ) {
		ll r = 0;
		for(x += 2 ; x ; x -= x & -x ) r += b[x];
		return r;
	}
	void upd( int x, ll v ) {
		for(x += 2 ; x < MAXN ; x += x & -x ) b[x] += v;
	}
};
struct BITRange {
	BIT a,b;
	ll sum( int x ) {
		return a.sum( x ) * x + b.sum( x );
	}
	ll query( int l, int r ) { 
		return sum( r ) - sum( l - 1 ); 
	} 
	void update( int l, int r, ll v ) {
		a.upd( l, v ), a.upd( r + 1, -v );
		b.upd( l, -v*( l - 1 ) ), b.upd( r + 1, v * r );
	}
};

// dinamica
template <class T>
class FenwickTree {
public:
	void init(int _n) {
		this->n = _n;
		bit.assign(n + 1, 0);
	}

	void init(const std::vector<T> &a) {
		n = a.size();
		bit.assign(n + 1, 0);
		for(int i = 1; i <= n; i++) {
			bit[i] += a[i - 1];
			if(i + (i & -i) <= n) {
				bit[i + (i & -i)] += bit[i];
			}
		}
	}

	T qry(int x) {
		x = std::min(x, (int)bit.size() - 1);
		T ans = 0;
		for(; x > 0; x -= x & -x) {
			ans += bit[x];
		}
		return ans;
	}

	void upd(int x, T v) {
		if(x <= 0) return;
		for(; x <= n; x += x & -x) {
			bit[x] += v;
		}
	}
private:
	int n;
	std::vector<T> bit;
};