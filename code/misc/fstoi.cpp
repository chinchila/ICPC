// O(n)
int fstoi( const char * str ) {
	int val = 0;
	while( *str ) val = val * 10 + ( *str++ - '0' );
	return val;
}

