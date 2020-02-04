// Yes if both trees are isomorphic | Index 1 | O(nlogn)
typedef vector<int> vi;
int n, a, b;
vi adj[2][MAXN];
int vis[MAXN], p[MAXN], sz[MAXN], x;
vi centr[2];
map<map<int, int>, int> m;
void dfsc(int t, int u) {
	vis[u] = x;
	sz[u] = 1;
	int ok = 1;
	for (int v : adj[t][u]) {
		if (v == p[u]) continue;
		if (vis[v] != x) p[v]=u, dfsc(t, v);
		sz[u] += sz[v];
		if (sz[v] > n/2) ok=0;
	}
	if (n-sz[u] > n/2) ok=0;
	if (ok) centr[t].push_back(u);
}
int dfs(int t, int u) {
	vis[u]=x;
	map<int, int> c;
	for (int v : adj[t][u]) {
		if (v == p[u]) continue;
		if (vis[v] != x) p[v]=u, dfs(t, v);
		c[sz[v]]++;
	}
	if (!m.count(c)) m[c] = m.size();
	return sz[u]=m[c];
}

// This goes on Main
int es[2];
for( int j = 0 ; j < 2 ; ++j ) {
	++x;
	p[1] = -1;
	dfsc(j, 1);
	++x;
	p[centr[j][0]] = -1;
	es[j] = dfs(j, centr[j][0]);
}
es[0] = es[0] == es[1];
if (!es[0] && centr[0].size()>1) {
	++x, p[centr[0][1]]=-1;
	es[0] = dfs(0, centr[0][1]) == es[1];
}
puts( ( es[0] ? "YES" : "NO" ) );

