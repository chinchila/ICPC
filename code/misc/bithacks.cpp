// http://www.graphics.stanford.edu/~seander/bithacks.html

template <class T, class X> inline bool getbit(T a, X i) { T t = 1; return ((a & (t << i)) > 0);}
template <class T, class X> inline T setbit(T a, X i) { T t = 1; return (a | (t << i)); }
template <class T, class X> inline T resetbit(T a, X i) { T t = 1; return (a & (~(t << i)));}

__builtin_ctz(x) // trailing zeroes
__builtin_clz(x) // leading zeroes
__builtin_popcount(x) // # bits set
__builtin_ffs(x) // index(LSB) + 1 [0 if x==0]

bool powerOfTwo( int n ) {
	return n && !( n & ( n - 1 ) );
}

bool opositeSigns( int x, int y ) {
	return ( ( x ^ y ) < 0 );
}

// f true = set, false = clear | m is the bits to change
int changeBit( int n, bool f, int m ) {
	return n = ( n & ~m ) | ( -f & m );
}

//32 bits only (log n)
int reverseBits( int n ) {
	unsigned int s = sizeof( n ) * CHAR_BIT;
	unsigned int mask = ~0;         
	while ( ( s >>= 1 ) > 0 ) 
	{
		mask ^= ( mask << s );
		v = ( ( v >> s ) & mask ) | ( ( v << s ) & ~mask );
	}
	return n;
}

// Round to next power of two (32 bits)
int roundUpP2( int v ) {
	if( v > 1 ) {
		float f = (float)v;
		int const t = 1U << ( ( *( int * ) & f >> 23 ) - 0x7f );
		return t << ( t < v );
	}
	else return 1;
}

// interleave bits, x is even, y is odd (x,y less than 65536)
int interleave( int x, char y ) {
	int z = 0;
	for( int i = 0; i < sizeof(x) * CHAR_BIT; ++i )
		z |= ( x & 1U << i ) << i | ( y & 1U << i ) << ( i + 1 );
	return z;
}

// v is the current permutation (lexicographically)
int next_permutation_bit( int v ) {
	int t = v | (v - 1);
	return( t + 1 ) | ( ( ( ~t & -~t ) - 1 ) >> ( __builtin_ctz( v ) + 1 ) );
}

// check if a word has a byte equal to n
#define hasvalue(x,n) (haszero((x) ^ (~0UL/255 * (n))))
// check if a word has a byte less than n (hasless(n,1) to check if it has a zero byte)
#define hasless(x,n) (((x)-~0UL/255*(n))&~(x)&~0UL/255*128)
// check if a word has a byte greater than n
#define hasmore(x,n) (((x)+~0UL/255*(127-(n))|(x))&~0UL/255*128)

