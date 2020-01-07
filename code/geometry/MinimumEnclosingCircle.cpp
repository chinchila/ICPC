/**
 * Computes the minimum circle that encloses a set of points.
 * O(n) maybe
 */
#include "circumcircle.cpp"

pair<P, double> mec( vector<P> ps ) {
	shuffle(ps.begin(), ps.end(), mt19937(time(0)));
	P o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
	for( int i = 0 ; i < ps.size() ; ++i ) {
		if( (o - ps[i]).dist() > r * EPS ) {
			o = ps[i], r = 0;
			for( int j = 0 ; j < i ; ++j ) {
				if( (o - ps[j]).dist() > r * EPS ) {
					o = (ps[i] + ps[j])/2;
					r = (o - ps[i]).dist();
					for( int k = 0 ; k  < j ; ++k ) {
						if( (o - ps[k]).dist() > r * EPS ) {
							o = ccCenter( ps[i], ps[j], ps[k] );
							r = (o - ps[i]).dist();
						}
					}
				}
			}
		}
	}
	return {o, r};
}
