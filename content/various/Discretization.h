/**
 * Author: Shi Zhengyu
 * Date: 2022-12-08
 * License: CC0
 * Description: Discretization, two ways of writing it.
 */


//1-index, vectors
vi b = a;
sort(b.begin() + 1, b.end());
b.erase(unique(b.begin() + 1, b.end()), b.end()); // there is no need to do unique actually lol jiangly don't 
// then you can iterate over b, having map<ll, ll> zip, unzip.


struct IntegerDisc {
    vector<ll> vecs;
    vector<ll> dedup;
    void init() {
        vecs.clear();
        dedup.clear();
    }
    void insert(ll v) { vecs.emplace_back(v); }
    void discretize() {
        sort(vecs.begin(), vecs.end());
        
        for (auto e: vecs) {
            while (!dedup.empty() && dedup.back() == e) dedup.pop_back();
            dedup.emplace_back(e);
        }
    }
    // assume x is in vecs; zero index.
    ll query(const ll v) {
        auto pos = lower_bound(dedup.begin(), dedup.end(), v);
        return pos - dedup.begin();
    }
};

struct FloatDisc {
    vector<ld> vecs;
    vector<ld> dedup;
    void init() {
        vecs.clear();
        dedup.clear();
    }
    void insert(ld v) { vecs.emplace_back(v); }
    void discretize() {
        sort(vecs.begin(), vecs.end());
        
        for (auto e: vecs) {
            while (!dedup.empty() && EQ(dedup.back(), e)) dedup.pop_back();
            dedup.emplace_back(e);
        }
    }
    // assume x is in vecs; zero index.
    ll query(const ld v) {
        auto pos = lower_bound(dedup.begin(), dedup.end(), v);
        if (pos != dedup.begin() && abs(*prev(pos) - v) < abs(*pos - v)) pos = prev(pos);
        return pos - dedup.begin();
    }
};