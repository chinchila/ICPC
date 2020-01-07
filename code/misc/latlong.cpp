//LatLong <-> rectangular
struct latlong {
  double r, lat, lon;
};
struct rect {
  double x, y, z;
};
latlong convert( rect &P ) {
	latlong Q;
	Q.r = sqrt( P.x * P.x + P.y * P.y + P.z * P.z );
	Q.lat = 180 / M_PI * asin( P.z / Q.r );
	Q.lon = 180 / M_PI * acos( P.x/sqrt( P.x * P.x + P.y * P.y ) );
	return Q;
}

rect convert( latlong &Q )
{
	rect P;
	P.x = Q.r * cos( Q.lon * M_PI / 180 ) * cos( Q.lat * M_PI / 180 );
	P.y = Q.r * sin( Q.lon * M_PI / 180 ) * cos( Q.lat * M_PI / 180 );
	P.z = Q.r * sin( Q.lat * M_PI / 180 );
	return P;
}
