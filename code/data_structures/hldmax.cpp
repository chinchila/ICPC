// hld::init() to build | O( n log n ) to build and O(log n) to query/update
// Be carefull with x*10^5 limits
#define ll long long
#define MAXSEG 2*MAXN
int N;
vector<int> adj[MAXN];

namespace hld {
	int parent[MAXN];
	vector<int> ch[MAXN];
	int depth[MAXN], sz[MAXN], in[MAXN], rin[MAXN], nxt[MAXN], out[MAXN], t = 0;
	void dfs_sz( int n = 0, int p = -1, int d = 0 ) {
		parent[n] = p, sz[n] = 1, depth[n] = d;
		for( auto v : adj[n] ) if( v != p ) {
			dfs_sz( v, n, d + 1 );
			sz[n] += sz[v];
			ch[n].push_back( v );
			if( sz[v] > sz[ch[n][0]] )
				swap( ch[n][0], ch[n].back() );
		}
	}
	void dfs_hld( int n = 0 ) {
		in[n] = t++;
		rin[in[n]] = n;
		for( auto v : ch[n] ) {
			nxt[v] = ( v == ch[n][0] ? nxt[n] : v );
			dfs_hld( v );
		}
		out[n] = t;
	}

	void init() {
		dfs_sz();
		dfs_hld();
	}

	int lca( int u, int v ) {
		while( nxt[u] != nxt[v] ) {
			if( depth[nxt[u]] < depth[nxt[v]] ) swap( u, v );
			u = parent[nxt[u]];
		}
		return depth[u] < depth[v] ? u : v;
	}

	// insert segtree with lazy here
	void update_subtree( int n, int x ) {
		update( in[n], out[n] - 1, x);
	}

	// Is v in subtree of v?
	bool inSubTree( int u, int v ) {
		return in[u] <= in[v] && in[v] < out[u];
	}

	ll query_subtree( int n ) {
		return query( in[n], out[n] - 1 );
	}

	void update_path( int u, int v, int x, bool ignore_lca = false ) {
		while( nxt[u] != nxt[v] ) {
			if( depth[nxt[u]] < depth[nxt[v]] ) swap( u, v );
			update( in[nxt[u]], in[u], x );
			u = parent[nxt[u]];
		}
		if( depth[u] < depth[v] ) swap( u, v );
		update( in[v] + ignore_lca, in[u], x );
	}

	ll query_path( int u, int v, bool ignore_lca = false ) {
		ll ret = 0;
		while( nxt[u] != nxt[v] ) {
			if( depth[nxt[u]] < depth[nxt[v]] ) swap( u, v );
			ret = max( ret, query( in[nxt[u]], in[u] ) );
			u = parent[nxt[u]];
		}
		if( depth[u] < depth[v] ) swap(u, v);
		ret = max( ret, query( in[v] + ignore_lca, in[u] ) );
		return ret;
	}
}
