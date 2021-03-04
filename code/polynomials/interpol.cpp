// find a polynomial given a list of points
// usage auto pol = InterPol<Type>(x).query(y);
// O(n*log^2(n))

#include "poly.cpp"
#include "multieval.cpp"

template <class T> using VV = V<V<T>>;

template <class T> struct InterPol {
    using Po = Poly<T>;
    VV<Po> que;
    Po s;
    int n, l;
    InterPol(const V<T>& _que) {
        n = int(_que.size());
        que.push_back(V<Po>(n));
        for (int i = 0; i < n; i++) {
            que[0][i] = {{-_que[i], 1}};
        }
        while (que.back().size() > 1) {
            int n2 = int(que.back().size());
            V<Po> nque((n2 + 1) / 2);
            for (int i = 0; i < n2 / 2; i++) {
                nque[i] = que.back()[2 * i] * que.back()[2 * i + 1];
            }
            if (n2 % 2) nque.back() = que.back().back();
            que.push_back(nque);
        }
        l = int(que.size());
        s = MultiEval<T>(_que).query(que.back()[0].diff());
    }
    Po query(const V<T>& ys) const {
        V<Po> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = {{ys[i] / s.freq(i)}};
        }
        for (int ph = 1; ph < l; ph++) {
            int n2 = int(que[ph - 1].size());
            V<Po> nres((n2 + 1) / 2);
            for (int i = 0; i < n2 / 2; i++) {
                nres[i] = res[2 * i] * que[ph - 1][2 * i + 1] +
                          res[2 * i + 1] * que[ph - 1][2 * i];
            }
            if (n2 % 2) nres.back() = res.back();
            res = nres;
        }
        return res[0];
    }
};