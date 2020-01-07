// Shortest path O(n^3) adjacency matrix with weights and INF when no weight
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
void fw( int n, vector<vector<ll> > &d ) {
	for( int k = 0 ; k < n ; ++k )
		for( int i = 0 ; i < n ; ++i )
			for( int j = 0 ; j < n ; ++j )
				d[i][j] = min( d[i][j], d[i][k] + d[k][j] );
}

