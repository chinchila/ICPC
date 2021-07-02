// Edmond's Blossom (general graph matching) O(VE) / pass MAX_N into constructor
#define INV_PAIR { -1, -1 }
struct Bloss {
	vector<vector<int> > adj;
	vector<int> pairs, fst, que;
	vector<pair<int, int> > lbl;
	int head, tail;

	Bloss( int n ) : adj( n ), pairs( n + 1, n ), fst( n + 1, n ), que( n ), lbl( n + 1, INV_PAIR ) {}

	void add( int u, int v ) {
		adj[u].push_back( v ), adj[v].push_back( u );
	}
	void rem( int v, int w ) {
		int t = pairs[v]; pairs[v] = w;
		if( pairs[t] != v ) return;
		if( lbl[v].second == -1 )
			pairs[t] = lbl[v].first, rem( pairs[t], t );
		else
			rem( lbl[v].first, lbl[v].second ), rem( lbl[v].second, lbl[v].first );
	}

	int find( int u ) {
		return lbl[fst[u]].first < 0 ? fst[u] : fst[u] = find( fst[u] );
	}

	void rel( int x, int y ) {
		int r = find( x );
		int s = find( y );
		if( r == s ) return;
		auto h = lbl[r] = lbl[s] = { ~x, y };
		int join;
		while( true ) {
			if( s != adj.size() ) swap( r, s );
			r = find( lbl[pairs[r]].first );
			if( lbl[r] == h ) {
				join = r; break;
			}
			else lbl[r] = h;
		}
		for( int v : { fst[x], fst[y] } ) {
			for( ; v != join ; v = fst[lbl[pairs[v]].first] ) {
				lbl[v] = { x, y };
				fst[v] = join;
				que[tail++] = v;
			}
		}
	}

	bool aug( int u ) {
		lbl[u] = { adj.size(), -1 };
		fst[u] = adj.size();
		head = tail = 0;
		for( que[tail++] = u ; head < tail ; ) {
			int x = que[head++];
			for( int y : adj[x] ) {
				if( pairs[y] == adj.size() && y != u ) {
					pairs[y] = x;
					rem( x, y );
					return true;
				}
				else if( lbl[y].first >= 0 ) rel( x, y );
				else if( lbl[pairs[y]].first == -1 ) {
					lbl[pairs[y]].first = x;
					fst[pairs[y]] = y;
					que[tail++] = pairs[y];
				}
			}
		}
		return false;
	}

	int match() {
		int ans = head = tail = 0;
		for( int u = 0 ; u < adj.size() ; ++u ) {
			if( pairs[u] < adj.size() || !aug( u ) ) continue;
			++ans;
			for( int i = 0 ; i < tail ; ++i )
				lbl[que[i]] = lbl[pairs[que[i]]] = INV_PAIR;
			lbl[adj.size()] = INV_PAIR;
		}
		return ans;
	}
	// só mudar idx=1 se o grafo for indexado em 1
	// precisa rodar o match antes :)
	vector<pair<int, int> > result(int idx=0){
		int n = adj.size();
		vector<pair<int, int> > result;
		for( int i = idx ; i < n+idx ; ++i)
			if(i > pairs[i])
				result.push_back({pairs[i], i});
		return result;
	}
};

