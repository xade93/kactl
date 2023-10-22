/**
 * Author: Shi Zhengyu
 * Description: Mo's Algorithm. 
 */

1. put queries into sqrt(n) blocks by their left end in O(q log q) / O(q) time.
2. for every block:
	a. sort all query by right end
	b. brute force from the first to last.

The complexity is O((N+Q) sqrt(N) * F), where O(F) is the complexity of add and remove function.

Complexity Analysis when push is not O(1):
	Left Push be done at most sqrt(n) *n times, worst case can be in n times per block;
	Right Push be done sqrt(n) * n, but worst can only sqrt(n) per block, visiting everything sqrt(n) times.
	if the right push is amortized O(1), it is also fine.(see Segment problems  Query number of segments fully intersect with given segment)