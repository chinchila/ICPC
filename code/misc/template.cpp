#include<bits/stdc++.h>
using namespace std;

#define mset( n, v ) memset( n, v, sizeof( n ) )
#define st first
#define nd second
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define pb push_back
#define eb emplace_back
#define PI 3.141592653589793238462643383279502884L
#define EPS 1e-9
#define mp make_pair
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()

typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli; 
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int main() {
	//fast cin/cout
	ios_base::sync_with_stdio( false );
	cin.tie( 0 );
	freopen("file.in", "r", stdin);
	ofstream fout ("area.out");
	ifstream fin ("area.in");

	// Ouput a specific number of digits past the decimal point,
    // in this case 5    
    cout.setf( ios::fixed ); cout << setprecision( 5 );
    cout << 100.0/7.0 << endl;
    cout.unsetf(ios::fixed);
    
    // Output the decimal point and trailing zeros
    cout.setf( ios::showpoint );
    cout << 100.0 << endl;
    cout.unsetf( ios::showpoint );
    
    // Output a '+' before positive values
    cout.setf( ios::showpos );
    cout << 100 << " " << -100 << endl;
    cout.unsetf( ios::showpos );
    
    // Output numerical values in hexadecimal
    cout << hex << 100 << " " << 1000 << " " << 10000 << dec << endl;
	return 0;
}

