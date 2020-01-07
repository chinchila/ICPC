// Fast bipartite matching O(sqrt(V) * E) // indexed in 1
int N; // size of left set
vector<int> g[MAX_N];
int b[MAX_N];
int dist[MAX_N];

bool bfs() {
	queue<int> q;
	memset( dist, -1, sizeof dist );
	for( int i = 1 ; i <= N ; ++i )
		if( b[i] == -1 )
			q.push( i ), dist[i] = 0;
	bool reached = false;
	while( !q.empty() ) {
		int n = q.front();
		q.pop();
		for( int v : g[n] ) {
			if( b[v] == -1 ) reached = true;
			else if( dist[b[v]] == -1 ) {
				dist[b[v]] = dist[n] + 1;
				q.push( b[v] );
			}
		}
	}
	return reached;
}

bool dfs( int n ) {
	if( n == -1 ) return true;
	for( int v : g[n] ) {
		if( b[v] == -1 || dist[b[v]] == dist[n] + 1 ) {
			if( dfs( b[v] ) ) {
				b[v] = n, b[n] = v;
				return true;
			}
		}
	}
	return false;
}

int hk()
{
	memset( b, -1, sizeof b );
	int ans = 0;
	while( bfs() ) {
		for( int i = 1 ; i <= N ; ++i )
			if( b[i] == -1 && dfs( i ) ) ++ans;
	}
	return ans;
}

