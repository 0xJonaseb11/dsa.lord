# C++ DSA Reference

## Custom comparators

```cpp
// Sort pairs by second, then first
sort(all(v), [](const pii& a, const pii& b) {
    if (a.second != b.second) return a.second < b.second;
    return a.first < b.first;
});

// Priority queue with custom order
struct Node { int d, u; };
auto cmp = [](const Node& a, const Node& b) { return a.d > b.d; };
priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
```

## Useful snippets

```cpp
// Inf for Dijkstra / BFS on weighted graphs
const ll INF = 1e18;

// Directions: 4-way and 8-way
const int dx4[] = {1, -1, 0, 0};
const int dy4[] = {0, 0, 1, -1};

// Prefix sum
vector<ll> pref(n + 1);
for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

// Disjoint Set Union
struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n), sz(n, 1) { iota(all(p), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a; sz[a] += sz[b];
        return true;
    }
};

// Fenwick tree (1-indexed)
struct BIT {
    int n; vector<ll> t;
    BIT(int n) : n(n), t(n + 1) {}
    void add(int i, ll v) { for (; i <= n; i += i & -i) t[i] += v; }
    ll sum(int i) { ll s = 0; for (; i; i -= i & -i) s += t[i]; return s; }
    ll range(int l, int r) { return sum(r) - sum(l - 1); }
};
```

## Debugging (local only)

```cpp
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n';
#else
#define dbg(x)
#endif
```

Remove debug macros before submission.
