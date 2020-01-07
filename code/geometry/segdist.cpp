/**
Returns the shortest distance between point p and the line segment from point s to e.
bool onSegment = segDist(a,b,p) < 1e-10;
O(1)
*/
#include "point.cpp"

template<class P> bool onSegment( P a, P b, P c ) {
	return segDist(a,b,c) < 1e-10;
}

typedef Point<double> P;
double segDist(P& s, P& e, P& p) {
	if (s==e) return (p-s).dist();
	auto d = (e-s).dist2(), t = min(d,max(.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}
