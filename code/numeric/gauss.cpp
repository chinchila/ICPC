// O(n^3)
// return determinant
// a will be inverted
// b will return x
const double EPS = 1e-10;

double Gauss( vector<vector<double> > &a, vector<vector<double> > &b ) {
	const int n = a.size();
	const int m = b[0].size();
	vector<int> irow( n ), icol( n ), ipiv( n );
	double det = 1;

	for( int i = 0 ; i < n ; ++i ) {
		int pj = -1, pk = -1;
		for( int j = 0 ; j < n ; ++j ) if( !ipiv[j] )
			for( int k = 0 ; k < n ; ++k ) if( !ipiv[k] )
				if( pj == -1 || fabs( a[j][k] ) > fabs( a[pj][pk] ) ) { pj = j; pk = k; }
		if( fabs( a[pj][pk] ) < EPS ) { /* Error matrix is singular. */ }
		++ipiv[pk];
		swap( a[pj], a[pk] );
		swap( b[pj], b[pk] );
		if( pj != pk ) det *= -1;
		irow[i] = pj;
		icol[i] = pk;
		double c = 1.0 / a[pk][pk];
		det *= a[pk][pk];
		a[pk][pk] = 1.0;
		for( int p = 0 ; p < n ; ++p ) a[pk][p] *= c;
		for( int p = 0 ; p < m ; ++p ) b[pk][p] *= c;
		for( int p = 0 ; p < n ; ++p ) if( p != pk ) {
			c = a[p][pk];
			a[p][pk] = 0;
			for( int q = 0 ; q < n ; ++q ) a[p][q] -= a[pk][q] * c;
			for( int q = 0 ; q < m ; ++q ) b[p][q] -= b[pk][q] * c;
		}
	}

	for( int p = n - 1 ; p >= 0 ; --p ) if( irow[p] != icol[p] )
		for( int k = 0 ; k < n ; ++k ) swap( a[k][irow[p]], a[k][icol[p]] );
	return det;
}


/////////implementation with basis and rank//////////////////
// sols = gauss(A, b)
// rank = basis.size()-1
// b = sols[0]
// basis = sols[1:]
template <class T> int row_reduce(vector<vector<T>>& a, int lim = 1e9) {
	int n = a.size(), m = a[0].size(), rank = 0;
	for (int j = 0; j < min(m, lim); ++j) {
		for (int i = rank + 1; i < n; ++i) if (!(a[i][j] == 0)) {
			swap(a[rank], a[i]);
			break;
		}
		if (a[rank][j] == 0) continue;
		T inv = 1 / a[rank][j];
		for (auto&& e : a[rank]) e *= inv;
		for (int i = 0; i < n; ++i) if (i != rank and !(a[i][j] == 0))
			for (int k = m; k-- > j; ) a[i][k] -= a[rank][k] * a[i][j];
		if (++rank == n) break;
	}
	return rank;
}

template <class T>
vector<vector<T>> gauss(vector<vector<T>> a, vector<T> b) {
	int n = a.size(), m = a[0].size();
	for (int i = 0; i < n; ++i) a[i].push_back(b[i]);
	int rank = row_reduce(a, m);
	for (int i = rank; i < n; ++i) if (!(a[i][m] == 0)) return {};
	vector<vector<T>> res(1, vector<T>(m));
	vector<int> pivot(m, -1);
	for (int i = 0, j = 0; i < rank; ++i) {
		while (a[i][j] == 0) ++j;
		res[0][j] = a[i][m], pivot[j] = i;
	}
	for (int j = 0; j < m; ++j) if (pivot[j] == -1) {
		vector<T> x(m);
		x[j] = -1;
		for (int k = 0; k < j; ++k) if (pivot[k] != -1) x[k] = a[pivot[k]][j];
		res.push_back(x);
	}
	return res;
}
/////////////////end///////////////////

// Gauss with bitset (mod 2) 32 times faster
// m = # of equations
// n = # of variables
// vector b is the last on a
// example a[0][0] = 0, a[0][1] = 1, a[0][n] = 0:
// |a  |b
// |0 1|0
bool gauss( vector<bitset<N> > a, bitset<N> &ans, int n ) {
	int m = a.size(), c = 0;
	bitset<N> where; where.set();
	for( int j = n-1, i ; j >= 0 ; --j ) {
		for( i = c; i < m ; ++i )
			if( a[i][j] ) break;
		if( i == m ) continue;
		swap( a[c], a[i] );
		i = c++; where[j] = 0;
		for( int k = 0 ; k < m ; ++k )
			if( a[k][j] && k != i )
				a[k] ^= a[i];
	}
	ans = where;
	for( int i = 0 ; i < m ; ++i ){
		int ac = 0;
		for( int j = 0 ; j < n ; ++j ){
			if( !a[i][j] ) continue;
			if( !where[j] ) where[j] = 1, ans[j] = ac^a[i][n];
			ac ^= ans[j];
		}
		if( ac != a[i][n] ) return false;
	}
	return true;
}
