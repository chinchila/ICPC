// Some basic stuff
// begin 3dhull
// if a and b are multiple (same line)
bool isMult(const P3& a, const P3& b) {
	P3 c = a.cross(b);
	return !(c.x!=0||c.y!=0||c.z!=0);
}

// a, b and c are collinear?
bool collinear(const P3& a, const P3& b, const P3& c) { 
	return isMult(b-a,c-a);
}

// Distance from point p to plane a->b, a->c
PType DC(const P3&a,const P3&b,const P3&c,const P3&p) {
	return (b-a).cross(c-a).dot(p-a);
}

// Point p coplanar with plane a->b, a->c?
bool coplanar(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return DC(a,b,c,p) == 0;
}
// Point p above plane a->b, a->c?
bool above(const P3&a,const P3&b,const P3&c,const P3&p) { 
	return DC(a,b,c,p) > 0;
}

// end 3dhull
