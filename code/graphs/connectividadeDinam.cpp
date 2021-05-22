// Conectividade Dinamica - UFMG
//
// Offline com Divide and Conquer e
// DSU com rollback
// O(n log^2(n))

typedef pair<int, int> T;

namespace data {
	int n, ans;
	int p[MAX], sz[MAX];
	stack<int> S;

	void build(int n2) {
		n = n2;
		for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
		ans = n;
	}
	int find(int k) {
		while (p[k] != k) k = p[k];
		return k;
	}
	void add(T x) {
		int a = x.first, b = x.second;
		a = find(a), b = find(b);
		if (a == b) return S.push(-1);
		ans--;
		if (sz[a] > sz[b]) swap(a, b);
		S.push(a);
		sz[b] += sz[a];
		p[a] = b;
	}
	int query() {
		return ans;
	}
	void rollback() {
		int u = S.top(); S.pop();
		if (u == -1) return;
		sz[p[u]] -= sz[u];
		p[u] = u;
		ans++;
	}
};

// outra ponta do intervalo ou -1 se for query
int ponta[MAX];
int ans[MAX], n, q;
T qu[MAX];

void solve(int l = 0, int r = q-1) {
	if (l >= r) {
		ans[l] = data::query();
		return;
	}
	int m = (l+r)/2, qnt = 1;
	for (int i = m+1; i <= r; i++)
		if (ponta[i]+1 and ponta[i] < l)
			data::add(qu[i]), qnt++;
	solve(l, m);
	while (--qnt) data::rollback();
	for (int i = l; i <= m; i++)
		if (ponta[i]+1 and ponta[i] > r)
			data::add(qu[i]), qnt++;
	solve(m+1, r);
	while (qnt--) data::rollback();
}
//////////////////////////////////////////////////////////
// Conectividade Dinamica - UFMG - ATENÇÃO COM A ENTRADA
// Offline com link-cut trees (aresta)
// O(n log(n))
void dyn_conn() {
	int n, q; cin >> n >> q;
	vector<int> p(2*q, -1); // outra ponta do intervalo
	for (int i = 0; i < n; i++) lct::make_tree(i);
	vector<pair<int, int>> qu(q);
	map<pair<int, int>, int> m;
	for (int i = 0; i < q; i++) {
		char c; cin >> c;
		if (c == '?') continue;
		int a, b; cin >> a >> b; a--, b--;
		if (a > b) swap(a, b);
		qu[i] = {a, b};
		if (c == '+') {
			p[i] = i+q, p[i+q] = i;
			m[make_pair(a, b)] = i;
		} else {
			int j = m[make_pair(a, b)];
			p[i] = j, p[j] = i;
		}
	}
	int ans = n;
	for (int i = 0; i < q; i++) {
		if (p[i] == -1) {
			cout << ans << endl; // numero de comp conexos
			continue;
		}
		int a = qu[i].first, b = qu[i].second;
		if (p[i] > i) { // +
			if (lct::conn(a, b)) {
				int mi = lct::query(a, b);
				if (p[i] < mi) {
					p[p[i]] = p[i];
					continue;
				}
				lct::cut(qu[p[mi]].first, qu[p[mi]].second);
                ans++;
				p[mi] = mi;
			}
			lct::link(a, b, p[i]), ans--;
		} else if (p[i] != i) lct::cut(a, b), ans++; // -
	}
}