// Suffix Automaton Construction - O(n) FROM IME
// Suffix automaton = compressed form of all substrings
// len[i] = length of the longest string in the state i
// sl[i] = suffix link of state i
// sz = # of states
// sum[i] = # of distinct substrings of i-th prefix of string
// dp[i] = # number of paths that end on state i
const int N = 1e6+1, K = 26;
int sl[2*N], len[2*N], sz, last;
ll cnt[2*N];
map<int, int> adj[2*N];
//ll dp[2*N];
//ll sum[N];

void add(int c) {
	int u = sz++;
	len[u] = len[last] + 1;
	cnt[u] = 1;
	int p = last;
	while(p != -1 and !adj[p][c])
		 adj[p][c] = u, p = sl[p];
		 //dp[u] += dp[p]
	if (p == -1) sl[u] = 0;
	else {
		int q = adj[p][c];
		if (len[p] + 1 == len[q]) sl[u] = q;
		else {
			int r = sz++;
			len[r] = len[p] + 1;
			sl[r] = sl[q];
			adj[r] = adj[q];
			while(p != -1 and adj[p][c] == q)
				adj[p][c] = r, p = sl[p];
				//dp[q] -= dp[p], dp[r] += dp[p]
			sl[q] = sl[u] = r;
		}
	}
	last = u;
}

void clear() {
	for(int i=0; i<=sz; ++i) adj[i].clear();
	last = 0;
	sz = 1;
	sl[0] = -1;
	//dp[0] = 1;
}

void build(char *s) {
	clear();
	for(int i=0; s[i]; ++i) add(s[i]); //sum[i+1] = sum[i] + dp[last]
}

// terminal state = where end up on a suffix
// to get terminals use the following
vector<int> terminals;
terminals.push_back(0);
int p = last;
while(p>0) terminals.push_back( p ), p = sl[p];

// Pattern matching - O(|p|)
bool check(char *p) {
	int u = 0, ok = 1;
	for(int i=0; p[i]; ++i) {
		u = adj[u][p[i]];
		if (!u) ok = 0;
	}
	return ok;
}

// Substring count - O(|p|)
// uncomment to calculate length
// of all distinct substrings
// concatenated
ll d[2*N];

void substr_cnt(int u) {
	d[u] = 1;
	for(auto p : adj[u]) {
		int v = p.second;
		if (!d[v]) substr_cnt(v);
		d[u] += d[v];
		//sum[u] += d[v] + sum[v];
	}
}

ll substr_cnt() {
	memset(d, 0, sizeof d);
	substr_cnt(0);
	return d[0] - 1;
}

// k-th Substring - O(|s|)
// Just find the k-th path in the automaton.
// first compute all terminals
// where terminal[i] = true if i is terminal
// then run this code

ll oc[2*N], sum[2*N];

void dfs(int u) {
	oc[u] += terminal[u];
	word[u] += terminal[u];
	for(auto p : adj[u]) {
		int v = p.second;
		if(!oc[v]) dfs(v);
		oc[u] += oc[v];
		word[u] += oc[v] + word[v];
	}
}

void kth(ll cur, ll k, string &ans, int u) {
	if(cur >= k) return;
	for(auto it : adj[u]) {
		if(cur + word[it.second] >= k){
			cur += oc[it.second];
			ans += it.first;
			kth(cur, k, ans, it.second);
			return;
		}
		else
			cur += word[it.second];
	}
	// If it reaches here, k > # of different substrings
	ans = "No such line.";
}


// Smallest cyclic shift - O(|s|)
// Build the automaton for string s + s. And adapt previous dp
// to only count paths with size |s|.


// Number of occurences - O(|p|)
vector<int> t[2*N];

// This count the occurrences of each state
// to find the number of occurences of substrings
// use cnt[i]*(len[i] - len[sl[i]])
void occur_count(int u) {
	for(int v : t[u]) occur_count(v), cnt[u] += cnt[v];
}

void build_tree() {
	for(int i=1; i<=sz; ++i)
		t[sl[i]].push_back(i);
	occur_count(0);
}

ll occur_count(char *p) {
	// Call build tree once per automaton
	int u = 0;
	for(int i=0; p[i]; ++i) {
		u = adj[u][p[i]];
		if (!u) break;
	}
	return !u ? 0 : cnt[u];
}

// First occurence - (|p|)
// Store the first position of occurence fp.
// Add the the code to add function:
// fp[u] = len[u] - 1;
// fp[r] = fp[q];

// To answer a query, just output fp[u] - strlen(p) + 1
// where u is the state corresponding to string p

// All occurences - O(|p| + |ans|)
// All the occurences can reach the first occurence via suffix links.
// So every state that contains a occurence is reacheable by the 
// first occurence state in the suffix link tree. Just do a DFS in this
// tree, starting from the first occurence.
// OBS: cloned nodes will output same answer twice.


// Smallest substring not contained in the string - O(|s| * K)
// Just do a dynamic programming:
// d[u] = 1 // if d does not have 1 transition
// d[u] = 1 + min d[v] // otherwise


// LCS of 2 Strings - O(|s| + |t|)
string LCS(string& S, string& T) {
	build(S);
	int at = 0, l = 0, ans = 0, pos = -1;
	for (int i = 0; i < T.size(); i++) {
		while (at and !adj[at].count(T[i])) at = sl[at], l = len[at];
		if (adj[at].count(T[i])) at = adj[at][T[i]], l++;
		else at = 0, l = 0;
		if (l > ans) ans = l, pos = i;
	}
	return T.substr(pos-ans+1, ans);
}

// LCS of n Strings - O(n*|s|*K)
void LCS(int caso, char *t){
    int state_num=0,match=0;
    for(int i=0;t[i];i++){
    while(state_num && !adj[state_num][t[i]-'a']) {
      state_num=sl[state_num];
      match=len[state_num];
    }
    if(adj[state_num][t[i]-'a']){
      state_num=adj[state_num][t[i]-'a'];
      match++;
    }
    dp[caso][state_num]=max(dp[caso][state_num],match);
    }
    for(int state=sz-1;state>=0;state--){
        if(dp[caso][state]){
            while(state){
                state=sl[state];
                dp[caso][state] = len[state];
            }
        }
    }
}
// on main:
int res=0;
for(int state=1;state<sz;state++){
	int temp = dp[0][state];
	for(int i=1;i<n;i++)
		temp = min(temp, dp[i][state]);
	res = max(res, temp);
}