// This gives a path that each edge is visited only one time | adj[i].second is the edge id
// It has an euler cycle iff all vertex are even | O(n+m)
int N, M;
vector<pair<int, int> > adj[MAXN];
int cur[MAXN];
bool used[MAXM];
vector<int> tour;

void dfs( int n ) {
	while( cur[n] != adj[n].size() ) {
		if( used[adj[n][cur[n]].second] ) {
			++cur[n];
			continue;
		}
		auto p = adj[n][cur[n]++];
		used[p.second] = true;
		dfs( p.first );
	}
	tour.push_back( n );
}
