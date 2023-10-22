/**
 * Author: Shi Zhengyu
 * Description: pow
 * Status: tested
 */
#pragma once
ll fp(ll a, ll b) {
    ll res = 1;
    for (; b; b /= 2, a *= a) if (b % 2) res *= a;
    return res;
}

ll fpm(ll a, ll b, ll p) {
    ll res = 1;
    for (; b; b /= 2, a = (a * a) % p) if (b % 2) res = (res * a) % p;
    return res;
}
