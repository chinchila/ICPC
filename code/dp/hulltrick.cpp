struct L {
    mutable ll a, b, p;
    bool operator<(const L &rhs) const { return a < rhs.a; }
    bool operator<(ll x) const { return p < x; }
	bool operator>(const L &rhs) const { return a > rhs.a; }
    bool operator>(ll x) const { return p < x; }
};
// change less to greater or operators as you need min or max
// if double change inf to a bigger number and div to a/b
struct DynamicHull : multiset<L, less<>> {
    static const ll kInf = 1e18;
	ll eval(L l, ll x){ return l.a*x + l.b; }
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool inter(iterator x, iterator y) {
        if (y == end()) { x->p = kInf; return false; }
        if (x->a == y->a) x->p = x->b > y->b ? kInf : -kInf;
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(ll a, ll b) {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (inter(y, z)) z = erase(z);
        if (x != begin() && inter(--x, y)) inter(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) inter(x, erase(y));
    }
    ll get(ll x) {
        auto l = *lower_bound(x);
        return eval(l, x);
    }
};