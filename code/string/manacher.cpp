// d1, d2 = number of palindromes with odd and even lengths with centers in i
vector<int> d1, d2;

void manacher( string s ){
	int n = s.length();
	// odd
	d1.resize(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
		d1[i] = k--;
		if (i + k > r) l = i - k, r = i + k;	
	}
	// even
	d2.resize(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;	
		d2[i] = k--;
		if (i + k > r) l = i - k - 1, r = i + k ;
	}
}

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


