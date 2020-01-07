// Green hackenbush is a game that each player can cut an edge
// until the root and the player that cant cut anymore loses
// O(n+m)
int n;
vector<int> adj[MAXN];
void add_edge(int u, int v) {
	adj[u].push_back(v);
	if (u != v) adj[v].push_back(u);
}

int grundy(int r) {
	vector<int> num(n), low(n);
	int t = 0;
	function<int(int,int)> dfs = [&](int p, int u) { 
		num[u] = low[u] = ++t;
		int ans = 0;
		for (int v: adj[u]) {
			if (v == p) { p += 2*n; continue; } 
			if (num[v] == 0) {
				int res = dfs(u, v);
				low[u] = min(low[u], low[v]);
				if (low[v] > num[u]) ans ^= (1 + res) ^ 1;
				else ans ^= res;
			} else low[u] = min(low[u], num[v]);
		}
		if (p > n) p -= 2*n;
		for (int v: adj[u])
			if (v != p && num[u] <= num[v]) ans ^= 1;
		return ans;
	};
	return dfs(-1, r);
}
