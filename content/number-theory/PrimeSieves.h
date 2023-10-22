/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Linear Prime Sieve. Use FastEratosthenes.h if need low constant. 
 *  \textbf{For sieving range}: Each time store sqrt(n), 
 *  Sieve 1..sqrt(n) with regular sieve,
 *  For each further segs, just have to iterate over all primes in first seg and sieve in that range
 *      this is because all composite number have factor <= sqrt(n). Roughly O(n log log n)
 */

ector<ll> primes;
void sieve(ll sz) {
    deque<bool> np(sz + 2);
    FOR(i, 2, sz) {
        if (!np[i]) primes.emplace_back(i);
        for (auto e: primes) {
            if (i * e > sz) break;
            np[i * e] = true;
            if (i % e == 0) break;
        }
    }
}
