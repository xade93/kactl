/**
 * Author: shaosy
 * Description: SPFA. return false when has negative loop
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

bool spfa(int n, int s) {
  queue<int> Q;
  Q.emplace(s);
  dis[s] = 0, in_queue[s] = 1;
  while (!Q.empty()) {
    auto u = Q.front();
    Q.pop(), in_queue[u] = 0;
    for (auto [v, w] : E[u]) {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w, cnt[v] = cnt[u] + 1;
        if (cnt[v] >= n)
          return false;
        if (!in_queue[v])
          Q.emplace(v), in_queue[v] = 1;
      }
    }
  }
  return true;
}