/**
bool left = sideOf(p1,p2,q)==1;
O(1)
 */
#include "point.cpp"

int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

int sideOf(const P& s, const P& e, const P& p, double eps) {
	auto a = (e-s).cross(p-s);
	double l = (e-s).dist()*eps;
	return (a > l) - (a < -l);
}
