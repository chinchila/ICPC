// Half plane intersection O(n*log(n))
// lines must be ccw (antihorario)

#include "point.h"
#include "lineIntersection.cpp"

bool cmp (P a,  P b) {
	if( a.quad() != b.quad() ) return a.quad() < b.quad();
	else return sgn( a.cross( b ) ) > 0;
}

bool operator < (L l0, L l1) {
	if (sameDir(l0, l1)) {
		return l1.include(l0[0]);
	} else {
		return cmp( l0.dir(), l1.dir() );
	}
}

bool check(L u, L v, L w) { 
	return w.include(lineInter(u, v).second); 
}

vector<P> halfPlaneIS(vector<L> &l) {
	sort(l.begin(), l.end());
	deque<L> q;
	for (int i = 0; i < (int)l.size(); ++i) {
		if (i && sameDir(l[i], l[i - 1])) continue;
		while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i])) q.pop_back();
		while (q.size() > 1 && !check(q[1], q[0], l[i])) q.pop_front();
		q.push_back(l[i]);
	}
	while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0])) q.pop_back();
	while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1])) q.pop_front();
	vector<P> ret;
	for (int i = 0; i < (int)q.size(); ++i) ret.push_back(lineInter(q[i], q[(i + 1) % q.size()]).second);
	return ret;
}