// inclusion exclusion principle
int n, k, res;
vector<int>pr;

void solve(int a, int p, ll x){
	if( x > n ) return;
	if( p == -1 ){
		if( x == 1 ) return;
		res += ( a%2 == 1 ? -1 : 1 ) * n / x;
		return;
	}
	solve( a, p - 1, x );
	solve( a + 1, p - 1, x * pr[p] );
}

