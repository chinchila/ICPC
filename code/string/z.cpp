// Z[i] stores length of the longest substring starting from st[i]
// which is also prefix of str[0..n-1].
// O(|P|+|S|)
int Z[MAXN], m[MAXN];

void z_do( string S ) {
	int N = S.size(), L = 0, R = 0;
	Z[0] = N;
	for( int i = 1 ; i < N ; ++i ) {
		if( i < R ) Z[i] = min( R - i, Z[i - L] );
		while( i + Z[i] < N && S[i + Z[i]] == S[Z[i]] ) ++Z[i];
		if( i + Z[i] > R ) L = i, R = i + Z[i];
	}
}

int search( string S, string P ) {
	int N = S.size(), M = P.size(), msize = 0;
	string combined = P + S;
	z_do( combined );
	for( int i = 0 ; i < N ; ++i )
		if( Z[M + i] >= M ) m[msize++] = i;
	return msize;
}

