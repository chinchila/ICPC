//O(n^2)
/*
Computes the Delaunay triangulation of a set of points.
Each circumcircle contains none of the input points.
If any three points are colinear or any four are on the same circle, behavior is undefined.
*/
#include "point.cpp"
#include "3dhull.cpp"

vector<array<P,3>> triHull(vector<P> p) {
	vector<P3> p3; vector<array<P,3>> res; for(auto x:p) p3.pb(P3(x.x,x.y,x.dist2()));
	bool ok = 0; for(auto t:p3) if (!coplanar(p3[0],p3[1],p3[2],t)) ok = 1;
	if (!ok) { // all points concyclic
		sort(1+all(p),[&p](P a, P b) { return (a-p[0]).cross(b-p[0]) > 0; });
		for(size_t i=1;i<p.size()-1;++i) res.pb({p[0],p[i],p[i+1]});
	} else {
		#define nor(h) P(p3[h].x,p3[h].y)
		for(auto t:hull3d(p3)) 
			if((p3[t[1]]-p3[t[0]]).cross(p3[t[2]]-p3[t[0]]).dot(P3(0,0,1)) < 0)
				res.pb({nor(t[0]),nor(t[2]),nor(t[1])});
	}
	return res;
}

/**
Each circumcircle contains none of the input points.
There must be no duplicate points.
If all points are on a line, no triangles will be returned.
Should work for doubles as well, though there may be precision issues in 'circ'.
pts variable contains triangles in order \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\},
all counter-clockwise.
Returns vector of triangles.
O(n log n)
*/
#include "point.cpp"

typedef struct Quad* Q;
typedef __int128_t lll; // (can be ll if coords are < 2e4)
P arb(LLONG_MAX,LLONG_MAX); // not equal to any other point

struct Quad {
	bool mark; Q o, rot; P p;
	P F() { return r()->p; }
	Q r() { return rot->rot; }
	Q prev() { return rot->o->rot; }
	Q next() { return r()->prev(); }
};

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
	lll p2 = p.dist2(), A = a.dist2()-p2,
	    B = b.dist2()-p2, C = c.dist2()-p2;
	return p.cross(a,b)*C + p.cross(b,c)*A + p.cross(c,a)*B > 0;
}
Q makeEdge(P orig, P dest) {
	Q q[] = {new Quad{0,0,0,orig}, new Quad{0,0,0,arb},
	         new Quad{0,0,0,dest}, new Quad{0,0,0,arb}};
	for( int i = 0 ; i < 4 ; ++i )
		q[i]->o = q[-i & 3], q[i]->rot = q[(i+1) & 3];
	return *q;
}
void splice(Q a, Q b) {
	swap(a->o->rot->o, b->o->rot->o); swap(a->o, b->o);
}
Q connect(Q a, Q b) {
	Q q = makeEdge(a->F(), b->p);
	splice(q, a->next());
	splice(q->r(), b);
	return q;
}

pair<Q,Q> rec(const vector<P>& s) {
	if (s.size() <= 3) {
		Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
		if (s.size() == 2) return { a, a->r() };
		splice(a->r(), b);
		auto side = s[0].cross(s[1], s[2]);
		Q c = side ? connect(b, a) : 0;
		return {side < 0 ? c->r() : a, side < 0 ? c : b->r() };
	}

#define H(e) e->F(), e->p
#define valid(e) (e->F().cross(H(base)) > 0)
	Q A, B, ra, rb;
	int half = s.size() / 2;
	tie(ra, A) = rec({s.begin(), s.end() - half});
	tie(B, rb) = rec({s.size() - half + s.begin(), s.end()});
	while ((B->p.cross(H(A)) < 0 && (A = A->next())) ||
	       (A->p.cross(H(B)) > 0 && (B = B->r()->o)));
	Q base = connect(B->r(), A);
	if (A->p == ra->p) ra = base->r();
	if (B->p == rb->p) rb = base;

#define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
		while (circ(e->dir->F(), H(base), e->F())) { \
			Q t = e->dir; \
			splice(e, e->prev()); \
			splice(e->r(), e->r()->prev()); \
			e = t; \
		}
	for (;;) {
		DEL(LC, base->r(), o);  DEL(RC, base, prev());
		if (!valid(LC) && !valid(RC)) break;
		if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
			base = connect(RC, base->r());
		else
			base = connect(base->r(), LC->r());
	}
	return { ra, rb };
}

vector<array<P,3>> triangulate(vector<P> pts) {
	sort(pts.begin(), pts.end());
	if (pts.size() < 2) return {};
	Q e = rec(pts).first;
	vector<Q> q = {e};
	size_t qi = 0;
	while (e->o->F().cross(e->F(), e->p) < 0) e = e->o;
#define ADD { Q c = e; do { c->mark = 1; pts.push_back(c->p); \
	q.push_back(c->r()); c = c->next(); } while (c != e); }
	ADD; pts.clear();
	while (qi < q.size()) if (!(e = q[qi++])->mark) ADD;
	vector<array<P,3>> ret(pts.size()/3); 
	for(size_t i=0;i<pts.size();++i) ret[i/3][i%3] = pts[i];
	return ret;
}
