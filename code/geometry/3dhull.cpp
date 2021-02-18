// O(n^2)
#include "point3d.cpp"
#include "3dbasics.cpp"
typedef vector<P3> vP3;
using vb = vector<bool>;
#define pb push_back
using F = array<int,3>; // face
// rearrange points such that first four are not coplanar
void prep(vP3& p) {
	int num = 1;
	for(int i = 1 ; i < p.size() || num < 4 ; ++i){
		if (num == 1) {
			if (p[0] != p[i]) swap(p[1],p[i]), ++num;
		} else if (num == 2) {
			if (!collinear(p[0],p[1],p[i]))
				swap(p[2],p[i]), ++num;
		} else if (num == 3) {
			if (!coplanar(p[0],p[1],p[2],p[i]))
				swap(p[3],p[i]), ++num;
		}
	}
	// if this trigger then there are 4 points coplanar
	assert(num == 4);
}

vector<F> hull3d(vP3& p) { // order of points is changed s.t. first four points form tetra
	prep(p); int N = p.size(); vector<F> hull; // triangle for each face
	auto ad = [&](int a, int b, int c) { hull.pb({a,b,c}); }; // add a new face to hull
	ad(0,1,2), ad(0,2,1); // initialize hull as first three points
	vector<vb> in(N,vb(N)); // is zero before each iteration
	for(int i=3;i<N;++i) { // incremental construction
		vector<F> def, HULL; swap(hull,HULL); // HULL now contains old hull
		auto ins = [&](int a, int b, int c) {
			if (in[b][a]) in[b][a] = 0; // kill reverse face
			else in[a][b] = 1, ad(a,b,c);
		};
		for(auto f : HULL) {
			if (above(p[f[0]],p[f[1]],p[f[2]],p[i])) // recalc all faces such that point is above face
				for(int j=0;j<3;++j) ins(f[j],f[(j+1)%3],i);
			else def.pb(f); 
		}
		for(auto t : hull) if (in[t[0]][t[1]]) // edge is exposed, add a new face
			in[t[0]][t[1]] = 0, def.pb(t);
		swap(hull,def);
	}
	return hull;
}

// This one is faster when we have a lot of points
// copy the defines and prep() from previous implementation
// can give wrong hull so be carefull
#define all(k) k.begin(), k.end()
using pi = pair<int,int>;
#define f first
#define s second
#define eb emplace_back
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

vector<F> hull3dFast(vP3& p) { // order of points is changed s.t. first four points form tetra
	shuffle(all(p),rng); prep(p); int N = p.size(); vector<F> hull; 
	vb active; vector<vector<int>> rvis; vector<array<pi,3>> other; // whether face is active
	// points visible from each face, other face adjacent to each edge of face
	vector<vector<int>> vis(N); // faces visible from each point
	auto ad = [&](int a, int b, int c) { 
		hull.pb({a,b,c}); active.pb(1); rvis.eb(); other.eb(); };
	auto ae = [&](int a, int b) { vis[b].pb(a), rvis[a].pb(b); };
	auto abv = [&](int a, int b) {
		F f = hull[a]; return above(p[f[0]],p[f[1]],p[f[2]],p[b]); };
	auto edge = [&](pi e) -> pi { return {hull[e.f][e.s],hull[e.f][(e.s+1)%3]}; };
	auto glue = [&](pi a, pi b) { // link two faces by an edge
		pi x = edge(a);
		other[a.f][a.s] = b, other[b.f][b.s] = a;
	}; 
	ad(0,1,2), ad(0,2,1); if (abv(1,3)) swap(p[1],p[2]); // ensure face 0 is removed when i=3
	for(int i=0;i<3;++i) glue({0,i},{1,2-i});
	for(int i=3;i<N;++i) ae(abv(1,i),i); // those that are coplanar go in rvis[0]
	vector<int> label(N,-1);
	for(int i=3;i<N;++i) { // incremental construction
		vector<int> rem; for(auto t:vis[i]) if (active[t]) active[t] = 0, rem.pb(t);
		if (!rem.size()) continue; // hull unchanged
		int st = -1; 
		for(auto r:rem) for(int j=0;j<3;++j) {
			int o = other[r][j].f;
			if (active[o]) { // create new face!
				int a,b; tie(a,b) = edge({r,j}); ad(a,b,i); st = a;
				int cur = rvis.size()-1; label[a] = cur; 
				vector<int> tmp; set_union(all(rvis[r]),all(rvis[o]),back_inserter(tmp)); 
				// merge sorted vectors ignoring duplicates
				for(auto x:tmp) if (abv(cur,x)) ae(cur,x);
				// if no rounding errors then guaranteed that only x > i matters
				glue({cur,0},other[r][j]); // glue old face with new face
			}
		}
		for (int x = st, y; ; x = y) { // glue new faces together
			int X = label[x]; glue({X,1},{label[y=hull[X][1]],2});
			if (y == st) break;
		}
	}
	vector<F> ans; for(int i=0;i<hull.size();++i) if (active[i]) ans.pb(hull[i]);
	return ans;
}
