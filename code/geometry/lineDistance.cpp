/**
Returns the signed distance between point p and the line containing points a and b. Positive value on left side and negative on right as seen from a towards b. a==b gives nan. P is supposed to be Point<T> or Point3D<T> where T is e.g. double or long long. It uses products in intermediate steps so watch out for overflow if using int or long long. Using Point3D will always give a non-negative distance.
O(1)
*/
#include "point.cpp"

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}

// from point p to seg b-a
double dist( P p, P a, P b ) {
	double k = ((p-a).dot(b-a))/((b-a).dot(b-a));
	return hypot( a.x+(b-a).x*k - p.x, a.y + (b-a).y*k - p.y );
}

// check if three points are collinear (integer)
bool collinear( P p1, P p2, P p3 ) {
	return (p1.y-p2.y) * (p1.x - p3.x) == (p1.y - p3.y) * (p1.x - p2.x );
}
//double
bool collinear(P p1, P p2, P p3 ) {
  return fabs((p1.y - p2.y) * (p1.x - p3.x) - (p1.y - p3.y) * (p1.x - p2.x)) <= 1e-9;
}
