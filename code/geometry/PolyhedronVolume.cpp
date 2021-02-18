/**
Faces should point outwards.
first = Surface area
second = volume
O(n)
*/
#include "point3d.cpp"

pair<PType, PType> SaVol(vector<P3> &p, vector<F> &faces) {
	PType s = 0, v = 0; 
	for(auto i : faces) {
		P3 a = p[i[0]], b = p[i[1]], c = p[i[2]];
		P3 q = (b-a).cross(c-a);
		s += q.dist(); v += a.cross(b).dot(c);
	}
	return {s/2,v/6};
}