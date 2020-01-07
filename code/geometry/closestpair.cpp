// Closest pair with line sweep
// O(n log n)
#define ll long long
#define nd second
#define st first
int n; //amount of points
pair<ll, ll> pnt[MAXN];

struct cmp{
	bool operator()(pair<ll,ll> a, pair<ll, ll> b) { return a.nd < b.nd; }
};

double closest_pair() {
	sort( pnt, pnt + n );
	double best = numeric_limits<double>::infinity();
	set<pair<ll, ll>, cmp> box;
	box.insert( pnt[0] );
	int l = 0;
	for( int i = 1 ; i < n ; ++i ){
		while( l < i && pnt[i].st - pnt[l].st > best )
			box.erase( pnt[l++] );
		for( auto it = box.lower_bound( {0, pnt[i].nd - best} ) ; it != box.end() && pnt[i].nd + best >= it->nd ; ++it )
			best = min( best, hypot( pnt[i].st - it->st, pnt[i].nd - it->nd ) );
		box.insert( pnt[i] );
	}
	return best;
}
