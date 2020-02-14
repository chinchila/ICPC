/**
Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
vector<P> p = ...;
p = polygonCut(p, P(0,0), P(1,0));
*/
#include "point.cpp"
#include "lineIntersection.cpp"

vector<P> polygonCut(const vector<P>& poly, P s, P e) {
	vector<P> res;
	for( int i = 0 ; i < poly.size() ; ++i ) {
		P cur = poly[i], prev = i ? poly[i-1] : poly.back();
		bool side = s.cross(e, cur) < 0;
		if (side != (s.cross(e, prev) < 0))
			res.push_back(lineInter(s, e, cur, prev).second);
		if (side)
			res.push_back(cur);
	}
	return res;
}
