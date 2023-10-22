/**
 * Author: Shi Zhengyu
 * Date: 2022-12-08
 * License: CC0
 * Description: DSU. remember to init when use.
 * Time: $O(\alpha(N))$
 */
struct DSU {
    static const ll N = ;// TODO
    ll p[N + 2];
    DSU() { FOR(i, 1, N) p[i] = i; }
    ll find(ll a) {
        if (p[a] == a) return a;
        else return p[a] = find(p[a]);
    }
    void merge(ll a, ll b) {
        p[find(b)] = find(a);
    }
} ufs;