// index 1
// dg[i] = degree of vertex i
// proc[i] = processed vertex on time i
// par[i] = parent of i
// sub[i] = size of subtree of vertex i
// parCycle[i] = closest vertex to i inside cycle
// depth[i] = depth of i or # of edges until parCycle[i]
// cycle[i] = index of cycle closest to i
// ini[i] = first vertex of cycle i
// sz[i] = size of cycle i
// idOnCycle[i] = id of vertex i on cycle
vector<int> proc, g[MAXN];
vector<int> cycles[MAXN];
bool vis[MAXN], onCycle[MAXN];
int par[MAXN], depth[MAXN], sub[MAXN], cycle[MAXN];
int ini[MAXN], sz[MAXN], idOnCycle[MAXN], cycleCount;
int parCycle[MAXN], n, dg[MAXN];

int findParent(int u) {
	for( int v : g[u] ) if( !vis[v] ) return v;
	return -1;
}

void foundCycle(int u){
	int iniv = u;
	int idCycle = ++cycleCount;
	int curId = 0;
	ini[idCycle] = u;
	sz[idCycle] = 0;
	cycles[idCycle].clear();
	while( vis[u] == 0 ) {
		vis[u] = 1;
		par[u] = findParent(u);
		if(par[u] == -1) par[u] = iniv;
		parCycle[u] = u, cycle[u] = idCycle;
		onCycle[u] = 1, idOnCycle[u] = curId;
		cycles[idCycle].push_back(u);
		++sz[idCycle], ++sub[u], depth[u] = 0;
		u = par[u], ++curId;
	}
}

void lenha(){
	queue<int> q;
	for( int i = 1 ;  i<= n ; ++i )
		if(dg[i] == 1 ) q.push(i), vis[i] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		proc.push_back(u);
		int v = findParent(u);
		par[u] = v, ++sub[u];
		sub[v] += sub[u], --dg[v];
		if(dg[v] == 1 ) q.push(v), vis[v] = 1;
	}
	cycleCount = 0;
	for( int i = 1 ;  i<= n ; ++i )
		if(!vis[i]) foundCycle(i);
	for( int i = proc.size() - 1 ; i >= 0 ; --i ) {
		int v = proc[i], pv = par[v];
		parCycle[v] = parCycle[pv];
		cycle[v] = cycle[pv];
		onCycle[v] = 0, idOnCycle[v] = -1;
		depth[v] = depth[pv] + 1;
	}
}

