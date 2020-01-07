/*
O(1) for make_tree
O(log n) amortized for all other operations
*/
typedef long long lld;
typedef unsigned long long llu;
using namespace std;
struct Node { int L, R, P, PP, sz; };
Node LCT[MAXN];

void make_tree( int v ){
	if (v == -1) return;
	LCT[v].L = LCT[v].R = LCT[v].P = LCT[v].PP = -1;
}

void update( int v ) {
	LCT[v].sz = 1;
	if( LCT[v].L != -1 ) LCT[v].sz += LCT[LCT[v].L].sz;
	if( LCT[v].R != -1 ) LCT[v].sz += LCT[LCT[v].R].sz;
}

void rotate( int v ){
	if( v == -1 ) return;
	if( LCT[v].P == -1 ) return;
	int p = LCT[v].P;
	int g = LCT[p].P;
	if( LCT[p].L == v ) {
		LCT[p].L = LCT[v].R;
		if( LCT[v].R != -1 ) LCT[LCT[v].R].P = p;
		LCT[v].R = p;
		LCT[p].P = v;
	} else {
		LCT[p].R = LCT[v].L;
		if( LCT[v].L != -1 ) LCT[LCT[v].L].P = p;
		LCT[v].L = p;
		LCT[p].P = v;
	}
	LCT[v].P = g;
	if( g != -1 ){
		if (LCT[g].L == p) LCT[g].L = v;
		else LCT[g].R = v;
	}
	LCT[v].PP = LCT[p].PP;
	LCT[p].PP = -1;
	update( p );
}

void splay( int v ){
	if (v == -1) return;
	while( LCT[v].P != -1 ){
		int p = LCT[v].P;
		int g = LCT[p].P;
		if( g == -1 )rotate(v);
		else if( ( LCT[p].L == v ) == ( LCT[g].L == p ) ) {
			rotate( p );
			rotate( v );
		} else {
			rotate( v );
			rotate( v );
		}
	}
	update( v );
}

void expose( int v ){
	if( v == -1 ) return;
	splay( v );
	if( LCT[v].R != -1 ) {
		LCT[LCT[v].R].PP = v;
		LCT[LCT[v].R].P = -1;
		LCT[v].R = -1;
		update( v );
	}
	while( LCT[v].PP != -1 ){
		int w = LCT[v].PP;
		splay( w );
		if( LCT[w].R != -1 ) {
			LCT[LCT[w].R].PP = w;
			LCT[LCT[w].R].P = -1;
		}
		LCT[w].R = v;
		LCT[v].P = w;
		update( w );
		splay(v);
	}
}

int find_root( int v ){
	if( v == -1 ) return -1;
	expose( v );
	int ret = v;
	while( LCT[ret].L != -1 ) ret = LCT[ret].L;
	expose( ret );
	return ret;
}

void link( int v, int w ){
	if( v == -1 || w == -1 ) return;
	expose( w );
	LCT[v].L = w;
	LCT[w].P = v;
	LCT[w].PP = -1;
	update( v );
}

int depth( int v ) {
	expose( v );
	return LCT[v].sz - 1;
}

void cut( int v ){
	if( v == -1 ) return;
	expose( v );
	if( LCT[v].L != -1 ){
		LCT[LCT[v].L].P = -1;
		LCT[LCT[v].L].PP = -1;
		LCT[v].L = -1;
	}
	update( v );
}

bool connected( int p, int q) {
	return find_root( p ) == find_root( q );
}

int LCA( int p, int q ){
	expose( p );
	splay( q );
	if( LCT[q].R != -1 ) {
		LCT[LCT[q].R].PP = q;
		LCT[LCT[q].R].P = -1;
		LCT[q].R = -1;
	}
	int ret = q, t = q;
	while( LCT[t].PP != -1 ) {
		int w = LCT[t].PP;
		splay( w );
		if( LCT[w].PP == -1 ) ret = w;
		if( LCT[w].R != -1 ) {
			LCT[LCT[w].R].PP = w;
			LCT[LCT[w].R].P = -1;
		}
		LCT[w].R = t;
		LCT[t].P = w;
		LCT[t].PP = -1;
		t = w;
	}
	splay( q );
	return ret;
}
