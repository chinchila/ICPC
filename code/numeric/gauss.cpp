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

// Implementation from cp-algorithms
// works with modulus (maybe the first works too)
int gauss(vector <vector<num> > a, vector<num> &ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    vector<int> where(m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (a[i][col] > a[sel][col])
                sel = i;
        if(a[sel][col] == 0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
        for (int i=0; i<n; ++i)
            if (i != row) {
                num c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }
    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m]/a[where[i]][i];
    for (int i=0; i<n; ++i) {
        num sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (sum - a[i][m] > 0)
            return 0;
    }
    return 1;
}