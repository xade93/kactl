struct ZKWTree {
  int no[maxn << 2];
  int t;

  void build_tree(int n) {
    for(t = 1; t <= n; t <<= 1);
    for(int i = t + 1; i <= t + n; ++i) no[i] = aa[i - t];
    for(int i = t; i; --i) push_up(i);
  }

  inline void add(int pla, int x) {
    for(pla += t; pla; pla >>= 1) no[pla] += x;
  }

  inline int query(int l, int r) {
    int ans = 0;
    for(l += t - 1, r += t + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
      if(~l & 1) ans += no[l ^ 1];
      if(r & 1) ans += no[r ^ 1];
    }
    return ans;
  }
};
