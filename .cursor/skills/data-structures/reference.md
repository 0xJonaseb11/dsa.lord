# Data Structures: Advanced Reference

## Segment tree (range sum, point update)

```cpp
struct SegTree {
    int n;
    vector<ll> t;
    SegTree(const vector<int>& a) {
        n = a.size();
        t.assign(4 * n, 0);
        build(1, 0, n - 1, a);
    }
    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) { t[v] = a[l]; return; }
        int m = (l + r) / 2;
        build(v*2, l, m, a);
        build(v*2+1, m+1, r, a);
        t[v] = t[v*2] + t[v*2+1];
    }
    void update(int v, int l, int r, int i, ll val) {
        if (l == r) { t[v] = val; return; }
        int m = (l + r) / 2;
        if (i <= m) update(v*2, l, m, i, val);
        else update(v*2+1, m+1, r, i, val);
        t[v] = t[v*2] + t[v*2+1];
    }
    ll query(int v, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[v];
        int m = (l + r) / 2;
        return query(v*2, l, m, ql, qr) + query(v*2+1, m+1, r, ql, qr);
    }
    void update(int i, ll val) { update(1, 0, n-1, i, val); }
    ll query(int l, int r) { return query(1, 0, n-1, l, r); }
};
```

## Trie (lowercase letters)

```cpp
struct Trie {
    struct Node { int child[26]; bool end; Node() : end(false) { memset(child, -1, sizeof child); } };
    vector<Node> nodes;
    Trie() { nodes.emplace_back(); }
    void insert(const string& s) {
        int cur = 0;
        for (char c : s) {
            int i = c - 'a';
            if (nodes[cur].child[i] == -1) {
                nodes[cur].child[i] = nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].child[i];
        }
        nodes[cur].end = true;
    }
    bool search(const string& s) {
        int cur = 0;
        for (char c : s) {
            int i = c - 'a';
            if (nodes[cur].child[i] == -1) return false;
            cur = nodes[cur].child[i];
        }
        return nodes[cur].end;
    }
};
```

## Sparse table (static RMQ)

```cpp
struct SparseTable {
    vector<vector<int>> st;
    vector<int> log2;
    SparseTable(const vector<int>& a) {
        int n = a.size();
        log2.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) log2[i] = log2[i/2] + 1;
        int K = log2[n] + 1;
        st.assign(K, vector<int>(n));
        st[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                st[k][i] = min(st[k-1][i], st[k-1][i + (1 << (k-1))]);
    }
    int query(int l, int r) {  // inclusive
        int k = log2[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
```

## Graph representations

```cpp
// Adjacency matrix: dense, O(n²) space, O(1) edge lookup
vector<vector<int>> mat(n, vector<int>(n, INF));

// Edge list: Kruskal, Bellman-Ford
vector<tuple<int,int,int>> edges;  // u, v, w

// Compressed coordinates when values are huge but count is small
vector<int> coords = a;
sort(all(coords));
coords.erase(unique(all(coords)), coords.end());
auto get = [&](int x) {
    return int(lower_bound(all(coords), x) - coords.begin());
};
```

## When to build vs use STL

| Build custom | Use STL |
|--------------|---------|
| Segment tree, Fenwick, Trie | vector, map, set, priority_queue |
| DSU with rollback | deque, stack, queue |
| Persistent structures | unordered_map, unordered_set |
| Treap / Splay (rare) | multiset for order statistics (careful with duplicates) |
