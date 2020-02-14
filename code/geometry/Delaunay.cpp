//O(n^2)
/*
Computes the Delaunay triangulation of a set of points.
Each circumcircle contains none of the input points.
If any three points are colinear or any four are on the same circle, behavior is undefined.
*/
#include "point.cpp"
#include "3dhull.cpp"

template<class F>
void delaunay(vector<P>& ps, F trifun) {
	if (sz(ps) == 3) { int d = (ps[0].cross(ps[1], ps[2]) < 0);
		trifun(0,1+d,2-d); }
	vector<P3> p3;
	trav(p, ps) p3.emplace_back(p.x, p.y, p.dist2());
	if (sz(ps) > 3) trav(t, hull3d(p3)) if ((p3[t.b]-p3[t.a]).
			cross(p3[t.c]-p3[t.a]).dot(P3(0,0,1)) < 0)
		trifun(t.a, t.c, t.b);
}

/**
Each circumcircle contains none of the input points.
There must be no duplicate points.
If all points are on a line, no triangles will be returned.
Should work for doubles as well, though there may be precision issues in 'circ'.
Returns triangles in order \{t[0][0], t[0][1], t[0][2], t[1][0], \dots\}, all counter-clockwise.
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

vector<P> triangulate(vector<P> pts) {
	sort(pts.begin(), pts.end());
	if (pts.size() < 2) return {};
	Q e = rec(pts).first;
	vector<Q> q = {e};
	int qi = 0;
	while (e->o->F().cross(e->F(), e->p) < 0) e = e->o;
#define ADD { Q c = e; do { c->mark = 1; pts.push_back(c->p); \
	q.push_back(c->r()); c = c->next(); } while (c != e); }
	ADD; pts.clear();
	while (qi < q.size()) if (!(e = q[qi++])->mark) ADD;
	return pts;
}
