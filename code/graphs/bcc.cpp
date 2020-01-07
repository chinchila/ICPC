// Complexity O(n+m)
int N;
vector<int> adj[MAXN];
vector<int> bcc[MAXN];
int bccnum = 0;
int in[MAXN], low[MAXN], t = 0;
stack<pair<int, int> > s;
bool visited[MAXN];

void dfs( int u, int p = -1 ) {
	visited[u] = true;
	low[u] = in[u] = t++;
	for( int v : adj[u] ) if ( v != p ) {
		if( !visited[v] ) {
			s.emplace( v, u );
			dfs( v, u );
			low[u] = min( low[u], low[v] );
			if( low[v] >= in[u] ) { // u is articulation
				while( true ) {
					auto p = s.top();
					s.pop();
					int a = p.first, b = p.second;
					if( bcc[a].empty() || bcc[a].back() != bccnum )
						bcc[a].push_back( bccnum );
					if( bcc[b].empty() || bcc[b].back() != bccnum )
						bcc[b].push_back( bccnum );
					if( a == v && b == u ) break;
				}
				++bccnum;
			}
		}
		else if( in[v] < in[u] ) {
			low[u] = min( low[u], in[v] );
			s.emplace( v, u );
		}
	}
}

void tarjan() {
	for( int i = 1 ; i <= N ; ++i ) if ( !visited[i] ) dfs( i );
}

bool biconnected( int u, int v ) {
	for( int c : bcc[u] )
		if( binary_search( bcc[v].begin(), bcc[v].end(), c ) )
			return true;
	return false;
}

