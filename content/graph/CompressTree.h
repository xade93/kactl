/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns a list of (par, orig\_index) representing a tree rooted at 0.
 * The root points to itself.
 * Time: $O(|S| \log |S|)$
 * Status: Tested at CodeForces
 */
#pragma once

#include "HLD.h"

struct virtual_tree {
  heavy_light_decomposition &G;
  vector<vector<int>> E;
  virtual_tree(heavy_light_decomposition &ptr) : G(ptr), E(ptr.n){};
  void build(vector<int> &node) {
    sort(node.begin(), node.end(),
         [&](int x, int y) { return G.dfn[x] < G.dfn[y]; });
    E[0].clear();
    stack<int> st;
    st.emplace(0);
    for (auto x : node) {
      E[x].clear();
      int top = G.lca(x, st.top());
      if (top == st.top()) {
        st.emplace(x);
        continue;
      }
      auto u = st.top();
      st.pop();
      while (!st.empty() && G.dep[st.top()] > G.dep[top]) {
        E[st.top()].emplace_back(u);
        u = st.top();
        st.pop();
      }
      if (!st.empty() && top == st.top()) {
        E[top].emplace_back(u);
      } else {
        E[top].clear();
        E[top].emplace_back(u);
        st.emplace(top);
      }
      st.emplace(x);
    }
    int u = st.top();
    st.pop();
    while (!st.empty()) {
      E[st.top()].emplace_back(u);
      u = st.top();
      st.pop();
    }
  }
};
