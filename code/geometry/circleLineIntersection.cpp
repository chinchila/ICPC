// p1 and p2 defines line
// cen is center and rad is radius from circle
// r1, r2 are the points that intersect, returns number of points intersecting circle
#include "point.cpp"
#define EPS 1e-9
#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884L
#endif
int circleLineIntersection(const P& p0, const P& p1, const P& cen, double rad, P& r1, P& r2) {
	double a, b, c, t1, t2;
	a = (p1 - p0).dot(p1 - p0);
	b = 2 * (p1 - p0).dot(p0 - cen);
	c = (p0-cen).dot(p0-cen) - rad * rad;
	double det = b * b - 4 * a * c;
	int res;
	if( fabs( det ) < EPS ) det = 0, res = 1;
	else if( det < 0 ) res = 0;
	else res = 2;
	det = sqrt( det );
	t1 = ( -b + det ) / ( 2 * a );
	t2 = ( -b - det ) / ( 2 * a );
	r1 = p0 + ( p1 - p0 ) * t1;
	r2 = p0 + ( p1 - p0 ) * t2;
	return res;
}
// returns the arc length
// p1, p2 are the segment
// r radius, cen is center of circle
double calcArc( P p1, P p2, double r, P &cen ) {
	double d = (p2-p1).dist();
	double ang = ((p1-cen).angle() - (p2-cen).angle()) * 180 / M_PI;
	if( ang < 0 ) ang += 360;
	ang = min( ang, 360 - ang );
	return r * ang * M_PI / 180;
}
