/**
 * Author: shaosy
 * Description: Blossom tree
 */
#pragma once

struct blossom { 
  int n, vis_t;
  vector<vector<int>> E;
  vector<int> match, label, org, vis, parent;
  queue<int> Q;
  blossom(int _n)
      : n(_n), E(_n), match(_n, -1), label(_n), org(_n), vis(_n),
        parent(_n, -1) {
    iota(org.begin(), org.end(), 0);
    vis_t = 0;
  }
  void addEdge(int u, int v) {
    E[u].emplace_back(v);
    E[v].emplace_back(u);
  }
  auto lca(int v, int u) {
    vis_t++;
    while (true) {
      if (v != -1) {
        if (vis[v] == vis_t) {
          return v;
        }
        vis[v] = vis_t;
        if (match[v] == -1) {
          v = -1;
        } else {
          v = org[parent[match[v]]];
        }
      }
      swap(v, u);
    }
  }
  void agument(int v) {
    while (v != -1) {
      auto pv = parent[v];
      auto nxt = match[pv];
      match[v] = pv;
      match[pv] = v;
      v = nxt;
    }
  }
  void flower(int v, int u, int a) {
    while (org[v] != a) {
      parent[v] = u;
      u = match[v];
      if (label[u] == 1) {
        label[u] = 0;
        Q.emplace(u);
      }
      org[v] = org[u] = a;
      v = parent[u];
    }
  }
  auto bfs(int root) {
    fill(label.begin(), label.end(), -1);
    iota(org.begin(), org.end(), 0);
    while (!Q.empty()) {
      Q.pop();
    }
    Q.emplace(root);
    label[root] = 0;
    while (!Q.empty()) {
      auto u = Q.front();
      Q.pop();
      for (auto v : E[u]) {
        if (label[v] == -1) {
          label[v] = 1;
          parent[v] = u;
          if (match[v] == -1) {
            agument(v);
            return true;
          }
          label[match[v]] = 0;
          Q.push(match[v]);
          continue;
        } else if (label[v] == 0 && org[v] != org[u]) {
          auto a = lca(org[u], org[v]);
          flower(v, u, a);
          flower(u, v, a);
        }
      }
    }
    return false;
  }
  void solve() {
    for (int i = 0; i < n; ++i) {
      if (match[i] == -1) { // if match[i] == -1, no matching
        bfs(i);
      }
    }
  }
};