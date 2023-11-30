/**
 * Author: pufanyi
 * Description: LCT
 */
class LCT {
  // node
  
 public:
  int sum[maxn], val[maxn];
  int s[maxn][2], fa[maxn];
  
 private:
  bool lzy_fan[maxn];
  
  void push_up(int x) { sum[x] = val[x] ^ sum[s[x][0]] ^ sum[s[x][1]]; }
  
  bool nrt(int x) { return s[fa[x]][0] == x || s[fa[x]][1] == x; }
  
  void fan(int x) {
    swap(s[x][0], s[x][1]);
    lzy_fan[x] ^= 1;
  }
  
  void push_down(int x) {
    if (lzy_fan[x]) {
      if (s[x][0]) fan(s[x][0]);
      if (s[x][1]) fan(s[x][1]);
      lzy_fan[x] = 0;
    }
  }
  
  // splay
 private:
  void rotate(int x) {
    int y = fa[x], z = fa[y];
    int k = (s[y][1] == x), ss = s[x][!k];
    if (nrt(y)) {
      s[z][s[z][1] == y] = x;
    }
    fa[x] = z;
    s[x][!k] = y;
    fa[y] = x;
    s[y][k] = ss;
    if (ss) {
      fa[ss] = y;
    }
    push_up(y);
    push_up(x);
  }
  
  int sta[maxn];
  void splay(int x) {
    int K = x, top = 0;
    sta[++top] = K;
    while (nrt(K)) sta[++top] = K = fa[K];
    while (top) push_down(sta[top--]);
    while (nrt(x)) {
      int y = fa[x], z = fa[y];
      if (nrt(y)) {
        rotate(((s[y][0] == x) ^ (s[z][0] == y)) ? x : y);
      }
      rotate(x);
    }
  }
  
  // LCT
 private:
  void access(int x) {
    for (int y = 0; x; x = fa[y = x]) {
      splay(x);
      s[x][1] = y;
      push_up(x);
    }
  }
  
  void make_root(int x) {
    access(x);
    splay(x);
    fan(x);
  }
  
  int find_root(int x) {
    access(x);
    splay(x);
    while (s[x][0]) {
      push_down(x);
      x = s[x][0];
    }
    splay(x);
    return x;
  }

  void split(int x, int y) {
    make_root(x);
    access(y);
    splay(y);
  }

 public:
  void link(int x, int y) {
    make_root(x);
    if (find_root(y) != x) fa[x] = y;
  }

  void cut(int x, int y) {
    make_root(x);
    if (find_root(y) == x && fa[y] == x && !s[y][0]) {
      fa[y] = s[x][1] = 0;
      push_up(x);
    }
  }

  void change(int x, int y) {
    splay(x);
    val[x] = y;
    push_up(x);
  }

  int ask(int x, int y) {
    split(x, y);
    return sum[y];
  }
} tr;