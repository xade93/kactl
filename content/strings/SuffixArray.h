/**
 * Author: pupu
 * Description: suffix array
 */

struct SuffixArray {
    static const int N = 1000005; // the length of the string

    int n, m, cnt[N], sa[N], rk[N], id[N];

    void radixSort() {
        for (int i = 0; i < m; ++i) {
            cnt[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            ++cnt[rk[i]];
        }
        for (int i = 1; i < m; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; ~i; --i) {
            sa[--cnt[rk[id[i]]]] = id[i];
        }
    }

    bool cmp(int x, int y, int l) {
        return id[x] == id[y] && id[x + l] == id[y + l];
    }

    template<typename T>
    void initSA(T first, T last) {
        n = last - first, m = 0;
        for (int i = 0; i < n; ++i) {
            rk[i] = *(first + i);
            m = std::max(m, rk[i] + 1);
            id[i] = i;
        }
        radixSort();
        for (int l = 1, p = 0; p < n && l < n; m = p, l <<= 1) {
            p = 0;
            for (int i = n - l; i < n; ++i) {
                id[p++] = i;
            }
//            std::cout << "p = " << p << ' ' << l << std::endl;
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= l && p < n) {
                    id[p++] = sa[i] - l;
                }
            }
            radixSort();
            for (int i = 0; i < n; ++i) id[i] = rk[i];
            p = 1, rk[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                if (!cmp(sa[i - 1], sa[i], l) && p < n) ++p;
                rk[sa[i]] = p - 1;
            }
        }
    }
} SA;
