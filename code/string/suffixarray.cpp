// O(n log(n) )
vector<int> suffix_array( string S ) {
	int N = S.size();
	vector<int> sa( N ), classes( N );
	for( int i = 0 ; i < N ; ++i ) sa[i] = N - 1 - i, classes[i] = S[i];
	stable_sort( sa.begin(), sa.end(), [&S]( int i, int j ) {
		return S[i] < S[j];
	} );
	for( int len = 1 ; len < N ; len *= 2 ) {
		vector<int> c( classes );
		for( int i = 0; i < N; ++i ) {
			bool same = i && sa[i - 1] + len < N
			              && c[sa[i]] == c[sa[i - 1]]
			              && c[sa[i] + len / 2] == c[sa[i - 1] + len / 2];
			classes[sa[i]] = same ? classes[sa[i - 1]] : i;
		}
		vector<int> cnt( N ), s( sa );
		for( int i = 0 ; i < N ; ++i ) cnt[i] = i;
		for( int i = 0 ; i < N ; ++i ) {
			int s1 = s[i] - len;
			if( s1 >= 0 )
				sa[cnt[classes[s1]]++] = s1;
		}
	}
	return sa;
}

vector<int> LCP( const vector<int>& sa, string S ) {
	int N = S.size();
	vector<int> rank( N ), lcp( N - 1 );
	for( int i = 0 ; i < N ; ++i ) rank[sa[i]] = i;
	int pre = 0;
	for( int i = 0 ; i < N ; ++i ) {
		if( rank[i] < N - 1 ) {
			int j = sa[rank[i] + 1];
			while( max( i, j ) + pre < S.size() && S[i + pre] == S[j + pre] ) ++pre;
			lcp[rank[i]] = pre;
			if( pre > 0 ) --pre;
		}
	}
	return lcp;
}

// O(n)
vector<int> buildSa(const string& in) {
	int n = in.size(), c = 0;
	vector<int> temp(n), posBucket(n), bucket(n), bpos(n), out(n);
	for (int i = 0; i < n; i++) out[i] = i; 
	sort(out.begin(), out.end(), [&](int a, int b) { return in[a] < in[b]; });
	for (int i = 0; i < n; i++) {
		bucket[i] = c;
		if (i + 1 == n || in[out[i]] != in[out[i + 1]]) c++;
	}
	for (int h = 1; h < n && c < n; h <<= 1) {
		for (int i = 0; i < n; i++) posBucket[out[i]] = bucket[i];
		for (int i = n - 1; i >= 0; i--) bpos[bucket[i]] = i;
		for (int i = 0; i < n; i++) {
			if (out[i] >= n - h) temp[bpos[bucket[i]]++] = out[i];
		}
		for (int i = 0; i < n; i++) {
			if (out[i] >= h) temp[bpos[posBucket[out[i] - h]]++] = out[i] - h;
		}
		c = 0;
		for (int i = 0; i + 1 < n; i++) {
				int a = (bucket[i] != bucket[i + 1]) || (temp[i] >= n - h)
						|| (posBucket[temp[i + 1] + h] != posBucket[temp[i] + h]);
				bucket[i] = c;
				c += a;
		}
		bucket[n - 1] = c++;
		temp.swap(out);
	}
	return out;
}

// Longest Repeated Substring O(n)
int lrs = 0;
for( int i = 0 ; i < n ; ++i ) lrs = max(lrs, lcp[i]);

// Longest Common Substring O(n)
string LCS(string &a, string &b) {
  string s = a + '$' + b + '#';
  vector<int> sa = buildSa(s);
  vector<int> lcp = LCP(sa, s);
  int lcs = 0, idx = -1;
  for (int i = 0; i < s.size()-1; i++) {
    if ((sa[i] < a.size()) != (sa[i + 1] < a.size())) {
      if (lcp[i] > lcs) {
        lcs = lcp[i];
        idx = sa[i];
      }
    }
  }
  return s.substr(idx, lcs);
}

// To calc LCS for multiple texts use a slide window with minqueue
// The number of different substrings of a string is n*(n + 1)/2 - sum(lcs[i]) 
