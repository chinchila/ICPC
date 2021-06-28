//subset sum O(n*sum)
dp[0] = 1;
for( int i = 0 ; i < n ; ++i )
	for(int j = sum ; j >= v[i] ; --j )
		dp[j] |= dp[j-v[i]];

// bitset optimization O(n*sum/(32|64))
bitset<MAXSUM> dp;
dp.set( 0 );
for( int i = 0 ; i < n ; ++i )
	dp |= dp << v[i];

// Código que decompõe as frequências
// onde f[i] é a frequência do peso i
// x = min(w, soma dos pesos)
dp.set( 0 );
for(int i = 1; i <= x; i++) {
  while(f[i] >= 3) {
    f[i] -= 2;
    f[i+i]++;
  }
  while(f[i] > 0) {
    f[i]--;
    dp |= dp << i;
  }
}


// coin change
#define INF 0x3f3f3f3f
// find the minimum number of coin changes
// coins = vector with values, n is size
int coin_change( int amt ){
	int dp[amt+1];
	int pred[amt+1];
	for( int i = 0 ; i <= amt ; ++i ) pred[i] = 0, dp[i] = INF;
	dp[0] = 0;
	for( int i = 1 ; i <= amt ; ++i ){
		int mini = dp[i];
		for (int j = 0 ; j < n ; ++j ){
			if( i >= coins[j] ){
				mini = min( mini, dp[i-coins[j]] + 1 );
				pred[i] = j;
			}
		}
		dp[i] = mini;
	}
	// get each coin used
	int m = amt;
	while( m != 0 ){
		//process here, coin value at coins[pred[m]]
		m -= coins[pred[m]];
	}
	return dp[amt];
}
