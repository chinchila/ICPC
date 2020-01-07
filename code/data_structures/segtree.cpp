// Index 0
// O(n log n) build | O(log n) query
// check if 0 should be returned on query (INF on max/min)
#define ll long long
ll st[MAXSEG];
ll lazy[MAXSEG];

void push(int node, int lo, int hi) {
	if (lazy[node] == 0) return;
	st[node] += lazy[node]; //(hi-lo+1)*lazy[node] for sum
	if (lo != hi) {
		lazy[2 * node + 1] += lazy[node];
		lazy[2 * node + 2] += lazy[node];
	}
	lazy[node] = 0;
}

void update(int s, int e, ll x, int lo=0, int hi=-1, int node=0) {
	if (hi == -1) hi = N - 1;
	push(node, lo, hi);
	if (hi < s || lo > e) return;
	if (lo >= s && hi <= e) {
		lazy[node] = x;
		push(node, lo, hi);
		return;
	}
	int mid = (lo + hi) / 2;
	update(s, e, x, lo, mid, 2 * node + 1);
	update(s, e, x, mid + 1, hi, 2 * node + 2);
	st[node] = max(st[2 * node + 1], st[2 * node + 2]);
}

ll query(int s, int e, int lo=0, int hi=-1, int node=0) {
	if (hi == -1) hi = N - 1;
	push(node, lo, hi);
	if (hi < s || lo > e) return -0x3f3f3f3f;
	if (lo >= s && hi <= e) return st[node];
	int mid = (lo + hi) / 2;
	return max(query(s, e, lo, mid, 2 * node + 1),
			query(s, e, mid + 1, hi, 2 * node + 2));
}
