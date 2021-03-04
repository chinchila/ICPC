// Solves for a polynomial f(x) = sum c_i *x^i from 0 to n-1
// f(x_1), f(x_2), ..., f(x_m)
// O(n*log^2(n))
// Usage:
// auto pol = Poly<T>(c);
// auto multi_eval = MultiEval<T>(p);
// auto answer = multi_eval.query(pol);

#include "poly.cpp"

template <class T> struct MultiEval {
    using NP = MultiEval*;
    NP l, r;
    V<T> que;
    int sz;
    Poly<T> mul;
    MultiEval(const V<T>& _que, int off, int _sz) : sz(_sz) {
        if (sz <= 100) {
            que = {_que.begin() + off, _que.begin() + off + sz};
            mul = {{1}};
            for (auto x : que) mul *= {{-x, 1}};
            return;
        }
        l = new MultiEval(_que, off, sz / 2);
        r = new MultiEval(_que, off + sz / 2, sz - sz / 2);
        mul = l->mul * r->mul;
    }
    MultiEval(const V<T>& _que) : MultiEval(_que, 0, int(_que.size())) {}
    void query(const Poly<T>& _pol, V<T>& res) const {
        if (sz <= 100) {
            for (auto x : que) {
                T sm = 0, base = 1;
                for (int i = 0; i < _pol.size(); i++) {
                    sm += base * _pol.freq(i);
                    base *= x;
                }
                res.push_back(sm);
            }
            return;
        }
        auto pol = _pol % mul;
        l->query(pol, res);
        r->query(pol, res);
    }
    V<T> query(const Poly<T>& pol) const {
        V<T> res;
        query(pol, res);
        return res;
    }
};