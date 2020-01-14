// usage, cin >> s; foreach i -> len(s) : insert(i)
// lps = longest palindromic substring
// num = number of palindromes in substring
// ptr-2 = number of different palindromic substrings
struct Node {
	int start, end;
	int len;
	int num;
	// change to map if both cases (watch for TLE)
	int next[27];
	int link;
};

Node tree[MAXN];
int currNode;
int lps;
string s;
int ptr;

void insert(int idx) {
	int tmp = currNode;
	int let = s[idx] - 'a';// Watch!!
	while(!(idx - tree[tmp].len >= 1 && s[idx] == s[idx-tree[tmp].len-1]))
		tmp = tree[tmp].link;
	if(tree[tmp].next[let] != 0) {
		currNode = tree[tmp].next[let];
		return;
	}
	ptr++;
	tree[tmp].next[let] = ptr;
	tree[ptr].len = tree[tmp].len + 2;
	tree[ptr].end = idx;
	tree[ptr].start = idx - tree[ptr].len + 1;
	tmp = tree[tmp].link;
	currNode = ptr;
	lps = max( lps, tree[ptr].len );
	if(tree[currNode].len == 1) {
		tree[currNode].link = 2;
		tree[currNode].num = 1;
		return;
	}
	while(!(idx-tree[tmp].len >= 1 && s[idx] == s[idx-tree[tmp].len-1]))
		tmp = tree[tmp].link;
	tree[currNode].link = tree[tmp].next[let];
	tree[currNode].num = 1 + tree[tree[currNode].link].num;
}

void init() {
	tree[1].len = -1;
	tree[1].link = tree[2].link = 1;
	tree[2].len = 0;
	ptr = 2, currNode = 1;
}
