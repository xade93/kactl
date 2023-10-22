/**
 * Author: Shi Zhengyu
 * Date: 2022-12-07
 * License: CC0
 * Description: see top for advice
 */
struct SegmentTree {
    struct segt{
        ll l, r;
        ll ans; 
    };
    vector<segt> T;
    
    SegmentTree(ll n) { // don't forget to call build.
        T.resize(n << 2);
    }

    segt combine(segt l, segt r) {
        segt res; res.l = l.l, res.r = r.r;    
        res.ans = max(l.ans, r.ans);// TODO
        return res;
    }

    void build(ll l, ll r, ll o = 1) {
        T[o].l = l, T[o].r = r;
        if (l == r) T[o].ans = a[l]; // TODO
        else {
            ll m = (l + r) >> 1;
            build(l, m, o << 1), build(m+1, r, o << 1 | 1);
            T[o] = combine(T[o << 1], T[o << 1 | 1]);
        }
    }

    segt query(ll l, ll r, ll o = 1) {
        assert(l <= r);
        if (T[o].l == l && T[o].r == r) return T[o];
        else {
            ll m = (T[o].l + T[o].r) >> 1;
            if (r <= m) return query(l, r, o << 1);
            else if (l >= m+1) return query(l, r, o << 1 | 1);
            return combine(query(l, m, o << 1), query(m + 1, r, o << 1 | 1));
        }
    }

    void update(ll tx, ll nx, ll o = 1) { // singly update
        if (T[o].l == T[o].r) // TODO
        else {
            ll m = (T[o].l + T[o].r) >> 1;
            if (tx <= m) update(tx, nx, o << 1);
            else update(tx, nx, o << 1 | 1);
            T[o] = combine(T[o << 1], T[o << 1 | 1]);
        }
    }
}