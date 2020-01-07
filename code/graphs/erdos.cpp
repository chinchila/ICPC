//   Erdos-Gallai theorem states that a sequence 
//   d = [d_1, ..., d_n] is a degree sequence of some
//   simple graph if and only if it satisfies
//     1. d_1+...+d_n is even,
//   and
//     2. d_1+...+d_k <= k(k-1)+min(k,d_k+1)+...+min(k, d_n).
//   for all k = 1, ..., n.

bool is_graphic(vector<int> d) {
	int n = d.size();
	sort(d.begin(), d.end(), greater<int>());
	vector<int> s(n+1);
	for (int i = 0; i < n; ++i) s[i+1] = s[i] + d[i];
	if (s[n] % 2) return false;
	for (int k = 1; k <= n; ++k) {
		int p = distance(d.begin(), lower_bound(d.begin()+k, d.end(), k, greater<int>()));
		if (s[k] > k * (p-1) + s[n] - s[p]) return false;
	}
	return true;
}
