/**
 * Author: shi zhengyu
 * Description: Multiplicative Sieve; default to euler phi
 */

const ll N = ;
vl primes; bool isComposite[N + 2];
ll f[N + 2], cnt[N + 2];

ll fastpow(ll a, ll n) {
	if (n == 0) return 1;
	ll ans = fastpow(a, n/2); ans *= ans;
	if (n % 2) ans *= a;
	return ans;
}
// need to define it for all prime p, f(p ^ k) AND f(1).
// BUT f(1) = 1 ALWAYS, since 1 coprime with any k, hence f(k) = f(1)f(k).
// hence need f(p ^ k) only.
ll fBase(ll p, ll k) {
    // TODO: return f(p ^ k) where p is a prime.
    // Mobius Func: [k = 0] - [k = 1].
    return fastpow(p, k) - fastpow(p, k - 1);
}

void sieve() {
    f[1] = 1;
    FOR(i, 2, N) {
        if (!isComposite[i]) {
            primes.eb(i);
            f[i] = fBase(i, 1), cnt[i] = 1;
        } // otherwise, f[i] and cnt[i] were already determined.
        for(auto p: primes) {
            if (p * i > N) break;
            isComposite[p * i] = true;
            if (i % p == 0) {
                cnt[i * p] = cnt[i] + 1;
                // f(i * p) = f(i / p^cnt[i]) * f(p^(cnt[i] + 1))
                f[i * p] = fBase(p, cnt[i * p]) * f[i / fastpow(p, cnt[i])];
                break;
            }else {
                cnt[i * p] = 1;
                f[i * p] = f[i] * f[p];
            }
        }
    }
}