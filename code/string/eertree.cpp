// usage:
// cin >> s; errtree tr(s); foreach i -> len(s) : tr.insert(i)
// lps = longest palindromic substring
// cnt = number of occurrences (run occurrences() before using)
// sum(num) = number of different palindromes that can be created
// concatenating other palindromic substrings example:
// * malayalam = m + ala + y + ala + m
// * malayalam = m + a + l + aya + l + a + m
// ptr-2 = number of different palindromic substrings
#define ALFA 26
struct Node {
	int start, end;
	int len, cnt, num;
	int nxt[ALFA];
	vector<int> edges;
	int sufflink;
};

int ptr;
Node tree[MAX];

struct eertree{
	int suff;
	string s;
	int rootEven, rootOdd;

	bool insert(int pos) {
		int curr = suff, curr_len = 0;
		int letter = s[pos]-'a';// Watch!!
		while (true) {
			curr_len = tree[curr].len;
			if (pos - 1 - curr_len > -1 && s[pos - 1 - curr_len] == s[pos])
				break;
			curr = tree[curr].sufflink;
		}
		if (tree[curr].nxt[letter]) {
			suff = tree[curr].nxt[letter];
			tree[suff].cnt++;
			return false;
		}
		suff = ++ptr;
		tree[ptr].len = tree[curr].len + 2;
		tree[ptr].end = pos;
		tree[ptr].start = pos-tree[ptr].len+1;
		tree[ptr].cnt = 1;
		tree[curr].nxt[letter] = ptr;

		if (tree[ptr].len == 1) {
			tree[ptr].sufflink = rootEven;
			tree[ptr].num = 1;
			tree[rootEven].edges.push_back(ptr);
			return true;
		}
		while (true) {
			curr = tree[curr].sufflink;
			curr_len = tree[curr].len;
			if (pos - 1 - curr_len > -1 && s[pos - 1 - curr_len] == s[pos]) {
				tree[ptr].sufflink = tree[curr].nxt[letter];
				tree[tree[curr].nxt[letter]].edges.push_back(ptr);
				break;
			}
		}
		tree[ptr].num = 1 + tree[tree[ptr].sufflink].num;
		return true;
	}
	eertree(){}
	eertree(string st) {
		rootOdd = ++ptr, rootEven = ++ptr;
		tree[rootOdd].len = -1;
		tree[rootOdd].sufflink = tree[rootEven].sufflink = rootOdd;
		tree[rootEven].len = 0;
		suff = rootEven;
		tree[rootOdd].edges.push_back(rootEven);
		s = st;
	}
	void clearNode( int i ){
		tree[i].start = tree[i].end = 0;
		tree[i].len = tree[i].cnt = 0;
		tree[i].num = tree[i].sufflink = tree[i].marked = 0;
		tree[i].edges.clear();
		memset(tree[i].nxt, 0, sizeof tree[i].nxt);
	}
	void occurrences(){
		occurrences(rootOdd);
	}
	void occurrences(int node) {
		for (int i : tree[node].edges) {
			occurrences(i);
			tree[node].cnt += tree[i].cnt;
		}
	}
};


// Longest common palindromic substring
// n = number of strings
// ans = answer
// pt[i] = palindromic tree of word i
// on main
// dfs(odd roots)
// dfs(even roots)
int n, ans;
eertree pt[N];

void dfs(vector<int> &u) {
	if (tree[u[0]].len > ans) ans = tree[u[0]].len;
	vector<int> v(n);
	for(char c = 0; c < ALFA; c++) {
		bool ok = true;
		for(int i = 0; i < n && ok; i++) {
			v[i] = tree[u[i]].nxt[c];
			if (!tree[u[i]].nxt[c]) ok = false;
		}
		if (!ok) continue;
		dfs(v);
	}
}
