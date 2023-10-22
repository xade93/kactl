/**
 * Author: Shao Siyang
 * Date: 2023-03-09
 * Description: Alternative Divide and conquere DP
 */
function<void(ll, ll, ll, ll, ll)> dfs = [&](ll l, ll r, ll L, ll R, ll x) {
    if (l > r || L > R) return;
    ll mid = (l + r) / 2;
    ll pos = L;
    for (ll i = L; i <= min(R, mid); ++i) {
        if (dp[x][mid] > dp[x - 1][i - 1] + cost[i][mid]) {
            dp[x][mid] = dp[x - 1][i - 1] + cost[i][mid];
            pos = i;
        }
    }
    dfs(l, mid - 1, L, pos, x);
    dfs(mid + 1, r, pos, R, x);
};

// init
for (ll x = 1; x <= k; ++x) {
    // init
    dfs(1, n, 1, n, x);
}