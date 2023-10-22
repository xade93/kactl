/**
 * Author: shaosy
 * Description: A directed graph, each node has a value. Choose a subgraph with
 * maixmum sum value, in which each node's conected point is also in the
 * subgraph. Use minimum cut. Connect $S$ with every point with positive value
 * (weight is $val_i$), and every negative value with $T$ (weight is $-val_i$).
 * All edges in the graph's weight is $inf$. The subgraph is the point connected
 * with $S$ after minimum cut, and the sum is sum of positive points - minimum
 * cut.
 *
 */