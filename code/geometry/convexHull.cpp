// O(n log n )
// NAO ESQUECE QUE O TAMANHO DO HULL VAI MUDAR, NAO USE N, USE .size()
// COLOQUEI UM n POR PARAMETRO PRA ISSO, MAS SE VAI USAR O N ANTIGO NAO PASSE
// #CUIDADO
// You can use pair<ptype, ptype> as P too
#include "point.cpp"

PType ccw( P a, P b, P c ) {
    return (b.x - a.x) * (c.y - a.y ) - (b.y - a.y) * (c.x - a.x );
}

vector<P> ch( P *points, int &n ) {
	sort( points, points+n );
	vector<P> hull( n + 1 );
	int idx = 0;
	for( int i = 0 ; i < n ; ++i ) {
		while( idx >= 2 && ccw( hull[idx - 2], hull[idx - 1], points[i] ) >= 0 ) --idx;
		hull[idx++] = points[i];
	}
	int half = idx;
	for( int i = n - 2 ; i >= 0 ; --i ) {
		while( idx > half && ccw( hull[idx - 2], hull[idx - 1], points[i] ) >= 0 ) --idx;
		hull[idx++] = points[i];
	}
	--idx;
	hull.resize( idx );
	n = hull.size();
	return hull;
}

