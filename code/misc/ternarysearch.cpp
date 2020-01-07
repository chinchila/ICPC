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
