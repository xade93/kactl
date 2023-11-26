/**
 * Author: xade, szaranczuk
 * Date: 2023-11-27
 * License: CC0
 * Source: https://codeforces.com/blog/entry/112346
 * Description: Compute $d_k=\sum_{gcd(i,j)=k} a_i \cdot b_j$ for array of size
 * n in $O(n log n)$. Status: Untested
 */
#pragma once

template <typename T>
vector<T> gcdConvolution(vector<T> a, vector<T> b, T mod) {
    int n = a.size();
    vector<T> A(n), B(n), D(n);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j += i + 1) {
            A[i] += a[j], B[i] += b[j];
            A[i] %= mod, B[i] %= mod;
        }
        D[i] = A[i] * B[i], D[i] %= mod;
    }
    vector<T> d(n);
    for (int i = n - 1; i >= 0; i--) {
        d[i] = D[i];
        for (int j = 2 * i + 1; j < n; j += i + 1) {
            d[i] -= d[j], d[i] = (d[i] + mod) % mod;
        }
    }
    return d;
}