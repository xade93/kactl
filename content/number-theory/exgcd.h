/**
 * Author: shi zhengyu
 * Description: Recall euclidean's correctness: 
 * $a, b \leftrightarrow a, b - a  \leftrightarrow a, b mod a \leftrightarrow b mod a, a$ \\
 * Also \textbf{ExGCD correctness}: $(x1, y1) \rightarrow (y1, x1 - y1 * (a / b))$ \\
 * Also \textbf{Diophantine correctness}: If $g | c$ fail, no solution (Bezout: linear combination of 2 number is always divisible by common divisior)  \\
 * Otherwise, solution is $a\cdot u_g + b \cdot u_g = g \rightarrow a\cdot (c/g * u_g) + \cdot (c/g \cdot v_g) = c$ \\
 * \textbf{All solutions} comes from $x=x_0+k\cdot \frac{b}{g}$ and $y=y_0-k\cdot \frac{a}{g}$ \\
 * i.e. $u + v = u_0 + v_0 + k \cdot \frac{b - a}{g}$ ie if $a < b$ we need min k, $a > b$ need max k, $a = b$ k irrelevant. \\
 * \textbf{Extend to negative} GCD is meaningful for $\mathbb{Z}$ by taking abs for its args. ExGCD does not work for neg args (since we are using primitive b % a). \\
 * so we just convert args to abs val \\
 * \textbf{All Answers} very complex as (1) intersection of segments (2) c++ round to 0 not floor (3) result have unobvious sign
 */

namespace Diophantine {
    ll floorDiv(ll x, ll y) {
        bool neg = (x < 0) ^ (y < 0); x = abs(x), y = abs(y);
        if (!neg) return x / y;
        else return - (x + y - 1) / y; // negation become ceil
    }

    ll ceilDiv(ll x, ll y) {
        bool neg = (x < 0) ^ (y < 0); x = abs(x), y = abs(y);
        if (!neg) return (x + y - 1) / y;
        else return - x / y; // negation become ceil
    }

    bool intersection(pair<ll, ll>& ret, pair<ll, ll> p1, pair<ll, ll> p2) {
        if (p1.first > p1.second || p2.first > p2.second) return false; // TODO maybe even throw error?
        ret = {max(p1.first, p2.first), min(p1.second, p2.second)};
        return (ret.first <= ret.second);
    }

    #define sgn(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))
    pair<ll, ll> exgcd_(ll a, ll b) {
        if (b == 0) return {1, 0};
        auto [x1, y1] = exgcd_(b, a % b);
        return {y1, x1 - y1 * (a / b)};
    }

    pair<ll, ll> exgcd(ll a, ll b) { // wrapper for mathematically correct under negative numers
        ll k1 = sgn(a), k2 = sgn(b);
        auto [u, v] = exgcd_(abs(a), abs(b));
        return {k1 * u, k2 * v};
    }

    bool diophantine(pair<ll, ll>& ret, ll a, ll b, ll c) {
        if (a == 0 && b == 0) {
            if (c == 0) {
                ret = {0, 0};
                return true;
            } else return false;
        }
        if (c % gcd(a, b) != 0) return false; // this make solution nonexist

        ll k = c / gcd(a, b);
        auto [u, v] = exgcd(a, b);
        ret = {u * k, v * k};
        return true;
    }


    // get the (continuous) solution parametrized by k, of diophantine equation with constraint on x and y.
    // does not work when a == 0 and b == 0.
    bool getDiophantineRanged(pair<ll, ll>& ret, ll a, ll b, ll c, pair<ll, ll> xConstraint, pair<ll, ll> yConstratint) {
        assert(a != 0 || b != 0); // for next line, actly these two lines should be done at input of data
        auto g = gcd(gcd(a, b), c); a /= g, b /= g, c /= g;

        auto [Lx, Rx] = xConstraint; auto [Ly, Ry] = yConstratint;

        pair<ll, ll> x0y0;
        bool dio = diophantine(x0y0, a, b, c);
        auto [x0, y0] = x0y0;
        if (!dio) return false;

        pair<ll, ll> k1 = {ceilDiv((b >= 0 ? Lx : Rx) - x0, b), floorDiv((b >= 0 ? Rx : Lx) - x0, b)};
        pair<ll, ll> k2 = {ceilDiv(y0 - (a >= 0 ? Ry : Ly), a), floorDiv(y0 - (a >= 0 ? Ly : Ry), a)};

        return intersection(ret, k1, k2);
    }

    void debugSolutions(ll a, ll b, ll c, pair<ll, ll> range) {
        auto g = gcd(gcd(a, b), c); a /= g, b /= g, c /= g;
        pair<ll, ll> x0y0;
        assert(diophantine(x0y0, a, b, c));
        auto [x0, y0] = x0y0;
        FOR(k, range.first, range.second) cout << "k = " << k << ", x = " << x0 + k * b << ", y = " << y0 - k * a << endl;
    }
}
