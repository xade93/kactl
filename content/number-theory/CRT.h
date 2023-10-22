/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * 
 * \textbf{General Case}:
 * 	You have $a\equiv a_i \mod p_i$,  you can express ans as $a=x_1+x_2p_1+x_3p_1p_2 +...+x_kp_1...p_{k-1}$. \\
 *  Substitute into CRT, and solve for x yield e.g. $x_3=((a_3-x_1)r_{13}-x_2)r_{23}$. This is $O(k ^ 2)$. 
 * Time: $\log(n)$
 * Status: Works
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}
