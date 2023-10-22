/**
 * Author: shi zhengyu
 * Date: 2022-12-08
 * Description: Caution: cannot use x, y, use cout for debug, beware of the expected bugs: norm(); complex<ll>; always use ll / ld for T not integers.\\
    Before Use: modify EPS \\
    Notice: angle is in [-pi, pi], remainder(x, 2 M\_PI) for remainder in <cmath> to [-pi, pi] \\
	Conversion to other types: <ll> works fine against local and CF gcc; tested in nwerc21f \\
    Input: pt(a, b); cin >> pt only works for a+bi afaik \\
    cannot use map unordered\_map consider convert to pair for that \\
    Calculate precision and adjust EPS accordingly; sometimes this is nontrivial;  \\
    there is no unsi gned long double, so if EPs is very small, consider use integer arithmetic, or change the variable you are storing. 
*/

namespace Geometry {
    using T = ld;
    using pt = complex<T>;
    #define x real()
    #define y imag()

    // basic operations

    #define dot(a, b) (conj(a) * (b)).x
    #define cross(a, b) (conj(a) * (b)).y
    #define dist_2(a, b) norm((a) - (b)) // beware precision loss bug in C++
    #define dist(a, b) abs((a) - (b))
    #define sign_area(a, b, c) (cross((b) - (a), (c) - (b))) // negative if c is rhs of AB (clockwise), zero if collinear; do not use thumb rule
    #define a_norm(a) (remainder(a, 2.0 * M_PI))

    // extra functions
    #define slope(a, b) arg((b) - (a))
    #define project_vec(p, a) ((v) * dot(p, v) / norm(v))
    #define project(p, a, b) ((a) + ((b) - (a)) * dot((p) - (a), (b) - (a)) / norm((b) - (a)))
    #define reflect(p, a, b) ((a) + conj(((p) - (a)) / ((b) - (a))) * ((b) - (a)))
    #define rotate(x, base, theta) (((x) - (base)) * polar(1.0, theta) + (base))
    #define angDiff(a, b, base) (a_norm(arg(a - base) - arg(b - base))) // positive angle yield by letting a "counter clockwise" from b. i.e. a is at left if y > 0. think a bout it.
    // floating point
    #define EPS 1e-12
    #define EQ(a, b) (fabs((a) - (b)) < EPS)

    bool clockwise(pt a, pt b, pt c, bool include_collinear) {
        T o = sign_area(a, b, c);
        return ((EQ(o, 0) && include_collinear) || (!EQ(o, 0) && o < 0));
    }

    // noncolinear tested on Kattis, Codeforces and Luogu; Luogu C++17 O2 wa/re for some reason.
    // colinear not rig. tested
    vector<pt> convexHull(vector<pt>& v, bool include_collinear = false) {
        assert(!v.empty());
        pt p0 = *min_element(v.begin(), v.end(), [](pt a, pt b) {
            return make_pair(a.y, a.x) < make_pair(b.y, b.x);
        });
        sort(v.begin(), v.end(), [&p0](const pt& a, const pt& b) {
            T o = sign_area(p0, a, b);
            if (a == b) return false;
            if (!EQ(o, 0)) return o < 0; // clockwise
            else return dist(p0, a) < dist(p0, b); 
        });
        if (include_collinear) {
            ll i = (ll)v.size() - 1;
            while (i >= 0 && EQ(sign_area(p0, v[i], v.back()), 0)) i--;
            reverse(v.begin() + i + 1, v.end());
        }

        vector<pt> ret;
        ll n = v.size();
        FOR(i, 0, n - 1) {
            while (ret.size() >= 2 && !clockwise(ret[ret.size() - 2], ret[ret.size() - 1], v[i], include_collinear)) ret.pop_back();
            ret.push_back(v[i]);
        }
        return ret;
    }

    // tested in Kattis
    T circum(vector<pt>& v) {
        T ans = 0;
        for (int i = 0; i <= (signed)v.size() - 2; ++i) ans += dist(v[i], v[i + 1]);
        ans += dist(v[0], v.back());
        return ans;
    }

    vector<pt> minkowski(vector<pt>& v1, vector<pt>& v2) {
        assert(v1.size() >= 2 && v2.size() >= 2);
        auto reorderPolygon = [](vector<pt>& P) {
            ll pos = 0;
            for (ll i = 1; i < P.size(); ++i) if (P[i].y <= P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
            rotate(P.begin(), P.begin() + pos, P.end());
        };
        reorderPolygon(v1), reorderPolygon(v2);

        // cyclic
        v1.push_back(v1[0]), v1.push_back(v1[1]);
        v2.push_back(v2[0]), v2.push_back(v2[1]);

        vector<pt> ans;
        ll i = 0, j = 0;
        while (i < v1.size() - 2 || j <= v2.size() - 2) {
            ans.push_back(v1[i] + v2[i]);
            auto cross = cross(v1[i + 1] - v1[i], v2[i + 1] - v2[i]);
            if (EQ(cross, 0)) ++i, ++j;
            else if (cross > 0) ++i;
            else ++j;
        }
        return ans;
    }
}