// It is a data structure that admits the following operations:
//	add_edge(s, t): insert edge (s,t) to the network if
//									it does not make a cycle
// is_reachable(s, t): return true iff there is a path s --> t
// amortized O(n) per update

struct dag_reachability {
	int n;
	vector<vector<int>> parent;
	vector<vector<vector<int>>> child;
	dag_reachability(int n) : n(n), parent(n, vector<int>(n, -1)),
		child(n, vector<vector<int>>(n)) { }
	bool is_reachable(int src, int dst) {
		return src == dst || parent[src][dst] >= 0;
	}
	bool add_edge(int src, int dst) {
		if (is_reachable(dst, src)) return false; // break DAG condition
		if (is_reachable(src, dst)) return true; // no-modification performed
		for (int p = 0; p < n; ++p) 
			if (is_reachable(p, src) && !is_reachable(p, dst)) 
				meld(p, dst, src, dst);
		return true;
	}
	void meld(int root, int sub, int u, int v) {
		parent[root][v] = u;
		child[root][u].push_back(v);
		for (int c: child[sub][v]) 
			if (!is_reachable(root, c)) 
				meld(root, sub, v, c);
	}
};

