// solve ODE O(n)
#define EPS 1e-5
double runge_kutta(double (*f)(), double t, double tend, double x) {
	for( double h = EPS; t < tend; ) {
		if( t + h >= tend ) h = tend - t;
		double k1 = h * f( t, x );
		double k2 = h * f( t + h/2, x + k1/2 );
		double k3 = h * f( t + h/2, x + k2/2 );
		double k4 = h * f( t + h  , x + k3);
		x += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		t += h;
	}
	return x;
}
