/**
 * Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * O(n)
 */
#include "point.cpp"
#include "segdist.cpp"

bool inPolygon(vector<P> &p, P a, bool strict = true) {
	int cnt = 0, n = p.size();
	for( int i = 0 ; i < n ; ++i ){
		P q = p[(i + 1) % n];
		if (onSegment(p[i], q, a)) return !strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt ^= ((a.y<p[i].y) - (a.y<q.y)) * a.cross(p[i], q) > 0;
	}
	return cnt;
}
