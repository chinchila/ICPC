// Find hamiltonian cycle with minimum weight
// change to commented in order to solve hamiltonian path
// O(2^n * n^2 )
// index 0
int n;
int dist[MAXN][MAXN];

int TSP(){
	int dp[1 << n][n];
	memset( dp, INF, sizeof( dp ) );
	dp[1][0] = 0;// for( int i = 0 ; i < n ; ++i ) dp[1<<i][i] = 0;
	for( int mask = 1 ; mask < 1 << n ; mask += 2 ) // mask = 0, ++mask
		for( int i = 1 ; i < n ; ++i )// i from 0
		if( ( mask & 1 << i ) != 0 )
			for( int j = 0 ; j < n ; ++j )
				if( ( mask & 1 << j ) != 0 )
					dp[mask][i] = min( dp[mask][i], dp[mask ^ (1 << i)][j] + dist[j][i] );
	int res = INF;
	for( int i = 1 ; i < n ; ++i )
		// min( res, dp[(1<<n)-1][i] )
		res = min( res, dp[(1 << n) - 1][i] + dist[i][0] );
	// reconstruct path
	int cur = (1 << n) - 1;
	int order[n];
	int last = 0;
	for( int i = n - 1 ; i >= 1 ; --i ) {// i>=0
		int bj = -1;
		for( int j = 1 ; j < n ; ++j ) {//j=0
			if( ( cur & 1 << j ) != 0 &&
//( bj==-1 ||
//dp[cur][bj] + (last == -1 ? 0 : dist[bj][last] > dp[cur][j] + (last == -1 ? 0 : dist[j][last] ) )
				( bj == -1 || dp[cur][bj] + dist[bj][last] > dp[cur][j] + dist[j][last] ) ) bj = j;
			order[i] = bj;
			cur ^= 1 << bj;
			last = bj;
		}
		return res;
	}
}

// O(n^2) with Ore condition d(u) + d(v) >= n, (u,v) not in E.
vector<int> hamilton_cycle() {
	auto X = [&](int i) { return i < n ? i : i - n; }; // faster than mod
	vector<int> cycle(n);
	iota(cycle.begin(), cycle.end(), 0);
	while (1) { 
		bool updated = false;
		for (int i = 0; i < n; ++i) {
			if (adj[cycle[i]].count(cycle[X(i+1)])) continue;
			for (int j = i+2; j < i+n; ++j) {
				if (adj[cycle[i]].count(cycle[X(j)]) &&
					adj[cycle[X(i+1)]].count(cycle[X(j+1)])) {
					for (int k = i+1, l = j; k < l; ++k, --l)
						swap(cycle[X(k)], cycle[X(l)]);
					updated = true;
					break;
				}
			}
		}
		if (!updated) break;
	}
	return cycle;
}

