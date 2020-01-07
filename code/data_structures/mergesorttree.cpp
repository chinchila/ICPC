// Mergesort Tree - Time <O(nlognlogn), O(nlogn)> - Memory O(nlogn)
// Mergesort Tree is a segment tree that stores the sorted subarray
// on each node. index 1

vector<int> st[4*MAXN];

void build(int p, int l, int r) {
	if( l == r ) { st[p].push_back( s[l] ); return; }
	build(2*p, l, (l+r)/2);
	build(2*p+1, (l+r)/2+1, r);
	st[p].resize(r-l+1);
	merge(st[2*p].begin(), st[2*p].end(),
		st[2*p+1].begin(), st[2*p+1].end(),
		st[p].begin());
}

int query( int p, int l, int r, int i, int j, int a, int b ) {
	if( j < l || i > r ) return 0;
	if( i <= l && j >= r )
		return upper_bound(st[p].begin(), st[p].end(), b) -
				lower_bound(st[p].begin(), st[p].end(), a);
	return query(2*p, l, (l+r)/2, i, j, a, b) +
			query(2*p+1, (l+r)/2+1, r, i, j, a, b);
}
