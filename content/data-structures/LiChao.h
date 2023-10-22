/**
 * Author: Shi Zhengyu
 * Date: 2022-12-08
 * License: CC0
 * Description: Li chao segment tree. not rigorously tested. Only works in 64-bit as max. use min by default
 */

template <class Tp>
struct LiChaoSegtree {
    using pll = pair<Tp, Tp>;
    Tp f(pll& l, ll x) { // kx+b
        return l.first * x + l.second;
    }

    ll L, R; // support [L, R)
    vector<pll> T;

    LiChaoSegtree(ll l, ll r): L(l), R(r) { // [L, R) !!!!
        T.assign((r - l + 1) << 2, {0, 1e16}); // TODO change value; you can also abstract it out if have multiple tests
    }

    void insert(pll line, ll o = 1, ll l = LLONG_MAX, ll r = LLONG_MAX) {
        if (l == LLONG_MAX) l = L, r = R;
        ll m = (l + r) / 2;
        bool left = f(line, l) < f(T[o], l);
        bool mid  = f(line, m) < f(T[o], m);

        if (mid) swap(T[o], line); // best in center is kept. TODO think about it
        if (l == r - 1) return; // single leaf
        else if (left != mid) insert(line, o << 1, l, m); // since strongness switched, intersect at left
        else insert(line, o << 1 | 1, m, r);
    }

    Tp query(ll x, ll o = 1, ll l = LLONG_MAX, ll r = LLONG_MAX) {
        if (l == LLONG_MAX) l = L, r = R;
        ll m = (l + r) / 2;
        ll tval = f(T[o], x);
        if (l == r - 1) return tval;
        else if (x < m) return min(tval, query(x, o << 1, l, m));
        else return min(tval, query(x, o << 1 | 1, m, r));
    }
};

void solve() {
    LiChaoSegtree<ll> st(-1e5 - 1, 1e5 + 1);
    while (true) {
        ll mode; cin >> mode;
        if (mode == 1) {
            ll u, v; cin >> u >> v;
            st.insert({u, v});
        } else {
            ll x; cin >> x;
            cout << st.query(x) << endl;
        }
    }
}
