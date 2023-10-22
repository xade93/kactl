/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#pragma once

// Do maximum matching
for (auto i : lef) vis[i] = match[i] == -1;
stack<int> Q;
for (auto i : lef)
  if (vis[i])
    Q.emplace(i);
while (!Q.empty()) {
  auto u = Q.top();
  Q.pop();
  vis[u] = 1;
  for (auto v : E[u])
    if (match[v] != -1 && vis[v] == 0)
      vis[v] = 1, Q.emplace(match[v];)
}
for (auto i : lef)
  if (!vis[i]) ans.emplace_back(i);
for (auto i : rig)
  if (vis[i]) ans.emplace_back(i);