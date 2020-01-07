// Minimum number of operations (insert, remove, replace)
// to make strings equal
// O(n^2)

int editDistDP( string s1, string s2 ){
	int m = s1.size(), n = s2.size();
	int dp[m+1][n+1];
	for( int i = 0 ; i <= n ; ++i ){
		for( int j = 0 ; j <= m ; ++j ){
			if( i == 0 ) dp[i][j] = j;
			else if( j == 0 ) dp[i][j] = i;
			else if( s1[i-1] == s2[j-1] )
				dp[i][j] = dp[i-1][j-1];
			else
				//insert, remove, replace respectively
				dp[i][j] = 1 + min( dp[i][j-1], min( dp[i-1][j], dp[i-1][j-1] ) );
		}
	}
	return dp[n][m];
}

