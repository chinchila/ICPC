// Euler circuit for directed graphs O(n+m)
// example output 0 -> 1 -> 2 ... -> 0
// index 0
vector<int> circuit( vector<vector<int> > adj ){
	unordered_map<int,int> edge_count;
	for( int i = 0 ; i < adj.size() ; ++i ){
		edge_count[i] = adj[i].size();
	}
	if( !adj.size() ) return;
	stack<int> curr_path;
	vector<int> circuit;
	curr_path.push( 0 );
	int curr_v = 0;
	while( !curr_path.empty() ){
		if( edge_count[curr_v] ){
			curr_path.push(curr_v);
			int next_v = adj[curr_v].back();
			edge_count[curr_v]--;
			adj[curr_v].pop_back();
			curr_v = next_v;
		} else {
			circuit.push_back(curr_v);
			curr_v = curr_path.top();
			curr_path.pop();
		}
	}
	reverse(circuit.begin(), circuit.end());
	return circuit;
}

