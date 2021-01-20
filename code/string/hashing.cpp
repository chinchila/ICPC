// Rabin-karp O(n+m)
#define ull unsigned long long
const int B = 31;
char s[MAXN], p[MAXN];

void rabin( string s, string p ) {
	int n = s.length(), m = p.length();
	if( n<m ) return;
	ull hp = 0, hs = 0, E = 1;
	for (int i = 0; i < m; ++i)
		hp = ((hp*B)%MOD + p[i])%MOD,
		hs = ((hs*B)%MOD + s[i])%MOD,
		E = (E*B)%MOD;

	if (hs == hp) { /* matching position 0 */ }
	for( int i = m ; i < n ; ++i ) {
		hs = ((hs*B)%MOD + s[i])%MOD;
		hp = (hs - s[i-m]*E%MOD + MOD)%MOD;
		if( hs == hp ) { /* matching position i-m+1 */ }
	}
}

// Good hashing :) O(n+m)
typedef long long LL;
typedef pair<LL, LL> pll;

const int MOD = 1e9 + 7;
const pll BASE = {4441, 7817};

pll operator+(const pll& a, const pll& b) {
	return { (a.first + b.first) % MOD, (a.second + b.second) % MOD };
}
pll operator+(const pll& a, const LL& b) {
	return { (a.first + b) % MOD, (a.second + b) % MOD };
}
pll operator-(const pll& a, const pll& b) {
	return { (MOD + a.first - b.first) % MOD, (MOD + a.second - b.second) % MOD };
}
pll operator*(const pll& a, const pll& b) {
	return { (a.first * b.first) % MOD, (a.second * b.second) % MOD };
}
pll operator*(const pll& a, const LL& b) {
	return { (a.first * b) % MOD, (a.second * b) % MOD };
}

pll get_hash(string s) {
	pll h = {0, 0};
	for (int i = 0; i < s.size(); i++) {
		h = BASE * h + s[i];
	}
	return h;
}

struct hsh {
	int N;
	string S;
	vector<pll> pre, pp;

	void init(string S_) {
		S = S_;
		N = S.size();
		pp.resize(N);
		pre.resize(N + 1);
		pp[0] = {1, 1};
		for (int i = 0; i < N; i++) {
			pre[i + 1] = pre[i] * BASE + S[i];
			if (i) { pp[i] = pp[i - 1] * BASE; }
		}
	}

	pll get(int s, int e) {
		return pre[e] - pre[s] * pp[e - s];
	}
};

vector<int> search(string s, string p) {
	vector<int> matches;
	pll h = get_hash(p);
	hsh hs; hs.init(s);
	for (int i = 0; i + p.size() <= s.size(); i++) {
		if (hs.get(i, i + p.size()) == h) {
			matches.push_back(i);
		}
	}
	return matches;
}
