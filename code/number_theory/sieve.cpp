//O(n)
int lp[MAXN], pr[MAXN];
int cnt;

void sieve( int n ) {
	for( int i = 2 ; i <= n ; ++i ) {
		if( lp[i] == 0 ) lp[i] = pr[cnt++] = i;
		for( int j = 0 ; j < cnt && pr[j]<=lp[i] && i * pr[j] <= n ; ++j )
			lp[i * pr[j]] = pr[j];
	}
}

// O(n log log n)
void sieve( int n ) {
	vector<bool> is_prime(n+1, true);
	is_prime[0] = is_prime[1] = false;
	for (int i = 2; i * i <= n; i++) {
		if (is_prime[i]) {
			for (int j = i * i; j <= n; j += i)
				is_prime[j] = false;
		}
	}
}

