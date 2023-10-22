/**
 * Author: Shi Zhengyu
 * Date: 2022-12-08
 * License: CC0
 * Description: one indexed. for zero idx write special case for init(). Tested in NERC 2021 J.
 */
struct prefix2D {
	const static ll M = 200, N = 200; // TODO;
	ll a[M + 2][N + 2], pf[M + 2][N + 2];
	void init() {
		FOR(i, 1, M) FOR(j, 1, N) pf[i][j] = pf[i - 1][j] + pf[i][j - 1] - pf[i - 1][j - 1] + a[i][j];
	}
	ll sum(ll u, ll v, ll w, ll h) {
		// u, v must at topleft, w, h must at bottomright
		if (u > w || v > h) return 0;
		return pf[w][h] - pf[w][v - 1] - pf[u - 1][h] + pf[u - 1][v - 1];
	}
} p2d;

