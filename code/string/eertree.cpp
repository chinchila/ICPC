// usage, cin >> s; foreach i -> len(s) : insert(i)
// lps = longest palindromic substring
// num = number of palindromes in substring
// ptr-2 = number of different palindromic substrings
#define ALFA 26
struct Node {
	int start, end;
	int len, num;
	int next[ALFA];
	int link;
};

int ptr;
Node tree[MAXN];

struct eertree{
	int currNode;
	string s;
	int rootEven, rootOdd;

	void insert(int idx) {
		int tmp = currNode;
		int let = s[idx] - 'a';// Watch!!
		while(!(idx - tree[tmp].len >= 1 && s[idx] == s[idx-tree[tmp].len-1]))
			tmp = tree[tmp].link;
		if(tree[tmp].next[let] != 0) {
			currNode = tree[tmp].next[let];
			return;
		}
		tree[tmp].next[let] = ++ptr;
		tree[ptr].len = tree[tmp].len + 2;
		tree[ptr].end = idx;
		tree[ptr].start = idx - tree[ptr].len + 1;
		tmp = tree[tmp].link;
		currNode = ptr;
		if(tree[currNode].len == 1) {
			tree[currNode].link = rootEven;
			tree[currNode].num = rootOdd;
			return;
		}
		while(!(idx-tree[tmp].len >= 1 && s[idx] == s[idx-tree[tmp].len-1]))
			tmp = tree[tmp].link;
		tree[currNode].link = tree[tmp].next[let];
		tree[currNode].num = 1 + tree[tree[currNode].link].num;
	}
	eertree(){}
	eertree(string st) {
		rootOdd = ++ptr, rootEven = ++ptr;
		tree[rootOdd].len = -1;
		tree[rootOdd].link = tree[rootEven].link = rootOdd;
		tree[rootEven].len = 0;
		currNode = rootEven;
		s = st;
	}
};

// Longest common palindromic substring
// n = number of strings
// ans = answer
// pt[i] = palindromic tree of word i
//
int n, ans;
eertree pt[N];

void dfs(vector<int> &u) {
	if (tree[u[0]].len > ans) ans = tree[u[0]].len;
	vector<int> v(n);
	for(char c = 0; c < ALFA; c++) {
		bool ok = true;
		for(int i = 0; i < n && ok; i++) {
			v[i] = tree[u[i]].next[c];
			if (!tree[u[i]].next[c]) ok = false;
		}
		if (!ok) continue;
		dfs(v);
	}
}
