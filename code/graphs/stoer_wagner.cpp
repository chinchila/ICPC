// g is adjacency matrix bidirected
// minimum cut problem in undirected weighted graphs with non-negative weights
// O(VE)
// uncomment to recover the cut (v[bestCut] will be it)
// be carefull with cin >> n on local variable
// this changes the matrix g, if you want to use the graph please make a copy
// index 0, this algo is pretty slow
#define MAXN 1410
#define ll long long
#define INF 0x3f3f3f3f

int n, g[MAXN][MAXN];

int mincut() {
	int ans = INF;
	int w[MAXN], sel;
	bool exist[MAXN], added[MAXN];
	// int bestCut = -1;
	// set<int> v[MAXN];
	// for (int i=0; i<n; ++i) v[i].assign (1, i);
	memset (exist, true, sizeof exist);
	for (int phase=0; phase<n-1; ++phase) {
		memset (added, false, sizeof added);
		memset (w, 0, sizeof w);
		for (int j=0, prev; j<n-phase; ++j) {
			sel = -1;
			for (int i=0; i<n; ++i)
				if (exist[i] && !added[i] && (sel == -1 || w[i] > w[sel]))
					sel = i;
			if (j == n-phase-1) {
				if (w[sel] < ans) {
					ans = w[sel];
					// bestCut = sel;
				}
				// v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
				for (int i=0; i<n; ++i) g[prev][i] = g[i][prev] += g[sel][i];
				exist[sel] = false;
			}
			else {
				added[sel] = true;
				for (int i=0; i<n; ++i)  w[i] += g[sel][i];
				prev = sel;
			}
		}
	}
	return ans;
}

// karger algorithm is ok when we have no weight on edges
// find and join are from union-find, use it with path compression.
// run this at most n*n*lg(n) times and you should be fine,
// if TLE try lowering the IT variable to n*n or n*lg(n) or n
int kargerMinCut(int V){
	int E = edge.size();
	for( int v = 0 ; v < V ; ++v )
		rt[v] = v, rk[v] = 0;
	while( V > 2 ){
		int i = rand() % E;
		int u = find(edge[i].first);
		int v = find(edge[i].second);
		if(join(u, v)) --V;
	}
	int cut = 0;
	for( int i = 0 ; i < E ; ++i ){
		int u = find(edge[i].first);
		int v = find(edge[i].second);
		if( u != v ) ++cut;
	}
	return cut;
}
//on main
int IT = n*n*__lg(n);
while(IT--){
	mn = min(mn, kargerMinCut(n));
}