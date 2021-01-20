// Aho Corasick automaton O(N + sum(|S|))
// m is the number of states in automaton
// search function gives matches WITH overlap
#define ll long long
#define ALFA 26
#define OFF 'a'
#define MAXN 100013
#define MAXM 100013
int mm; // size of dictionary
string dict[MAXN];

int g[MAXM][ALFA]; // the normal edges in the trie
int f[MAXM]; // failure function
ll out[MAXM]; // output function

int aho_corasick() {
	memset( g, -1, sizeof g );
	memset( out, 0, sizeof out );
	int nodes = 1;
	for( int i = 0 ; i < mm ; ++i ) {
		string& s = dict[i];
		int cur = 0;
		for( int j = 0; j < s.size(); ++j ) {
			int c = s[j] - OFF;
			if (g[cur][c] == -1) g[cur][c] = nodes++;
			cur = g[cur][c];
		}
		++out[cur];
	}
	for( int ch = 0 ; ch < ALFA ; ++ch ) if( g[0][ch] == -1 ) g[0][ch] = 0;
	memset( f, -1, sizeof f );
	queue<int> q;
	for( int ch = 0 ; ch < ALFA ; ++ch ) {
		if( g[0][ch] != 0 ) {
			f[g[0][ch]] = 0;
			q.push( g[0][ch] );
		}
	}
	while( !q.empty() ) {
		int state = q.front();
		q.pop();
		for( int ch = 0 ; ch < ALFA ; ++ch ) {
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

ll search(string &text) {
	int state = 0;
	ll ret = 0;
	for( char c : text ) {
		c -= OFF;
		while( g[state][c] == -1 ) state = f[state];
		state = g[state][c];
		ret += out[state];
	}
	return ret;
}


// implementation from UFMG
// usage: for i -> len(strs): aho::insert(str[i]);
// aho::build();
// aho::query(s); // this will give matches WITHOUT overlap
namespace aho {
	map<char, int> to[MAX];
	int link[MAX], idx, term[MAX], exit[MAX];
	void insert(string& s) {
		int at = 0;
		for (char c : s) {
			auto it = to[at].find(c);
			if (it == to[at].end()) at = to[at][c] = ++idx;
			else at = it->second;
		}
		term[at] = 1;
	}
	void build() {
		queue<int> q;
		q.push(0);
		link[0] = exit[0] = -1;
		while (q.size()) {
			int i = q.front(); q.pop();
			for (auto cj : to[i]) {
				char c = cj.first;
				int j = cj.second;
				int l = link[i];
				while (l != -1 and !to[l].count(c)) l = link[l];
				link[j] = l == -1 ? 0 : to[l][c];
				exit[j] = term[link[j]] ? link[j] : exit[link[j]];
				q.push(j);
			}
		}
	}
	void clear(){
		for( int i = 0 ; i <= idx ; ++i ) {
			link[i] = exit[i] = term[i] = 0;
			to[i].clear();
		}
		idx = 0;
	}
	int query(string &ass) {
		int at = 0, ans = 0;
		for( char c : ass ){
			while (at and !to[at].count(c)) at = link[at];
			at = to[at][c];
			if (term[at] or exit[at]+1) ans++, at = 0;
		}
		return ans;
	}
}