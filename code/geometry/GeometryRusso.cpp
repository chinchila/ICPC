const double EPS = 1e-9;


struct Point {
	double x, y;

	Point() {}
	Point(double x, double y) : x(x), y(y) {}
	Point(const Point &a, const Point &b) : x(b.x - a.x), y(b.y - a.y) {}

	double angle() const {
		double a = atan2(y, x);
		if (a < -EPS)
			a += 2 * acos(-1.0);
		return a;
	}
	double length() const {
		return sqrt(x * x + y * y);
	}
	double distanceTo(const Point &that) const {
		return Point(*this, that).length();
	}

	Point operator + (const Point &that) const {
		return Point(x + that.x, y + that.y);
	}
	Point operator - (const Point &that) const {
		return Point(x - that.x, y - that.y);
	}
	Point operator * (double k) const {
		return Point(x * k, y * k);
	}   
	Point setLength(double newLength) const {
		double k = newLength / length();
		return Point(x * k, y * k);
	}

	double dotProduct(const Point &that) const {
		return x * that.x + y * that.y;
	}   
	double angleTo(const Point &that) const {
		return acos(max(-1.0, min(1.0, dotProduct(that) / (length() * that.length()))));
	}   
	bool isOrthogonalTo(const Point &that) const {
		return fabs(dotProduct(that)) < EPS;
	}   
	Point orthogonalPoint() const {
		return Point(-y, x);
	}

	double crossProduct(const Point &that) const {
		return x * that.y - y * that.x;
	}
	bool isCollinearTo(const Point &that) const {
		return fabs(crossProduct(that)) < EPS;
	}
};


struct Line {
	double a, b, c;

	Line() {}
	Line(double a, double b, double c) : a(a), b(b), c(c) {}
	Line(const Point &p1, const Point &p2) : a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x * p2.y - p2.x * p1.y) {}
	static Line LineByVector(const Point &p, const Point &v) {
		return Line(p, p + v);
	}
	static Line LineByNormal(const Point &p, const Point &n) {
		return LineByVector(p, n.orthogonalPoint());
	}

	Point normal() const {
		return Point(a, b);
	}
	Line orthogonalLine(const Point &p) const {
		return LineByVector(p, normal());
	}   
	Line parallelLine(const Point &p) const {
		return LineByNormal(p, normal());
	}
	Line parallelLine(double distance) const {
		Point p = (fabs(a) < EPS ? Point(0, -c / b) : Point(-c / a, 0));
		Point p1 = p + normal().setLength(distance);
		return LineByNormal(p1, normal());
	}

	int side(const Point &p) const {
		double r = a * p.x + b * p.y + c;
		if (fabs(r) < EPS)
			return 0;
		else
			return r > 0 ? 1 : -1;
	}
	double distanceTo(const Point &p) const {
		return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
	}
	bool has(const Point &p) const {
		return distanceTo(p) < EPS;
	}

	double distanceTo(const Line &that) const {
		if (normal().isCollinearTo(that.normal())) {
			Point p = (fabs(a) < EPS ? Point(0, -c / b) : Point(-c / a, 0));
			return that.distanceTo(p);
		} else
			return 0;
	}   
	bool intersectsWith(const Line &that) const {
		return distanceTo(that) < EPS;
	}
	Point intersection(const Line &that) const {
		double d = a * that.b - b * that.a;
		double dx = -c * that.b - b * -that.c;
		double dy = a * -that.c - -c * that.a;
		return Point(dx / d, dy / d);
	}   
};


struct Ray {
	Point p1, p2;
	double a, b, c;

	Ray(const Point &p1, const Point &p2) : p1(p1), p2(p2), a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x * p2.y - p2.x * p1.y) {}
	
	double distanceTo(const Point &p) const {
		if (Point(p1, p).dotProduct(Point(p1, p2)) >= -EPS)
			return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
		else
			return p1.distanceTo(p);
	}
	bool has(const Point &p) const {
		return distanceTo(p) < EPS;
	}

	double distanceTo(const Ray &that) const {
		Line l(a, b, c), thatL(that.a, that.b, that.c);
		if (l.intersectsWith(thatL)) {
			Point p = l.intersection(thatL);
			if (has(p) && that.has(p))
				return 0;
		}
		return min(distanceTo(that.p1), that.distanceTo(p1));
	}
	bool intersectsWith(const Ray &that) const {
		return distanceTo(that) < EPS;
	}
};


struct Segment {
	Point p1, p2;
	double a, b, c;

	Segment(const Point &p1, const Point &p2) : p1(p1), p2(p2), a(p1.y - p2.y), b(p2.x - p1.x), c(p1.x * p2.y - p2.x * p1.y) {}
	
	double distanceTo(const Point &p) const {
		if (Point(p1, p).dotProduct(Point(p1, p2)) >= -EPS && Point(p2, p).dotProduct(Point(p2, p1)) >= -EPS)
			return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
		else
			return min(p1.distanceTo(p), p2.distanceTo(p));
	}
	bool has(const Point &p) const {
		return distanceTo(p) < EPS;
	}

	double distanceTo(const Segment &that) const {
		Line l(a, b, c), thatL(that.a, that.b, that.c);
		if (l.intersectsWith(thatL)) {
			Point p = l.intersection(thatL);
			if (has(p) && that.has(p))
				return 0;
		}
		return min(min(distanceTo(that.p1), distanceTo(that.p2)), min(that.distanceTo(p1), that.distanceTo(p2)));
	}   
	bool intersectsWith(const Segment &that) const {
		return distanceTo(that) < EPS;
	}
};


struct Polygon {
	vector<Point> points;
	void addPoint(const Point &p) {
		points.push_back(p);
	}
	double area() const {
		double s = 0;
		for (int i = 1; i < points.size(); i++)
			s += points[i - 1].crossProduct(points[i]);
		s += points[points.size() - 1].crossProduct(points[0]);
		return fabs(s) / 2;
	}
};
