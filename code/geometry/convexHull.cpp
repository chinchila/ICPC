// O(n log n )
// NAO ESQUECE QUE O TAMANHO DO HULL VAI MUDAR, NAO USE N, USE .size()
// COLOQUEI UM n POR PARAMETRO PRA ISSO, MAS SE VAI USAR O N ANTIGO NAO PASSE
// #CUIDADO
typedef pair<double, double> point;
double ccw( point a, point b, point c ) {
    return (b.first - a.first) * (c.second - a.second ) - (b.second - a.second) * (c.first - a.first );
}

vector<point> ch( point *points, int &n ) {
	sort( points, points+n );
	vector<point> hull( n + 1 );
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

