// Closest pair with line sweep
// retorna quadrado da menor distancia
// O(n log n)
#define ll long long
#define nd second
#define st first

ll closest_pair(vector<pair<ll, ll>> &pnt) {
	sort( pnt.begin(), pnt.end() );
	ll best = numeric_limits<ll>::max();
	ll d = ceil(sqrt(best));
	set<pair<ll, ll>> box;
	box.insert( {pnt[0].nd, pnt[0].st} );
	int l = 0;
	for( int i = 1 ; i < pnt.size() ; ++i ){
		while( l < i && pnt[i].st - pnt[l].st >= best )
			box.erase( {pnt[l].nd, pnt[l].st} ), ++l;
		auto D = box.upper_bound( {pnt[i].nd + d, pnt[i].st} );
		for( auto it = box.lower_bound( {pnt[i].nd - d, pnt[i].st} ) ; it != D ; ++it ){
			ll x = pnt[i].st-it->nd;
			ll y = pnt[i].nd-it->st;
			best = min( best, x*x + y*y );
			d = ceil(sqrt(best));
		}
		box.insert( {pnt[i].nd, pnt[i].st} );
	}
	return best;
}