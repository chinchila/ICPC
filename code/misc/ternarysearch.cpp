double f( double x ) {
	return x;
}

double tsearch( double x ) {
	double l = 0, r = x;
	while( abs( l - r ) > EPS ) {
		double lt = l + ( r - l ) /3;
		double rt = r - ( r - l ) /3;
		if( f(lt) > f(rt) ) l = lt;
		else r = rt;
	}
	return max( r, l );
}

int tsearch(){
	int l = 0, r = INF;
	while( r - l >= 7 ) {
		int mid = ( r + l ) / 2;
		if( f(mid) < f(mid+1) ) r = mid+1;
		else l = mid;
	}
	for( int i = l+1 ; i <= r ; ++i ){
		if( f(l) > f(i) ) l = i;
	}
	return l;
}

