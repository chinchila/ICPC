
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct RollbackUF {
	vi e; vector<pii> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return st.size(); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

struct Edge { int a, b; ll w; };
struct Node {
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

pair<ll, vi> dmst(int n, int r, vector<Edge>& g) {
	RollbackUF uf(n);
	vector<Node*> heap(n);
	for (Edge e : g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n), par(n);
	seen[r] = r;
	vector<Edge> Q(n), in(n, {-1,-1}), comp;
	deque<tuple<int, int, vector<Edge>>> cycs;
	for(int s=0;s<n;++s) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			if (!heap[u]) return {-1,{}};
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			Q[qi] = e, path[qi++] = u, seen[u] = s;
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) {
				Node* cyc = 0;
				int end = qi, time = uf.time();
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.join(u, w));
				u = uf.find(u), heap[u] = cyc, seen[u] = -1;
				cycs.push_front({u, time, {&Q[qi], &Q[end]}});
			}
		}
		for(int i=0;i<qi;++i) in[uf.find(Q[i].b)] = Q[i];
	}
	for (auto& [u,t,comp] : cycs) {
		uf.rollback(t);
		Edge inEdge = in[u];
		for (auto& e : comp) in[uf.find(e.b)] = e;
		in[uf.find(inEdge.b)] = inEdge;
	}
	for(int i=0;i<n;++i) par[i] = in[i].a;
	return {res, par};
}