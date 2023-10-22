/**
 * Author: Shi Zhengyu
 * Date: 2023-10-07
 * Description: High precision arithmetic over modules. Apparently better than 10-based, can be seen as a additive bitset. 
 */
// operations are in place. 
// 
using ull = unsigned long long;
template <ull n>
struct AdditiveBitset {
    vector<ull> v;
    AdditiveBitset() { v.resize(n / 32); }
    void ls1() {
        bool carry = false;
        for (ull i = 0; i < n / 32; ++i) {
            v[i] = (v[i] << 1) | carry;
            carry = (v[i] & (1ll << 32));
            v[i] %= (1ll << 32);
        }
    }
    void rs1() {
        ll carry = 0;
        for (ull i = n / 32 - 1; i >= 0; --i) {
            bool nc = v[i] & 1;
            v[i] = (v[i] >> 1) | (carry << 31);
            carry = nc;
            v[i] %= (1ll << 32);
        }
    }
    bool get(int x) { return v[x / 32] & (1 << (x % 32)); }
    void toggle(int x) { v[x / 32] ^= (1 << (x % 32)); }
    void add(AdditiveBitset& b) {
        bool carry = false;
        for (ull i = 0; i < n / 32; ++i) {
            v[i] = v[i] + b.v[i] + carry;
            carry = (v[i] & (1ll << 32));
            v[i] %= (1ll << 32);
        }
    }
    ll popcount() {
        ll ans = 0;
        for (ull i = 0; i < n / 32; ++i) {
            ans += __builtin_popcountll(v[i] % (1ll << 32));
        }
        return ans;
    }
    void multInt(ll x) {
        ll carry = 0;
        for (ull i = 0; i < n / 32; ++i) {
            v[i] = v[i] * x + carry;
            carry = v[i] >> 32;
            v[i] %= (1ll << 32);
        }
    }
};