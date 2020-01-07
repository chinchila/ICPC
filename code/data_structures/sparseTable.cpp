//query from [first,last) / O( n * log(n) ) to build and O(1) to query | index 0
vector<vector<int> > jmp;
void build( const vector<int>& v ) {
	int n = v.size(), depth = 31 - __builtin_clz( N ) + 1;
	jmp.assign( depth + 1, v );
	for( int i = 0 ; i < depth ; ++i )
		for( int j = 0 ; j < n ; ++j )
			jmp[i+1][j] = min( jmp[i][j], jmp[i][min( n - 1, j + ( 1 << i ) )] );
}
int query( int a, int b ) {
	int dep = 31 - __builtin_clz( b - a );
	return min( jmp[dep][a], jmp[dep][b - ( 1 << dep )] );
}

