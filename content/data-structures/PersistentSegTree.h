/**
 * Author: shi zhengyu
 * Date: 2022-12-07
 * Description: persistent segment tree
 */
using ll = long long;
const ll N = 100000;
struct PersistentSegTree {
    vector<ll> lc, rc, val;
    ll cnt;
    PersistentSegTree(ll N) {
        ll v = N * 21;
        lc.resize(v), rc.resize(v), val.resize(v);
        cnt = 0;
    }
    void build(ll &o, ll l, ll r) {
        o = ++cnt;
        if (l == r) {
            val[o] = 0;  // TODO initial tree
            return;
        }
        ll mid = (l + r) >> 1;
        build(lc[o], l, mid), build(rc[o], mid + 1, r);
    }
    void ins(ll &o, ll pre, ll l, ll r, ll q,
             ll v) {  // o = retRoot, pre = prevRoot, l = 1, r = n, q =
                      // insert_pos, v = value
        o = ++cnt;
        lc[o] = lc[pre], rc[o] = rc[pre], val[o] = val[pre];
        if (l == r) {
            val[o] = v;
            return;
        }
        ll mid = (l + r) >> 1;
        if (q <= mid) ins(lc[o], lc[pre], l, mid, q, v);
        else ins(rc[o], rc[pre], mid + 1, r, q, v);

        val[o] = val[lc[o]] + val[rc[o]];
    }
    ll query(ll o, ll l, ll r, ll ql, ll qr) { // range query a single tree root.
        if (ql > qr) return 0;
        if (l == ql && r == qr) return val[o];
        ll mid = (l + r) >> 1;
        if (qr <= mid) return query(lc[o], l, mid, ql, qr);
        else if (ql > mid) return query(rc[o], mid + 1, r, ql, qr);
        else return query(lc[o], l, mid, ql, mid) + query(rc[o], mid + 1, r, mid + 1, qr);
    }
};
