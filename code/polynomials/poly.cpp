template <class T> using V = vector<T>;
using Mint = FF<998244353>;
template<int T> const FF<T> FF<T>::G = Mint(3);

template <class T> void nft(bool type, V<T>& a) {
    int n = int(a.size()), s = 0;
    while ((1 << s) < n) s++;
    assert(1 << s == n);

    static V<T> ep, iep;
    while (int(ep.size()) <= s) {
        ep.push_back(T::G.pow(T(-1).v / (1 << ep.size())));
        iep.push_back(ep.back().inv());
    }
    V<T> b(n);
    for (int i = 1; i <= s; i++) {
        int w = 1 << (s - i);
        T base = type ? iep[i] : ep[i], now = 1;
        for (int y = 0; y < n / 2; y += w) {
            for (int x = 0; x < w; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
}

template <class T> V<T> multiply(const V<T>& a, const V<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    int lg = 0;
    while ((1 << lg) < n + m - 1) lg++;
    int z = 1 << lg;
    auto a2 = a, b2 = b;
    a2.resize(z);
    b2.resize(z);
    nft(false, a2);
    nft(false, b2);
    for (int i = 0; i < z; i++) a2[i] *= b2[i];
    nft(true, a2);
    a2.resize(n + m - 1);
    T iz = T(z).inv();
    for (int i = 0; i < n + m - 1; i++) a2[i] *= iz;
    return a2;
}


template <class D> struct Poly {
    V<D> v;
    Poly(const V<D>& _v = {}) : v(_v) { shrink(); }
    void shrink() {
        while (v.size() && !v.back()) v.pop_back();
    }

    int size() const { return int(v.size()); }
    D freq(int p) const { return (p < size()) ? v[p] : D(0); }

    Poly operator+(const Poly& r) const {
        auto n = max(size(), r.size());
        V<D> res(n);
        for (int i = 0; i < n; i++) res[i] = freq(i) + r.freq(i);
        return res;
    }
    Poly operator-(const Poly& r) const {
        int n = max(size(), r.size());
        V<D> res(n);
        for (int i = 0; i < n; i++) res[i] = freq(i) - r.freq(i);
        return res;
    }
    Poly operator*(const Poly& r) const { return {multiply(v, r.v)}; }
    Poly operator*(const D& r) const {
        int n = size();
        V<D> res(n);
        for (int i = 0; i < n; i++) res[i] = v[i] * r;
        return res;
    }
    Poly operator/(const D &r) const{
        return *this * r.inv();
    }
    Poly operator/(const Poly& r) const {
        if (size() < r.size()) return {{}};
        int n = size() - r.size() + 1;
        return (rev().pre(n) * r.rev().inv(n)).pre(n).rev(n);
    }
    Poly operator%(const Poly& r) const { return *this - *this / r * r; }
    Poly operator<<(int s) const {
        V<D> res(size() + s);
        for (int i = 0; i < size(); i++) res[i + s] = v[i];
        return res;
    }
    Poly operator>>(int s) const {
        if (size() <= s) return Poly();
        V<D> res(size() - s);
        for (int i = 0; i < size() - s; i++) res[i] = v[i + s];
        return res;
    }
    Poly& operator+=(const Poly& r) { return *this = *this + r; }
    Poly& operator-=(const Poly& r) { return *this = *this - r; }
    Poly& operator*=(const Poly& r) { return *this = *this * r; }
    Poly& operator*=(const D& r) { return *this = *this * r; }
    Poly& operator/=(const Poly& r) { return *this = *this / r; }
    Poly& operator/=(const D &r) {return *this = *this/r;}
    Poly& operator%=(const Poly& r) { return *this = *this % r; }
    Poly& operator<<=(const size_t& n) { return *this = *this << n; }
    Poly& operator>>=(const size_t& n) { return *this = *this >> n; }

    Poly pre(int le) const {
        return {{v.begin(), v.begin() + min(size(), le)}};
    }
    Poly rev(int n = -1) const {
        V<D> res = v;
        if (n != -1) res.resize(n);
        reverse(res.begin(), res.end());
        return res;
    }
    Poly diff() const {
        V<D> res(max(0, size() - 1));
        for (int i = 1; i < size(); i++) res[i - 1] = freq(i) * i;
        return res;
    }
    Poly inte() const {
        V<D> res(size() + 1);
        for (int i = 0; i < size(); i++) res[i + 1] = freq(i) / (i + 1);
        return res;
    }

    // f * f.inv() = 1 + g(x)x^m
    Poly inv(int m) const {
        Poly res = Poly({D(1) / freq(0)});
        for (int i = 1; i < m; i *= 2) {
            res = (res * D(2) - res * res * pre(2 * i)).pre(2 * i);
        }
        return res.pre(m);
    }
    // exp(p(x)) mod x^n
    Poly exp(int n) const {
        assert(freq(0) == 0);
        Poly f({1}), g({1});
        for (int i = 1; i < n; i *= 2) {
            g = (g * 2 - f * g * g).pre(i);
            Poly q = diff().pre(i - 1);
            Poly w = (q + g * (f.diff() - f * q)).pre(2 * i - 1);
            f = (f + f * (*this - w.inte()).pre(2 * i)).pre(2 * i);
        }
        return f.pre(n);
    }
    // log(p(x)) mod x^n
    Poly log(int n) const {
        assert(freq(0) == 1);
        auto f = pre(n);
        return (f.diff() * f.inv(n - 1)).pre(n - 1).inte();
    }
    // sqrt(p(x)) mod x^n
    Poly sqrt(int n) const {
        assert(freq(0) == 1);
        Poly f = pre(n + 1);
        Poly g({1});
        for (int i = 1; i < n; i *= 2) {
            g = (g + f.pre(2 * i) * g.inv(2 * i)) / 2;
        }
        return g.pre(n + 1);
    }

    Poly pow_mod(LL n, const Poly& mod) {
        Poly x = *this, r = {{1}};
        while (n) {
            if (n & 1) r = r * x % mod;
            x = x * x % mod;
            n >>= 1;
        }
        return r;
    }

    friend ostream& operator<<(ostream& os, const Poly& p) {
        if (p.size() == 0) return os << "0";
        for (auto i = 0; i < p.size(); i++) {
            if (p.v[i]) {
                os << p.v[i] << "x^" << i;
                if (i != p.size() - 1) os << "+";
            }
        }
        return os;
    }
};