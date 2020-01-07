// Bipartite matching O( VE ) ; w[i][j] = edge between left i and right j
// mr, mc are match row and column
bool match( int i, vector<vector<int> > w, int *mr, int *mc, int *vis, int x ) {
	for( int j = 0 ; j < w[i].size() ; ++j ) {
		if( w[i][j] && vis[j] != x ) {
			vis[j] = x;
			if( mc[j] < 0 || match( mc[j], w, mr, mc, vis, x ) ) {
				mr[i] = j, mc[j] = i;
				return true;
			}
		}
	}
	return false;
}

int bi( vector<vector<int> > w ) {
	int vis[MAX_N] = {};
	int mr[MAX_N];
	int mc[MAX_N];
	int x = 0;
	int ct = 0;

	memset( mr, -1, sizeof( mr ) );
	memset( mc, -1, sizeof( mc ) );

	for( int i = 0; i < w.size(); ++i )
		if( match( i, w, mr, mc, vis, ++x ) ) ++ct;
	return ct;
}

