/**
Description: Returns twice the signed area of a polygon.
Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
O(n)
*/
#include "point.cpp"

template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	for( int i = 0 ; i < v.size()-1 ; ++i ) a += v[i].cross(v[i+1]);
	return a;
}
