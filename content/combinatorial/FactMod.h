/**
 * Author: shi zhengyu
 * Date: 2022-12-12
 * Description: Compute n! \% p in $O(log_p n)$. \\
 * Also Lucas's Theorem: $\binom{n}{k} \equiv \prod \binom{n_i}{k_i}$
 * Conventionally C(n, k) = 0 if k > n.
 * Corollary. C(m, n) \% p = 0 iff at least one digit of n > m.
 */
int factmod(int n, int p) {
    vector<int> f(p);
    f[0] = 1;
    for (int i = 1; i < p; i++)
        f[i] = f[i-1] * i % p;

    int res = 1;
    while (n > 1) {
        if ((n/p) % 2)
            res = p - res;
        res = res * f[n%p] % p;
        n /= p;
    }
    return res;
}
