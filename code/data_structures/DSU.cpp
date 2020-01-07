// main: link[i] = i, rank[i] = 0, his[i] = 0; O( log n )
int link[MAXN], rank[MAXN], his[MAXN];

int find( int x, int t ) { return ( link[x] == x || his[x] > t ) ? x : find( link[x], t ); }

bool join( int a, int b, int t ) {
	if( ( a = find( a ) ) == ( b = find( b ) ) ) return false;
	if( rank[a] < rank[b] ) swap( a, b );
	else if( rank[a] == rank[b] ) ++rank[a];
	// bysize
	// if( size[a] < size[b] ) swap( a, b );
	// size[a] += size[b];
	link[b] = a, his[a] = t;
	return true;
}

