/**
Apply the linear transformation (translation, rotation and scaling) which takes line p0-p1 to line q0-q1 to point r.
O(1)
*/
#include "point.cpp"

P transform(const P& p0, const P& p1, const P& q0, const P& q1, const P& r) {
	P dp = p1-p0, dq = q1-q0, num(dp.cross(dq), dp.dot(dq));
	return q0 + P((r-p0).cross(num), (r-p0).dot(num))/dp.dist2();
}
