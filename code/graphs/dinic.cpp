/* Max flow algorithm
 * Time Complexity:
 *   - O(V^2 E) for general graphs, but in practice ~O(E^1.5)
 *   - O(sqrt(V) * E) for bipartite matching
 *   - O(min(V^(2/3), E^(1/2)) E) for unit capacity graphs
 */
#define ll long long
const ll INF = numeric_limits<ll>::max();
class max_flow {
	struct edge {
		int t;
		unsigned long rev;
		ll cap, f;
	};

	vector<edge> adj[MAXN];
	int dist[MAXN];
	int ptr[MAXN];

	bool bfs( int s, int t ) {
		memset( dist, -1, sizeof dist );
		dist[s] = 0;
		queue<int> q( { s } );
		while( !q.empty() && dist[t] == -1 ) {
			int n = q.front();
			q.pop();
			for( edge& e : adj[n] ) {
				if( dist[e.t] == -1 && e.cap != e.f ) {
					dist[e.t] = dist[n] + 1;
					q.push( e.t );
				}
			}
		}
		return dist[t] != -1;
	}

	ll aug( int n, ll amt, int t ) {
		if( n == t ) return amt;
		for( ; ptr[n] < adj[n].size() ; ++ptr[n] ) {
			edge& e = adj[n][ptr[n]];
			if( dist[e.t] == dist[n] + 1 && e.cap != e.f ) {
				ll flow = aug( e.t, min( amt, e.cap - e.f ), t );
				if( flow != 0 ) {
					e.f += flow;
					adj[e.t][e.rev].f -= flow;
					return flow;
				}
			}
		}
		return 0;
	}

public:
	void add( int u, int v, ll cap=1, ll rcap=0 ) {
		adj[u].push_back({ v, adj[v].size(), cap, 0 });
		adj[v].push_back({ u, adj[u].size() - 1, rcap, 0 });
	}

	ll calc( int s, int t ) {
		ll flow = 0;
		while( bfs( s, t ) ) {
			memset( ptr, 0, sizeof ptr );
			while( ll df = aug( s, INF, t ) ) flow += df;
		}
		return flow;
	}

	void clear() {
		for( int n = 0 ; n < MAXN ; ++n ) adj[n].clear();
	}

	bool inCut( int u ){ return dist[u] != -1; }

	void dfs( int u ) {
		cut[u] = true;
		for( auto &e : adj[u] )
			if( e.cap > e.f && !cut[e.t] ) dfs( e.t );
	}
};

max_flow g;
