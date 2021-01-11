//Aways prefer long long/int as PType
template <class T> int sgn( T x ) { return (x > 0) - (x < 0); }
template<class T> struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	explicit Point(const Point &a, const Point &b) : x(b.x - a.x), y(b.y - a.y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	// Manhattan distance
	T manh() const { return abs(x) + abs(y); }
	// Chebyshev distance (manhattan with diagonals)
	T cheb() const { return max(abs(x), abs(y)); }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); }
	P perp() const { return P(-y, x); }
	P normal() const { return perp().unit(); }
	int quad() const { return sgn(y) == 1 || (sgn(y) == 0 && sgn(x) >= 0); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const { return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

typedef double PType;
typedef Point<PType> P;

// Line ps[0] -> ps[1], currently used on halfplaneIS only
struct L{ 
	P ps[2];
	P& operator[](int i) { return ps[i]; }
	P dir() { return ps[1] - ps[0]; }
	L (P a,P b) {
		ps[0]=a;
		ps[1]=b;
	}
	bool include(P p) { return sgn((ps[1] - ps[0]).cross(p - ps[0])) > 0; }
	L push(){ // push eps outward
		const double eps = 1e-8;
		P delta = (ps[1] - ps[0]).perp().unit() * eps;
		return {ps[0] + delta, ps[1] + delta};
	}
};

bool parallel(L l0, L l1) { return sgn( l0.dir().cross( l1.dir() ) ) == 0; }
bool sameDir(L l0, L l1) {
	return parallel(l0, l1) && sgn(l0.dir().dot(l1.dir()) ) == 1;
}
