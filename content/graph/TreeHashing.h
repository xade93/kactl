/**
 * Author: shaosy
 * Description: $hash_{now} = 1 + \sum f(hash(son_i))$. In which $f$ is a random
 * function (but could not be polynomial). Hash Collision is $O(n^2/2^w)$. Magic
 * number in $h$ can be replaced.
 *
 */
ll h(ll x) { return x * x * x * 156007 + 995669; }
ll f(ll x) { return h(x & ((1LL << 31) - 1)) + h(x >> 31); }