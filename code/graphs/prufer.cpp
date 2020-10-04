// the number of labeled trees is n^{n-2}.
// O(n)

int n;
vector<int> adj[MAXN];

void addEdge(int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}


vector<int> treeToCode() {
	vector<int> deg(n), parent(n, -1), code;
	function<void(int)> dfs = [&](int u) {
		deg[u] = adj[u].size();
		for (int v: adj[u]) {
			if (v != parent[u]) {
				parent[v] = u;
				dfs(v);
			}
		}
	};
	dfs(n-1);

	int index = -1;
	while (deg[++index] != 1);
	for (int u = index, i = 0; i < n-2; ++i) {
		int v = parent[u];
		code.push_back(v);
		if (--deg[v] == 1 && v < index) {
			u = v;
		} else {
			while (deg[++index] != 1);
			u = index;
		}
	}
	return code;
}

void codeToTree(vector<int> code) {
	int n = code.size() + 2;
	vector<int> deg(n, 1);
	for (int i = 0; i < n-2; ++i)
		++deg[code[i]];

	int index = -1;
	while (deg[++index] != 1);
	for (int u = index, i = 0; i < n-2; ++i) {
		int v = code[i];
		addEdge(u, v);
		--deg[u]; --deg[v];
		if (deg[v] == 1 && v < index) {
			u = v;
		} else {
			while (deg[++index] != 1);
			u = index;
		}
	}
	for (int u = 0; u < n-1; ++u) 
		if (deg[u] == 1)
			addEdge(u, n-1);
}

