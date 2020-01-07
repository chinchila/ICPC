// index 1 | build: O(n^2 * log^2(n)) | query & updt: O(log^2(n))
// 3d sum query: do ( 2d with kmax ) - ( 2d with kmin )
int bit[MAXN][MAXN];

void update(int i, int j, int v) {
	for (; i < N; i+=i&-i)
		for (int jj = j; jj < N; jj+=jj&-jj)
			bit[i][jj] += v;
}

int query(int i, int j) {
	int res = 0;
	for (; i; i-=i&-i)
		for (int jj = j; jj; jj-=jj&-jj)
			res += bit[i][jj];
	return res;
}

int query(int imin, int jmin, int imax, int jmax) {
	return query(imax, jmax) - query(imax, jmin-1) - query(imin-1, jmax) + query(imin-1, jmin-1);
}
