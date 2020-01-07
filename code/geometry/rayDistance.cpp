// ray = semi-reta
#define EPS 1e-6
double rayDist(const P &p, P p1, P p2) {
	double a = p1.y - p2.y, b = p2.x - p1.x, c = p1.x * p2.y - p2.x * p1.y;
    if (P(p1, p).dot(P(p1, p2)) >= -EPS)
        return fabs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
    else
        return P(p1, p).dist();
}
