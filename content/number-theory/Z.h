/**
 * Author: jiangly
 * Date: 2023-11-18
 * License: CC0
 * Description: jiangly's Z
 */

const ll p = 998244353; // TODO check if need __int128 for your modulus
ll norm(ll x) {
    x = (x % p + p) % p;
    return x;
}

template<class T>
T power(T a, ll b) {
    T res = 1; for (; b; b /= 2, a *= a) if (b % 2) res *= a;
    return res;
}

struct Z {
    ll x;
    ll normFast(ll t) {
        if (t >= p) return t - p;
        if (t < 0) return t + p;
        return t;
    }
    Z(ll t = 0) : x(norm(t)) {}
    ll val() const { return x; }
    Z operator-() const { return Z(norm(p - x)); }
    Z inv() const { assert(x != 0); return power(*this, p - 2); }
    Z &operator*=(const Z &rhs) { x = ll(x) * rhs.x % p; return *this; }
    Z &operator+=(const Z &rhs) { x = normFast(x + rhs.x); return *this; }
    Z &operator-=(const Z &rhs) { x = normFast(x - rhs.x); return *this; }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z &lhs, const Z &rhs) { Z res = lhs; res *= rhs; return res; }
    friend Z operator+(const Z &lhs, const Z &rhs) { Z res = lhs; res += rhs; return res; }
    friend Z operator-(const Z &lhs, const Z &rhs) { Z res = lhs; res -= rhs; return res; }
    friend Z operator/(const Z &lhs, const Z &rhs) { Z res = lhs; res /= rhs; return res; }
};