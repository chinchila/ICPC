/**
pair of the two points on the circle with radius r centered around c whos tangent lines intersect p. If p lies within the circle NaN-points are returned. P is intended to be Point<double>. The first point is the one to the right as seen from the p towards c.
O(1)
 */
#include "point.cpp"

pair<P,P> circleTangents(const P &p, const P &c, double r) {
	P a = p-c;
	double x = r*r/a.dist2(), y = sqrt(x-x*x);
	return make_pair(c+a*x+a.perp()*y, c+a*x-a.perp()*y);
}
