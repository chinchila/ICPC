// Shortest path faster algorithm avg O(E), worst case O(VE)
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
vector<ll> spfa( int start, int n, vector<pair<int, int> > *adj ) {
	vector<ll> dist( n+5, INF );
	vector<int> pre( n+5, -1 );
	bool inQueue[MAX_N]={};
	dist[start] = 0;
	list<int> q;
	q.push_back( start );
	inQueue[start] = 1;
	while( !q.empty() ) {
		int v = q.front();
		q.pop_front();
		inQueue[v] = 0;
		for( auto p : adj[v] ) {
			int u = p.first;
			ll d = dist[v] + p.second;
			if( d < dist[u] ) {
				dist[u] = d, pre[u] = v;
				if( !inQueue[u] ) {
					if (q.size() && d < dist[q.front()]) q.push_front(u);
					else q.push_back(u);
					inQueue[u] = 1;
				}
			}
		}
	}
	return dist;
}
