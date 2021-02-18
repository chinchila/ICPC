/* Minimum-Cost, Maximum-Flow solver using Successive Shortest Paths with Dijkstra and SPFA-SLF.
 * Requirements:
 *   - No negative cycles.
 * Time Complexity: O(Ef lg V) average-case, O(VE + Ef lg V) worst-case with negative costs.
 */
#define ll long long
const ll INF = numeric_limits<ll>::max()/3;
template<int V, class T=ll>
class mcmf {
	struct edge {
		int t, rev;
		T cap, cost, f;
	};

	vector<edge> adj[V];
	T dist[V];
	int pre[V];
	bool vis[V];

	void spfa(int s) { /* only needed if there are negative costs */
		list<int> q;
		memset(pre, -1, sizeof pre);
		memset(vis, 0, sizeof vis);
		fill(dist, dist + V, INF);
		dist[s] = 0;
		q.push_back(s);
		while (!q.empty()) {
			int v = q.front();
			q.pop_front();
			vis[v] = false;
			for (auto e : adj[v]) if (e.cap != e.f) {
				int u = e.t;
				T d = dist[v] + e.cost;
				if (d < dist[u]) {
					dist[u] = d, pre[u] = e.rev;
					if (!vis[u]) {
						if (q.size() && d < dist[q.front()]) q.push_front(u);
						else q.push_back(u);
						vis[u] = true;
					}
				}
			}
		}
	}

	priority_queue<pair<T, int>, vector<pair<T, int> >,
		greater<pair<T, int> > > pq; /* for dijkstra */

	void dijkstra(int s) {
		memset(pre, -1, sizeof pre);
		memset(vis, 0, sizeof vis);
		fill(dist, dist + V, INF);
		dist[s] = 0;
		pq.emplace(0, s);
		while (!pq.empty()) {
			int v = pq.top().second;
			pq.pop();
			if (vis[v]) continue;
			vis[v] = true;
			for (auto e : adj[v]) if (e.cap != e.f) {
				int u = e.t;
				T d = dist[v] + e.cost;
				if (d < dist[u]) {
					dist[u] = d, pre[u] = e.rev;
					pq.emplace(d, u);
				}
			}
		}
	}

	void reweight() {
		for (int v = 0; v < V; v++)
			for (auto& e : adj[v])
				e.cost += dist[v] - dist[e.t];
	}

public:
	void add(int u, int v, T cap=1, T cost=0) {
		adj[u].push_back({ v, (int) adj[v].size(), cap, cost, 0 });
		adj[v].push_back({ u, (int) adj[u].size() - 1, 0, -cost, 0 });
	}

	pair<T, T> calc(int s, int t, T f=INF) {
		spfa(s); /* comment out if all costs are non-negative */
		T totalflow = 0, totalcost = 0;
		T fcost = dist[t];
		while (true) {
			reweight();
			spfa(s);
			if (~pre[t]) {
				fcost += dist[t];
				T flow = f;
				for (int v = t; ~pre[v]; v = adj[v][pre[v]].t) {
					edge& r = adj[v][pre[v]];
					edge& e = adj[r.t][r.rev];
					flow = min(flow, e.cap - e.f);
				}
				for (int v = t; ~pre[v]; v = adj[v][pre[v]].t) {
					edge& r = adj[v][pre[v]];
					edge& e = adj[r.t][r.rev];
					e.f += flow;
					r.f -= flow;
				}
				totalflow += flow;
				totalcost += flow * fcost;
			}
			else break;
		}
		return { totalflow, totalcost };
	}
	bool inCut( int u ) { return dist[u] != INF; };
	void clear() {
		for (int i = 0; i < V; i++) {
			adj[i].clear();
			dist[i] = pre[i] = vis[i] = 0;
		}
	}
};