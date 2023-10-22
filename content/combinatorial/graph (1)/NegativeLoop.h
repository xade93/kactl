/**
 * Author: shaosy 
 * Description: Forced Full Flow for negative edges
 */
Primal_Dual<long long, long long> G(n + 2);
int ss = n, tt = n + 1;
long long ans = 0;
vector<long long> d(n);
for (int i = 0; i < m; ++i) {
  int x, y;
  long long f, v;
  cin >> x >> y >> f >> v;
  x--, y--;
  if (v >= 0) {
    G.addEdge(x, y, f, v);
  } else {
    G.addEdge(y, x, f, -v);
    ans += f * v;
    d[x] -= f;
    d[y] += f;
  }
}
for (int i = 0; i < n; ++i) {
  if (d[i] > 0) {
    G.addEdge(ss, i, d[i], 0);
  } else if(d[i] < 0) {
    G.addEdge(i, tt, -d[i], 0);
  }
}
auto [_, bs] = G.solve(ss, tt);
G.n -= 2;
auto [mx, mi] = G.solve(s, t);
cout << mx << " " << mi + bs + ans << "\n";