---
name: cpp-dsa
description: >-
  C++ for competitive programming and DSA — fast I/O, STL containers/algorithms,
  templates, and idioms. Use when writing, reviewing, or debugging C++ solutions,
  LeetCode/Codeforces problems, or when the user mentions C++, STL, or competitive programming.
---

# C++ for DSA

## Default setup

Use this boilerplate unless the problem specifies otherwise:

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int,int>
#define pb push_back
#define all(x) (x).begin(), (x).end()

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // ...
    return 0;
}
```

For single-file solutions in this repo, prefer one `.cpp` file per problem named `problem-slug.cpp`.

## I/O rules

| Input | Pattern |
|-------|---------|
| Single int | `int n; cin >> n;` |
| Array of n ints | `vi a(n); for (int& x : a) cin >> x;` |
| Unknown lines | `string line; while (getline(cin, line))` |
| Fast output | `cout << ans << '\n';` (avoid `endl`) |
| Many integers | use `\n` separators, batch with `ostringstream` if needed |

For problems with tight time limits and huge input, use `scanf/printf` only when profiling shows `cin` is the bottleneck.

## Container selection

| Need | Use | Notes |
|------|-----|-------|
| Dynamic array | `vector<T>` | Default for sequences |
| Stack / queue | `stack<T>`, `queue<T>` | Or `deque` for both ends |
| Min/max heap | `priority_queue<T>` | Default is max-heap; min-heap: `priority_queue<T, vector<T>, greater<T>>` |
| Hash map | `unordered_map<K,V>` | O(1) avg; use `map` when ordered keys needed |
| Hash set | `unordered_set<T>` | Duplicate detection, O(1) lookup |
| Ordered set | `set<T>` / `map<K,V>` | O(log n) |
| Deque ends | `deque<T>` | BFS, sliding window |
| Fixed-size bitset | `bitset<N>` | Subset DP, bitmask tricks |

## Algorithm shortcuts

```cpp
// Sort
sort(all(v));
sort(all(v), greater<int>());

// Binary search on answer or sorted array
auto it = lower_bound(all(v), x);  // first >= x
auto jt = upper_bound(all(v), x);  // first > x

// Permutations / next permutation
sort(all(v));
do { /* use v */ } while (next_permutation(all(v)));

// GCD / LCM
ll g = gcd(a, b);
ll l = lcm(a, b);  // C++17: std::lcm

// Mod arithmetic
const int MOD = 1e9 + 7;
(a + b) % MOD;
((ll)a * b) % MOD;
```

## Complexity guardrails

Before coding, state expected complexity. Reject approaches that exceed typical limits:

| n | Target |
|---|--------|
| ≤ 10 | O(n!) / O(2^n) OK |
| ≤ 20 | O(2^n) bitmask DP |
| ≤ 500 | O(n³) |
| ≤ 5,000 | O(n²) |
| ≤ 10⁵ | O(n log n) |
| ≤ 10⁶ | O(n) or O(n log n) with tight constants |
| ≤ 10⁷ | O(n) only, minimal overhead |

## Common pitfalls

- **Overflow**: use `long long` for sums/products; cast before multiply: `(ll)a * b`
- **Index off-by-one**: clarify 0-indexed vs 1-indexed in comments once
- **Mod on subtraction**: `(a - b + MOD) % MOD`
- **Integer division**: `-7/2 == -3` in C++; use `floor`/`ceil` helpers when needed
- **Uninitialized variables**: always initialize accumulators and DP tables
- **Recursion depth**: deep DFS may stack-overflow; switch to iterative or increase stack (platform-specific)
- **TLE on `endl`**: use `'\n'`

## Solution structure

When solving a problem, follow this order:

1. **Restate** — input, output, constraints
2. **Approach** — algorithm + time/space complexity
3. **Edge cases** — empty, single element, duplicates, negatives, overflow
4. **Implement** — clean, minimal code
5. **Verify** — walk through 2–3 examples including edge cases

## Output format for explanations

```markdown
## Approach
[1–2 sentences]

## Complexity
- Time: O(...)
- Space: O(...)

## Edge cases
- ...

## Code
[full solution]
```

## Additional resources

- STL container details and custom comparators: [reference.md](reference.md)
