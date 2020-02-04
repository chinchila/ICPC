// knapsack 0-1 O(n * wei) | index 0
// maximum profit for weight j
// wei is max weigth
// v is price, w is weight dp[MAXWEIGHT+1]
for( int i = 0 ; i < n ; ++i )
	for( int j = wei ; j >= w[i] ; --j )
		dp[j] = max( dp[j], v[i] + dp[j - w[i]] );

// repetition allowed with items dp[0] is pred dp[1] is formula
// bb is max weight, n is size
// wei = weights, val = values
for( int i = 0 ; i <= bb ; ++i ) {
	for( int j = 0 ; j < n ; ++j ) {
		if( i >= wei[j] ){
			dp[1][i] = max( dp[1][i], val[j] + dp[1][i - wei[j]] );
			dp[0][i] = j;
		}
	}
}
int m = bb;
while( m != 0 ){
	// access weight with wei[dp[0][m]]
	m -= wei[dp[0][m]];
}

// knapsack
// F[a] := minimum weight for profit a
int knapsackP(vector<int> p, vector<int> w, int c) {
	int n = p.size(), P = accumulate(p.begin(), p.end(), 0);
	vector<int> F(P+1, c+1); F[0] = 0;
	for (int i = 0; i < n; ++i)
		for (int a = P; a >= p[i]; --a)
			F[a] = min(F[a], F[a-p[i]] + w[i]);
	for (int a = P; a >= 0; --a) if (F[a] <= c) return a;
}

// knapsack with itens in order
val[n] = 0;
reverse(val, val+n+1);
for( int i = 1 ; i <= n ; ++i ) {
	for( int j = wei ; j >= val[i] ; --j ) {
		if( dp[i-1][j] > dp[i-1][j-val[i]]+val[i] )
			dp[i][j] = dp[i-1][j];
		else
			dp[i][j] = dp[i-1][j-val[i]] + val[i],
			dp2[i][j] = 1;
	}
	for( int j = val[i] - 1 ; j >= 0 ; --j ) dp[i][j] = dp[i-1][j];
}
int k = wei;
for( int i = n ; i > 0 ; --i )
	if( dp2[i][k] ) printf("%d ", val[i] ), k -= val[i];
printf("%d\n", dp[n][wei] );

// bounded knapsack
// ps = values ; ws = weights
// ms = quantity ; W = weight wanted ; n = item quantity
int solve(){
	int dp[n+1][W+1];
	for( int i = 0; i < n; ++i ) {
		for( int s = 0; s < ws[i]; ++s ) {
			int alpha = 0;
			queue<int> que;
			deque<int> peek;
			for( int w = s ; w <= W ; w += ws[i] ) {
				alpha += ps[i];
				int a = dp[i][w]-alpha;
				que.push( a );
				while( !peek.empty() && peek.back() < a ) peek.pop_back();
				peek.push_back(a);
				while( que.size() > ms[i]+1 ) {
					if (que.front() == peek.front()) peek.pop_front();
					que.pop();
				}
				dp[i+1][w] = peek.front()+alpha;
			}
		}
	}
	int ans = 0;
	for( int w = 0 ; w <= W ; ++w )
		ans = max( ans, dp[n][w] );
	return ans;
}

// Branch and bound, O(2^c) where c is small most of time
template <class T>
struct knapsack {
	T c; 
	struct item { T p, w; };
	vector<item> is;
	void add_item(T p, T w) {
		is.push_back({p, w});
	}
	T det(T a, T b, T c, T d) {
		return a * d - b * c;
	}
	T z;
	void expbranch(T p, T w, int s, int t) {
		if (w <= c) {
			if (p >= z) z = p;
			for (; t < is.size(); ++t) {
				if (det(p - z - 1, w - c, is[t].p, is[t].w) < 0) return;
				expbranch(p + is[t].p, w + is[t].w, s, t + 1);
			}
		} else {
			for (; s >= 0; --s) {
				if (det(p - z - 1, w - c, is[s].p, is[s].w) < 0) return;
				expbranch(p - is[s].p, w - is[s].w, s - 1, t);
			}
		}
	}
	T solve() {
		sort(is.begin(), is.end(), [](const item &a, const item &b) { 
			return a.p * b.w > a.w * b.p;
		});
		T p = 0, w = 0;
		z = 0;
		int b = 0; 
		for (; b < is.size() && w <= c; ++b) {
			p += is[b].p;
			w += is[b].w;
		}
		expbranch(p, w, b-1, b);
		return z;
	}
};

