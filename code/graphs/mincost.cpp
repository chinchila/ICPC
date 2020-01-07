/* Minimum-Cost, Maximum-Flow solver using Successive Shortest Paths with Dijkstra and SPFA-SLF.
 * Requirements:
 *   - No duplicate or antiparallel edges with different costs.
 *   - No negative cycles.
 * Time Complexity: O(Ef lg V) average-case, O(VE + Ef lg V) worst-case.
 */
#define INF 0x3f3f3f3f3f3f3f3f
template<int V, class T=long long>
class mcmf {
	unordered_map<int, T> cap[V], cost[V];
	T dist[V];
	int pre[V];
	bool visited[V];
	void spfa(int s) {
		static list<int> q;
		memset(pre, -1, sizeof pre);
		fill(dist, dist+V, INF);
		memset(visited, 0, sizeof visited);
		dist[s] = 0;
		q.push_back(s);
		while (!q.empty()) {
			int v = q.front();
			q.pop_front();
			visited[v] = false;
			for (auto p : cap[v]) if (p.second) {
				int u = p.first;
				T d = dist[v] + cost[v][u];
				if (d < dist[u]) {
					dist[u] = d, pre[u] = v;
					if (!visited[u]) {
						if (q.size() && d < dist[q.front()]) q.push_front(u);
						else q.push_back(u);
						visited[u] = true;
					}
				}
			}
		}
	}
	void dijkstra(int s) {
		static priority_queue<pair<T, int>, vector<pair<T, int> >,
				greater<pair<T, int> > > pq;
		memset(pre, -1, sizeof pre);
		fill(dist, dist+V, INF);
		memset(visited, 0, sizeof visited);
		dist[s] = 0;
		pq.push({0, s});
		while (!pq.empty()) {
			int v = pq.top().second;
			pq.pop();
			if (visited[v]) continue;
			visited[v] = true;
			for (auto p : cap[v]) if (p.second) {
				int u = p.first;
				T d = dist[v] + cost[v][u];
				if (d < dist[u]) {
					dist[u] = d, pre[u] = v;
					pq.push({d, u});
				}
			}
		}
	}
	void reweight() {
		for (int v = 0; v < V; v++) {
			for (auto& p : cost[v]) {
				p.second += dist[v] - dist[p.first];
			}
		}
	}
public:
	unordered_map<int, T> flows[V];
	void add(int u, int v, T f=1, T c=0) {
		cap[u][v] += f;
		cost[u][v] = c;
		cost[v][u] = -c;
	}
	pair<T, T> calc(int s, int t) {
		spfa(s);
		T totalflow = 0, totalcost = 0;
		T fcost = dist[t];
		while (true) {
			reweight();
			dijkstra(s);
			if (~pre[t]) {
				fcost += dist[t];
				T flow = cap[pre[t]][t];
				for (int v = t; ~pre[v]; v = pre[v])
					flow = min(flow, cap[pre[v]][v]);
				for (int v = t; ~pre[v]; v = pre[v]) {
					cap[pre[v]][v] -= flow;
					cap[v][pre[v]] += flow;
					flows[pre[v]][v] += flow;
					flows[v][pre[v]] -= flow;
				}
				totalflow += flow;
				totalcost += flow * fcost;
			}
			else break;
		}
		return { totalflow, totalcost };
	}
	void clear() {
		for (int i = 0; i < V; i++) {
			cap[i].clear();
			cost[i].clear();
			flows[i].clear();
			dist[i] = pre[i] = visited[i] = 0;
		}
	}
};

