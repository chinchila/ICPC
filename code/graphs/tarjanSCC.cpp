// O(n+m) | index 1
int n;
vector<int> adj[MAXN];
int scc[MAXN], sccnum = 0;
int in[MAXN], low[MAXN], t = 0;
stack<int> s;
bool instack[MAXN];

void dfs( int u ) {
	low[u] = in[u] = t++;
	s.push( u );
	instack[u] = true;
	for( int v : adj[u] )
		if( in[v] == -1 )
			dfs( v ),
			low[u] = min( low[u], low[v] );
		else if( instack[v] )
			low[u] = min(low[u], in[v]);
	if( low[u] == in[u] ) {
		while( true ) {
			int su = s.top();
			s.pop();
			scc[su] = sccnum;
			instack[su] = false;
			if (su == u) break;
		}
		++sccnum;
	}
}

void tarjan() {
	memset( scc, -1, sizeof scc );
	memset( in, -1, sizeof in );
	for( int i = 1 ; i <= n ; ++i ) if (scc[i] == -1) dfs(i);
}

// Mount condensed graph
memset(f, -1, sizeof(f));
for( int i = 0 ; i < sccnum ; ++i ) {
	for( int j : comps[i] ) {
		for( int k : adj[j] ) {
			int sc = scc[k];
			if( f[sc] != i && i != sc ) {
				f[sc] = i;
				fim[i].push_back( sc );
				ge[sc]++;
			}
		}
	}
}

