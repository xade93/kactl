/**
 * Author: shaosy
 * Description: for edge $u, v$, the flow should satisfy: $b(u,v)
 * \leq f(u,v) \leq c(u,v)$, in which $b(u,v)$ is the lower bound and $c(u,v)$
 * is the upper bound. For feasible flow without sink and source, if $ans =
 * \sum_{d[i] > 0} d[i] = \sum_{d[i] < 0} -d[i]$, there exist a feasible flow.
 * The exact flow in each edge is the sum of the flow in the graph and the lower
 * bound the the edge. Otherwise, there's no solution. If we want to calculate
 * maximum flow, we should note that for any feasible flow, running maximum
 * flow algorithm, we can always get the correct answer. The base is the flow of
 * edge $t,s$. Then, we delete all edges added (including edge $t, s$) and run
 * maximum flow algorithm on the residual network. The answer is the maximum
 * flow add the base (feasible flow). For Minimum Flow with Sink and Source, we
 * should notice that $MinF(s, t) = - MaxF(t, s)$. Same as Maximum Flow, but the
 * answer is the base (feasible fow) minus the maximum flow of $t, s$.
 */
// Feasible Flow without Sink and Source
G.addEdge(u, v, R - L);
d[u] -= L, d[v] += L;
if (d[i] > 0) {
    G.addEdge(SS, i, d[i]);
} else if (d[i] < 0) {
    G.addEdge(i, TT, -d[i]);
}
auto ans = G.solve(SS, TT);
// Feasible Flow with Sink and Source only need to add edge t,s,inf
G.addEdge(t, s, inf)
// Maximum Flow with Sink and Source
auto base = G.edg[id ^ 1].f;
// delete all edges (set f to 0)
auto ans = G.solve(s, t) + base;
// Minimum Flow with Sink and Source
auto ans = base - G.solve(t, s);


