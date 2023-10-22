/**
 *  Author: shaosy
 * Description:  Sort all node through degree from large to small. Only the edge
 * from the higher focus to the lower focus is counted. Bruteforce count $v,w$,
 * then $O(1)$ check whether $w$ is connected with $u$. Total time complexity is
 * Time: O(n\sqrt{n})
 */
for (int i = 0; i < n; ++i) {
  int u = rev[i];
  for (auto v : E[u]) if (id[v] < id[u]) f[v]++;
  for (auto v : E[u]) if (id[v] < id[u])
    for (auto w : E[v]) if (id[w] < id[v])
      ans += f[w];
  for (auto v : E[u]) if (id[v] < id[u]) f[v]--;
}