// If you need memory otimization, please consider using pointers
// O(sum(|s|))
int nds = 0;
int g[MAXN][26];

void add( string s ){
	int cur = 0;
	for( char ch : s ) {
		ch -= 'a';
		if( g[cur][ch] == 0 ) g[cur][ch] = ++nds;
		cur = g[cur][ch];
	}
}

bool find( string s ) {
	int cur = 0;
	for( char ch : s ) {
		ch -= 'a';
		if( g[cur][ch] == 0 ) return false;
		cur = g[cur][ch];
	}
	return true;
}

// Bolada
struct Node {
	map<char, int> child;
	bool end;
	int getchild( char c ) {
		auto it = child.find( c );
		if( it != child.end() ) return it->second;
		return -1;
	}
};

vector<Node> trie(1);

void add( string s ) {
	int cur = 0;
	for( char c : s ) {
		if( trie[cur].getchild(c) == -1 ) {
			trie.push_back( Node() );
			trie[cur].child[c] = trie.size()-1;
		}
		cur = trie[cur].getchild(c);
	}
	trie[cur].end = true;
}

bool find( string s ) {
	int cur = 0;
	for( char c : s ) {
		if( trie[cur].getchild(c) == -1 ) return 0;
		cur = trie[cur].getchild(c);
	}
	return trie[cur].end;
}

