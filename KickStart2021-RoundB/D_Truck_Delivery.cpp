#include<bits/stdc++.h>

using namespace std;

class Node {
  public:
    int V, L;
    long long int C;

  Node(int v, int li, long long int ci) {
    V = v, L = li, C = ci;
  }
};  

class SegmentTree {
  int Size;
  vector<long long int> Table;
  public:

  SegmentTree(int size) {
    Size = size + 1;
    Table = vector<long long int> (4 * Size, 0);
  }

  void update(int v, int tl, int tr, int pos, long long int value) {
    if (tl == tr) Table[v] = value;
    else {
      int tm = (tl + tr) / 2;
      if (pos <= tm) update(v * 2, tl, tm, pos, value);
      else update(v * 2 + 1, tm + 1, tr, pos, value);
      Table[v] = __gcd(Table[v * 2], Table[v * 2 + 1]);
    }
  }

  long long int rangeGCD(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return Table[v];
    int tm = (tl + tr) / 2;
    return __gcd(
                rangeGCD(v * 2, tl, tm, l, min(tm, r)), 
                rangeGCD(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
          );
  }
};

const int N = 2 * 1e5 + 1;
SegmentTree segTree(N);
map<pair<int, int>, long long int> query;

void dfs(int u, int parent, int n, vector<int> CQuery[], vector<Node> adj[]) {
  for (int l: CQuery[u]) {
    query[{u, l}] = segTree.rangeGCD(1, 0, N - 1, 0, l);
  }
  for (Node i: adj[u]) {
    if (i.V == parent) continue;
    segTree.update(1, 0, N - 1, i.L, i.C);
    dfs(i.V, u, n, CQuery, adj);
    segTree.update(1, 0, N - 1, i.L, 0);
  }
}

int main() {
  int tt; cin >> tt;
  for (int t = 1; t <= tt; t++) {
    int n, q; cin >> n >> q;
    vector<Node> adj[n + 1];
    for (int i = 0; i < n - 1; i++) {
      int U, V, Li; long long int Ci;
      cin >> U >> V >> Li >> Ci;
      adj[U].push_back(Node(V, Li, Ci));
      adj[V].push_back(Node(U, Li, Ci));
    }
    vector<int> CQuery[n + 1];
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
      int C, W; cin >> C >> W;
      CQuery[C].push_back(W);
      queries.push_back({C, W});
    }
    dfs(1, -1, n, CQuery, adj);
    cout << "Case #" << t << ": ";
    for (pair<int, int> i: queries) {
      cout << query[i] << " ";
    }
    cout << "\n";
    query.clear();
  }
  return 0;
}