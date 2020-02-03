// return number of bridges at variable "bridges", also dp[u] calculates back edges from u to ancestor.
// O(n+m) | start lvl[root] = 1
int bridges, n, m;
vector<pair<int, int> > g[MAXN];
int lvl[MAXN];
int dp[MAXN];

void dfs( int u ){
	dp[u] = 0;
	for( pair<int, int> pv : g[u] ){
		int v = pv.first, e = pv.second;
		if( !lvl[v] ){
			lvl[v] = lvl[u] + 1;
			dfs( v );
			dp[u] += dp[v];
		}
		else if( lvl[v] < lvl[u] ) ++dp[u];
		else if( lvl[v] > lvl[u] ) --dp[u];
	}
	--dp[u];
	if( lvl[u] > 1 && !dp[u] ) ++bridges;
}

// articulation points O(n+m) index 0
int par[MAXN], art[MAXN], low[MAXN], num[MAXN], ch[MAXN], cnt;

void articulation(int u) {
	low[u] = num[u] = ++cnt;
	for (int v : adj[u]) {
		if (!num[v]) {
			par[v] = u; ++ch[u];
			articulation(v);
			if (low[v] >= num[u]) art[u] = 1;
			if (low[v] > num[u]){
				// u-v bridge
			}
			low[u] = min(low[u], low[v]);
		}
		else if (v != par[u]) low[u] = min(low[u], num[v]);
	}
}

for (int i = 0; i < n; ++i) if (!num[i])
	articulation(i), art[i] = ch[i]>1;

