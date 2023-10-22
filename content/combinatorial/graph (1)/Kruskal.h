/**
 * Author: shaosy
 * Description: When connect $u, v$, find there represent point $U, V$, create
 * new node $C$ which $w_c = w_{u, v}$ and connect $C\to U$ and $C \to V$. We
 * will get a rooted tree $T$ which has $2n-1$ nodes. $T$ is a binary tree. All
 * the nodes in $G$ is leaf node in $T$. For node $u$ and it's ancestor $v$,
 * $w_u \leq w_v$, which means point the points which point $x$ can reach using
 * edges with weight $\leq d$ is the subtree for the ancestor $a$ ($w_a \leq d$)
 * for $x$.
 *
 */