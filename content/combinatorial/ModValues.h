/**
 * Author: Shi Zhengyu
 * Description: Pre-computation of modular combinatorial entities.
 */
const ll p = , sz = ;

ll fac[sz + 2], invfac[sz + 2], inv[sz + 2];
#define M(x) (((x)%p + p) % p)

void preprocess() {
    inv[1] = 1;
    FOR(i, 2, sz) inv[i] = p - (p / i) * inv[p % i] % p;

    fac[0] = invfac[0] = 1;
    FOR(i, 1, sz) fac[i] = M(fac[i-1] * i), invfac[i] = invfac[i - 1] * inv[i] % p;
}

ll c(ll n, ll k) {
    if (k > n) return 0;
    return (fac[n] * invfac[k] % p * invfac[n - k] % p);
}

ll A(ll n, ll k) {
    if (k > n) return 0;
    return (fac[n] * invfac[n - k] % p);
}

ll inv(ll a, ll p) { // for one time usage
    return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
}
