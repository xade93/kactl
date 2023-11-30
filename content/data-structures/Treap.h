class Treap {
 private:
  static const int inf = 0x3f3f3f3f;

  struct Node {
    int x, siz;
    unsigned rd;
    Node* s[2];

    void maintain() {
      siz = 1;
      if(s[0] != nullptr) {
        siz += s[0]->siz;
      }
      if(s[1] != nullptr) {
        siz += s[1]->siz;
      }
    }

    Node (int x) {
      this->x = x;
      siz = 1;
      s[0] = s[1] = nullptr;
      rd = rnd();
    }
  };

  Node* root;

  int getsiz(Node* x) {
    return x == nullptr ? 0 : x->siz;
  }

  void split(Node* now, int x, Node* &p1, Node* &p2) {
    if(now == nullptr) {
      p1 = p2 = nullptr;
      return;
    }
    if(now->x <= x) {
      p1 = now;
      split(now->s[1], x, now->s[1], p2);
    } else {
      p2 = now;
      split(now->s[0], x, p1, now->s[0]);
    }
    if(now != nullptr) {
      now->maintain();
    }
  }

    Node* merge(Node* p1, Node* p2) {
      if(p1 == nullptr) {
        return p2;
      }
      if(p2 == nullptr) {
        return p1;
      }
      if(p1->rd > p2->rd) {
        p1->s[1] = merge(p1->s[1], p2);
        p1->maintain();
        return p1;
      } else {
        p2->s[0] = merge(p1, p2->s[0]);
        p2->maintain();
        return p2;
      }
    }

  public:
    Treap() {
      root = nullptr;
    }

    void insert(int x) {
      Node *ll, *rr;
      split(root, x, ll, rr);
      root = merge(merge(ll, new Node(x)), rr);
    }

    void erase(int x) {
      Node *ll, *midd, *rr;
      split(root, x, ll, rr);
      split(ll, x - 1, ll, midd);
      Node* mid = nullptr;
      if(midd != nullptr) {
        mid = merge(midd->s[0], midd->s[1]);
        delete midd;
      }
      root = merge(merge(ll, mid), rr);
    }

    int kth(int k) {
      Node* now = root;
      while(true) {
        int tmp = getsiz(now->s[0]) + 1;
        if(tmp == k) {
          return now->x;
        }
        if(tmp < k) {
          k -= tmp, now = now->s[1];
        } else {
          now = now->s[0];
        }
      }
    }

    int rank(int x) {
      int ans = 0;
      int tmp = 0;
      Node* now = root;
      while(now != nullptr) {
        if(now->x == x) {
          ans = tmp + getsiz(now->s[0]) + 1;
        }
        if(x <= now->x) {
          now = now->s[0];
        } else {
          tmp += getsiz(now->s[0]) + 1;
          now = now->s[1];
        }
      }
      return ans;
    }

    int pred(int x) {
      int ans = -inf;
      Node* now = root;
      while(now != nullptr) {
        if(now->x < x) {
          ans = std::max(ans, now->x);
          now = now->s[1];
        } else {
          now = now->s[0];
        }
      }
      return ans;
    }

    int succ(int x) {
      int ans = inf;
      Node* now = root;
      while(now != nullptr) {
        if(now->x > x) {
          ans = std::min(ans, now->x);
        }
        if(x < now->x) {
          now = now->s[0];
        } else {
          now = now->s[1];
        }
      }
      return ans;
    }
} tr;
