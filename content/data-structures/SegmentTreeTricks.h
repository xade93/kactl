/** 
 * Author: Shi Zhengyu
 * Description: Dynamic Segtree Ig
*/
struct segt {
    ll l, r;
    ll ans;
    ll lp, rp; // physical, for dynamic
} T[sz << 5];
ll nxtFreeNode = 2;

void expand(ll o) { // guarantee empty subchild exist for o. Do not do anything on ans; rely on zero-init for correctness
    if (T[o].l == T[o].r) return; // no need expansion
    else if (T[o].lp != 0) return; // already expanded
    else {
        ll m = T[o].l + T[o].r >> 1;

        T[o].lp = nxtFreeNode;
        T[nxtFreeNode].l = T[o].l, T[nxtFreeNode].r = m;
        nxtFreeNode++;

        T[o].rp = nxtFreeNode;
        T[nxtFreeNode].l = m + 1, T[nxtFreeNode].r = T[o].r;
        nxtFreeNode++;
    }
}

void update(ll o, ll pos, ll x) {
    expand(o);
    if (T[o].l == T[o].r) T[o].ans += x;
    else {
        ll m = T[o].l + T[o].r >> 1;
        if (pos <= m) update(T[o].lp, pos, x);
        else update(T[o].rp, pos, x);
    }
}