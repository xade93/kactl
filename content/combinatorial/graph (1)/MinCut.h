/**
 * Author: shaosy
 * Description: After running max-flow, the left side of a min-cut from $s$ to
 * $t$ is given by all vertices reachable from $s$, only traversing edges with
 * positive residual capacity. If want to Minimize Cutting Edge under
 * Minimum-Cut first. Then change full edge's capacity into 1, other edge's
 * capacity into inf, run minimum cut again. This time the answer is the minimum
 * cut edge number. If no need under Minimum-Cut, just simply Change all the
 * edge's capacity into 1
 */
function<void(int)> dfs = [&](int u) {
  vis[u] = 1;
  for (auto id : E[u]) {
    auto [_, v, f] = edg[id];
    if (f > 0 && !vis[v]) {
      dfs(v);
    }
  }
};
dfs(S);