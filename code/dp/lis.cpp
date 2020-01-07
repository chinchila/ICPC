// O(n log n)
vector<int> lis( vector<int> v ) {
	vector<pair<int, int> > best;
	vector<int> dad( v.size(), -1 );
	for( int i = 0 ; i < v.size() ; ++i ) {
		pair<int, int> item = make_pair( v[i], 0 );
		auto it = lower_bound( best.begin(), best.end(), item );
		item.second = i;
		/* non-decreasing
		pair<int, int> item = make_pair(v[i], i);
		auto it = upper_bound( best.begin(), best.end(), item );
		*/
		if( it == best.end() ) {
			dad[i] = ( best.size() == 0 ? -1 : best.back().second );
			best.push_back( item );
		} else {
			dad[i] = it == best.begin() ? -1 : prev( it )->second;
			*it = item;
		}
	}
	vector<int> ret;
	for( int i = best.back().second ; i >= 0 ; i = dad[i] ) ret.push_back( v[i] );
	reverse( ret.begin(), ret.end() );
	return ret;
}

// Only size of lis
int lis( vector<int> v ) {
	int dp[v.size() + 10], lis = -1;
	memset( dp, 0x3f, sizeof dp );
	for( int i : v ) {
		int j = lower_bound( dp, dp + lis, i ) - dp;
		dp[j] = min( dp[j], i );
		lis = max( lis, j + 1 );
	}
	return lis;
}


// lis O(n^2) and count how many lises are, please take care of long long
// dp[i] stores length of the lis ending at i
// tot[i] stores how many ways we can obtain the lis ending in the values d[i]

int tot[MAXN];
int dp[MAXN];

pair<int, int> lis( vector<int> a ) {
	int lis = 1;
	for( int i = 0 ; i < a.size() ; ++i ) {
		dp[i] = 1;
		tot[i] = 1;
		for( int j = 0 ; j < i ; ++j ) {
			if( a[j] < a[i] ) {
				if( dp[i] < dp[j] + 1 ) {
					dp[i] = dp[j] + 1;
					tot[i] = tot[j];
					lis = max( lis, dp[i] );
				} else if( dp[i] == dp[j] + 1 ) {
					tot[i] = ( tot[i] + tot[j] ) % MOD;
				}
			}
		}
	}
	int qnt = 0;
	for( int i = 0 ; i < a.size() ; ++i ) {
		if( dp[i] == lis ) {
			qnt = ( qnt + tot[i] ) % MOD;
		}
	}
	return {lis, qnt};
}
