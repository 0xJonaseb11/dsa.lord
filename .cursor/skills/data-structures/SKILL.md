---
name: data-structures
description: >-
  Data structures for algorithm problems: selection guide, implementations,
  complexity, and pattern matching. Use when implementing or choosing arrays,
  linked lists, stacks, queues, trees, graphs, heaps, hash tables, tries,
  segment trees, or when the user asks about DSA, data structures, or Big-O tradeoffs.
---

# Data Structures for DSA

## Selection guide

| Problem signal | Structure | Why |
|----------------|-----------|-----|
| Random access, prefix sums | Array / vector | O(1) index, O(n) prefix in O(1) query |
| Push/pop at one end | Stack | DFS, parentheses, monotonic stack |
| FIFO processing | Queue / deque | BFS, sliding window |
| Min/max of stream | Heap (priority_queue) | O(log n) insert/extract |
| Fast lookup by key | Hash map / set | O(1) avg |
| Sorted order, rank queries | BST / ordered set / Fenwick | O(log n) |
| Parent-child hierarchy | Tree | Recursion, DFS |
| Connections, paths | Graph (adj list) | Sparse graphs |
| Prefix on strings | Trie | Autocomplete, XOR max |
| Range sum/min on array | Segment tree / Fenwick | O(log n) per update/query |
| Dynamic connectivity | DSU (Union-Find) | O(α(n)) amortized |
| LRU / ordered expiry | List + hash map | Design problems |

When multiple structures fit, prefer the one with simpler code and acceptable complexity.

## Core structures: complexity

| Structure | Access | Search | Insert | Delete | Space |
|-----------|--------|--------|--------|--------|-------|
| Array | O(1) | O(n) | O(n) | O(n) | O(n) |
| Linked list | O(n) | O(n) | O(1)* | O(1)* | O(n) |
| Stack / Queue | O(n) | O(n) | O(1) | O(1) | O(n) |
| Hash table | n/a | O(1)* | O(1)* | O(1)* | O(n) |
| BST (balanced) | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Heap | n/a | O(n) | O(log n) | O(log n) | O(n) |
| Trie (len L) | O(L) | O(L) | O(L) | O(L) | O(Σ·L) |

*Amortized or with known position for linked list.

## Pattern → technique map

| Pattern | Technique |
|---------|-----------|
| Two pointers on sorted array | Opposite ends or slow/fast |
| Subarray sum equals k | Prefix sum + hash map |
| Next greater element | Monotonic stack |
| Sliding window max/min | Deque (monotonic) |
| K largest / smallest | Heap size k |
| Shortest path unweighted | BFS |
| Shortest path weighted (non-neg) | Dijkstra + heap |
| Negative edges | Bellman-Ford |
| All-pairs shortest | Floyd-Warshall (n ≤ 400) |
| Cycle in directed graph | DFS coloring / topo sort |
| Cycle in undirected | DSU or DFS parent |
| Connected components | DFS/BFS or DSU |
| Tree diameter | Two BFS/DFS |
| LCA | Binary lifting / Euler tour |
| Range query static | Prefix / sparse table |
| Range query dynamic | Segment tree / Fenwick |
| Inversion count | Merge sort / Fenwick |
| String matching | KMP / Z / Rabin-Karp |

## Implementation defaults (C++)

Prefer STL when sufficient. Implement from scratch only when the problem requires it or for learning.

```cpp
// Adjacency list
vector<vector<int>> g(n);
vector<vector<pii>> wg(n);  // weighted: {neighbor, weight}

// Tree as adjacency (root at 0)
vector<vector<int>> tree(n);
// Build from edges; avoid adding parent back in undirected build

// Monotonic stack: next greater to the right
vi nextGreater(const vi& a) {
    int n = a.size();
    vi res(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            res[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}
```

## Tree traversals

```cpp
// DFS recursive
function<void(int,int)> dfs = [&](int u, int p) {
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
};

// BFS
queue<int> q;
q.push(root);
while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
        if (!vis[v]) { vis[v] = true; q.push(v); }
    }
}
```

## Workflow

1. Name what you are storing
2. List the operations you need and how often they run
3. Pick a structure from the guide
4. State time and space cost
5. Use STL first; hand-roll only when the exercise requires it

## Additional resources

- Advanced structures (segment tree, trie, sparse table): [reference.md](reference.md)
