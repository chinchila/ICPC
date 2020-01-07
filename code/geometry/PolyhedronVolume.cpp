/**
Faces should point outwards.
O(n)
*/
template<class V, class L>
double signed_poly_volume(const V& p, const L& trilist) {
	double v = 0;
	for( auto i : trilist ) v += p[i.a].cross(p[i.b]).dot(p[i.c]);
	return v / 6;
}
