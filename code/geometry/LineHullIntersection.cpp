/**
Line-convex polygon intersection. The polygon must be ccw and have no colinear points.
 * lineHull(line, poly) returns a pair describing the intersection of a line with the polygon:
 *    (-1, -1) if no collision,
 *    (i, -1) if touching the corner i,
 *    (i, i) if along side (i, i+1),
 *    (i, j) if crossing sides (i, i+1) and (j, j+1).
In the last case, if a corner $i$ is crossed, this is treated as happening on side (i, i+1).
The points are returned in the same order as the line hits the polygon.
extrVertex: returns the point of a hull with the max projection onto a line.
 * Time: O(N + Q \log n)
 */
#include "point.cpp"

typedef array<P, 2> Line;
#define cmp(i,j) sgn(dir.perp().cross(poly[(i)%n]-poly[(j)%n]))
#define extr(i) cmp(i + 1, i) >= 0 && cmp(i, i - 1 + n) < 0
int extrVertex(vector<P>& poly, P dir) {
	int n = sz(poly), lo = 0, hi = n;
	if (extr(0)) return 0;
	while (lo + 1 < hi) {
		int m = (lo + hi) / 2;
		if (extr(m)) return m;
		int ls = cmp(lo + 1, lo), ms = cmp(m + 1, m);
		(ls < ms || (ls == ms && ls == cmp(lo, m)) ? hi : lo) = m;
	}
	return lo;
}

#define cmpL(i) sgn(line[0].cross(poly[i], line[1]))
array<int, 2> lineHull(Line line, vector<P> poly) {
	int endA = extrVertex(poly, (line[0] - line[1]).perp());
	int endB = extrVertex(poly, (line[1] - line[0]).perp());
	if (cmpL(endA) < 0 || cmpL(endB) > 0)
		return {-1, -1};
	array<int, 2> res;
	for( int i = 0 ; i < 2 ; ++i ) {
		int lo = endB, hi = endA, n = sz(poly);
		while ((lo + 1) % n != hi) {
			int m = ((lo + hi + (lo < hi ? 0 : n)) / 2) % n;
			(cmpL(m) == cmpL(endB) ? lo : hi) = m;
		}
		res[i] = (lo + !cmpL(hi)) % n;
		swap(endA, endB);
	}
	if (res[0] == res[1]) return {res[0], -1};
	if (!cmpL(res[0]) && !cmpL(res[1]))
		switch ((res[0] - res[1] + sz(poly) + 1) % sz(poly)) {
			case 0: return {res[0], res[0]};
			case 2: return {res[1], res[1]};
		}
	return res;
}
