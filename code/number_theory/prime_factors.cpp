// Find all prime factors | O(n^1/3) ?
// here we find the smallest finite base of a fraction a/b
#define ll long long
int main() {
    scanf("%lld %lld", &a, &b);
 
    ll g = __gcd(a, b);
    b /= g;
 
    cur = b;
    for(ll i = 2; i <= cbrt(cur); i++) {
        if(cur % i == 0) {
            ans *= i;
            while(cur % i == 0) cur /= i;
        }
    }
 
    ll sq = round(sqrt(cur));
    if(sq * sq == cur) cur = sq;
 
    printf("%lld\n", max(2LL, ans * cur));
    return 0;
}
