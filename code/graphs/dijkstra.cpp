// Shortest path from start to any other vertex O( (V + E) * log(E) )
// Doesnt work with negative weights (use SPFA)
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
vector<ll> dk( int start, int n, vector<pair<int, ll> > *adj ) {
	vector<ll> dist( n + 5, INF );
	priority_queue<pair<ll, int> > q;
	q.push( { dist[start] = 0, start } );
	while( !q.empty() ) {
		int u = q.top().second;
		ll d = -q.top().first; q.pop();
		if( d > dist[u] ) continue;
		for( pair<int, ll> pv : adj[u] ) {
			int v = pv.first, w = pv.second;
			if( dist[u] + w < dist[v] )
				q.push( { -( dist[v] = dist[u] + w ), v } );
		}
	}
	return dist;
}
