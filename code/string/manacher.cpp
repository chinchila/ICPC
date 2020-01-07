// To get the string just str.substr( ( id + 1 - mx ) / 2, mx ) | mx is the size of the LPS
// O(n)
pair<int, int> manacher( string str ){
	int i, j, k, l = str.length(), n = l << 1, mx = -1, id;
	vector<int> pal( n );
	for( i = 0, j = 0, k = 0 ; i < n ; j = max( 0, j - k ), i += k ) {
		while( j <= i && ( i + j + 1 ) < n && str[( i - j ) >> 1] == str[( i + j + 1 ) >> 1] ) ++j;
		for( k = 1, pal[i] = j; k <= i && k <= pal[i] && ( pal[i] - k ) != pal[i - k]; ++k )
			pal[i + k] = min( pal[i - k], pal[i] - k );
		if( pal[i] > mx ) mx = pal[i], id = i;
	}
	pal.pop_back();
	return { mx, id };
}

