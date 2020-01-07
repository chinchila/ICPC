// A sequence xs is zigzag if x[i] < x[i+1], x[i+1] > x[i+2], for all i
// (initial direction can be arbitrary). The maximum length zigzag 
// subsequence is computed in O(n) time by a greedy method.
int longestZigZagSubsequence( vector<int> xs ) {
	int n = xs.size(), len = 1, prev = -1;
	for( int i = 0, j; i < n; i = j ){
		for( j = i+1 ; j < n && xs[i] == xs[j] ; ++j );
		if (j < n) {
			int sign = (xs[i] < xs[j]);
			if (prev != sign) ++len;
			prev = sign;
		}
	}
	return len;
}
int longestZigZagSubsequence(vector<int> A) {
	int n = A.size();
	int Z[n][2];
	Z[0][0] = 1;
	Z[0][1] = 1;
	int best = 1;
	for( int i = 1; i < n; ++i ){
		for( int j = i-1; j>= 0; --j ){
			if( A[j] < A[i] ) Z[i][0] = max( Z[j][1]+1, Z[i][0] );
			if( A[j] > A[i] ) Z[i][1] = max( Z[j][0]+1, Z[i][1] );
		}
		best = max( best, max( Z[i][0], Z[i][1] ) );
	}
	return best;
}
