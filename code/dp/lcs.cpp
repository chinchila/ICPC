// O(m * n)
// to compute only size use:
int lcs( string &X, string &Y ) {
	int m = X.length(), n = Y.length();
	int L[2][n + 1];
	bool bi;
	for( int i = 0 ; i <= m ; ++i ) {
		bi = i & 1;
		for( int j = 0; j <= n ; ++j ) {
			if (i == 0 || j == 0)  L[bi][j] = 0;
			else if( X[i-1] == Y[j-1] ) L[bi][j] = L[1 - bi][j - 1] + 1;
			else L[bi][j] = max(L[1 - bi][j], L[bi][j - 1]);
		}
	}
	return L[bi][n];
}
//to compute sequence:
typedef vector<int> vi;
typedef vector<vi> vvi;

void backtrack( vvi &dp, vi &res, vi &A, vi &B, int i, int j ) {
	if( !i || !j ) return;
	if( A[i-1] == B[j-1] )
		res.push_back( A[i-1] ), backtrack( dp, res, A, B, i - 1, j - 1 );
	else
		if( dp[i][j-1] >= dp[i-1][j] ) backtrack( dp, res, A, B, i, j - 1 );
		else backtrack( dp, res, A, B, i - 1, j );
}

void backtrackall( vvi &dp, set<vi> &res, vi &A, vi &B, int i, int j ) {
	if( !i || !j ) { res.insert(vi()); return; }
	if( A[i-1] == B[j-1] ) {
		set<vi> tempres;
		backtrackall( dp, tempres, A, B, i - 1, j - 1 );
		for( auto it = tempres.begin() ; it!=tempres.end() ; ++it ) {
			vi temp = *it;
			temp.push_back( A[i-1] );
			res.insert( temp );
		}
	}
	else
	{
		if( dp[i][j-1] >= dp[i-1][j] ) backtrackall( dp, res, A, B, i, j - 1 );
		if( dp[i][j-1] <= dp[i-1][j] ) backtrackall( dp, res, A, B, i - 1, j );
	}
}

vi LCS( vi &A, vi &B ) {
	vvi dp;
	int n = A.size(), m = B.size();
	dp.resize( n + 1 );
	for( int i = 0 ; i <= n ; ++i ) dp[i].resize( m + 1, 0 );
	for( int i = 1 ; i <= n ; ++i )
		for( int j = 1 ; j <= m ; ++j )
			if( A[i-1] == B[j-1] ) dp[i][j] = dp[i-1][j-1]+1;
			else dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
	vi res;
	backtrack( dp, res, A, B, n, m );
	reverse( res.begin(), res.end() );
	return res;
}

set<vi> LCSall( vi &A, vi &B ) {
	vvi dp;
	int n = A.size(), m = B.size();
	dp.resize( n + 1 );
	for( int i = 0 ; i <= n ; ++i ) dp[i].resize(m+1, 0);
	for( int i = 1 ; i <= n ; ++i )
		for(int j = 1 ; j <= m ; ++j )
			if( A[i-1] == B[j-1] ) dp[i][j] = dp[i-1][j-1]+1;
			else dp[i][j] = max( dp[i-1][j], dp[i][j-1] );
	set<vi> res;
	backtrackall( dp, res, A, B, n, m );
	return res;
}
