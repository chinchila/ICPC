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
