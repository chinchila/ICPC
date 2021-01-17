// trans = transition
struct trans {
	int m, to[MAXN], match[MAXN];
	trans(int _m = -1) : m(_m) {}
};

trans operator +(trans a, trans b) {
	if (b.m < 0) return a;
	if (a.m < 0) return b;
	trans c(a.m);
	for(int i = 0; i < c.m; i++) {
		c.to[i] = b.to[a.to[i]];
		c.match[i] = (a.match[i] + b.match[a.to[i]])%MOD;
	}
	return c;
}

struct KMP {
	string P;
	int b[MAXN], m;
	void build(string &_P) {
		P = _P;
		m = P.size();
		memset(&b, -1, sizeof b);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			b[++i] = ++j;
		}
	}
	trans get(char c) {
		trans ans(m);
		for(int i = 0, j, cnt; i < m; i++) {
			j = i; cnt = 0;
			while(j >= 0 && c != P[j]) j = b[j];
			j++;
			if (j == m) cnt++, j = b[j];
			ans.to[i] = j;
			ans.match[i] = cnt;
		}
		return ans;
	}
};
