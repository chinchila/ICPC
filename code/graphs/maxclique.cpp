// Complexity is 2^n or 2^(n/2) or something like this
// if you need this it will probably pass
// uncoment if n > 64
// Usage: MaxClique mc; mc.init(vertices); mc();
#define maxn 64
// #define uint64_t bitset<maxn>
// #define pcount(k) (k).count()
// #define ctz(k) (k)._Find_first()
#define pcount __builtin_popcountll
#define ctz(k) __builtin_ctzll(k&-k)

struct MaxClique {
	int n, deg[maxn];
	uint64_t adj[maxn], ans;
	vector<pair<int, int>> edge;
	void init(int n_) {
		n = n_;
		fill(adj, adj + n, 0);
		fill(deg, deg + n, 0);
		edge.clear();
	}
	void add_edge(int u, int v) {
		edge.emplace_back(u, v);
		++deg[u], ++deg[v];
	}
	vector<int> operator()() {
		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](int u, int v) { return deg[u] < deg[v]; });
		vector<int> id(n);
		for (int i = 0; i < n; ++i) id[ord[i]] = i;
		for (auto e : edge) {
			int u = id[e.first], v = id[e.second];
			adj[u] |= uint64_t(1)<<v;
			adj[v] |= uint64_t(1)<<u;
		}
		uint64_t r(0), p(1);
		p = (p<<n)-1;
		// for( int i = 0 ; i < n ; ++i ) p.set(i);
		ans = 0;
		dfs(r, p);
		vector<int> res;
		for (int i = 0; i < n; ++i) {
			if ((ans>>i&uint64_t(1))/*.count()*/) res.push_back(ord[i]);
		}
		return res;
	}
	void dfs(uint64_t r, uint64_t p) {
		if (p == 0) {
			if (pcount(r) > pcount(ans)) ans = r;
			return;
		}
		if (pcount(r|p) <= pcount(ans)) return;
		int x = ctz(p);
		uint64_t c = p & ~adj[x];
		while (c/*.count()*/ > 0) {
			x = ctz(c);
			uint64_t xmask(1);
			xmask <<= x;
			r |= xmask;
			dfs(r, p & adj[x]);
			r &= ~(xmask);
			p &= ~(xmask);
			c ^= (xmask);
		}
	}
};