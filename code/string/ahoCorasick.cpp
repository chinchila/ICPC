// Aho Corasick automaton O(N + sum(|S|)) / m is the number of states in automaton
#define ll long long
#define OFF 'a'
#define MAX_N 100013
int n; // size of dictionary
string dict[MAX_N];
string text;

#define MAX_M 100013
int g[MAX_M][26]; // the normal edges in the trie
int f[MAX_M]; // failure function
ll out[MAX_M]; // output function

int aho_corasick() {
	memset( g, -1, sizeof g );
	memset( out, 0, sizeof out );
	int nodes = 1;
	for( int i = 0 ; i < n ; ++i ) {
		string& s = dict[i];
		int cur = 0;

		for( int j = 0; j < s.size(); ++j ) {
			if (g[cur][s[j] - OFF] == -1) g[cur][s[j] - OFF] = nodes++;
			cur = g[cur][s[j] - OFF];
		}
		++out[cur];
	}

	for( int ch = 0 ; ch < 26 ; ++ch ) if( g[0][ch] == -1 ) g[0][ch] = 0;

	memset( f, -1, sizeof f );
	queue<int> q;
	for( int ch = 0 ; ch < 26 ; ++ch ) {
		if( g[0][ch] != 0 ) {
			f[g[0][ch]] = 0;
			q.push( g[0][ch] );
		}
	}

	while( !q.empty() ) {
		int state = q.front();
		q.pop();

		for( int ch = 0 ; ch < 26 ; ++ch ) {
			if( g[state][ch] == -1 ) continue;

			int fail = f[state];
			while( g[fail][ch] == -1 ) fail = f[fail];

			f[g[state][ch]] = g[fail][ch];
			out[g[state][ch]] += out[g[fail][ch]];

			q.push( g[state][ch] );
		}
	}

	return nodes;
}

ll search() {
	int state = 0;
	ll ret = 0;
	for( char c : text ) {
		while( g[state][c - OFF] == -1 ) state = f[state];
		state = g[state][c - OFF];
		ret += out[state];
	}
	return ret;
}

