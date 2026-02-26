# dsu

Union-Find (Disjoint Set Union) for modern C++.

`dsu` provides a deterministic implementation of Disjoint Set Union with
path compression and union by rank.

Header-only. Zero external dependencies.

## Download

https://vixcpp.com/registry/pkg/gaspardkirira/dsu

## Why dsu?

Connectivity problems appear everywhere:

-   Graph connected components
-   Cycle detection
-   Kruskal's minimum spanning tree
-   Dynamic connectivity queries
-   Competitive programming tasks

Rewriting Union-Find repeatedly often leads to:

-   Missing path compression
-   Incorrect union heuristics
-   Broken size tracking
-   Off-by-one indexing bugs

This library provides:

-   Path compression
-   Union by rank
-   Component size tracking
-   Component count tracking
-   Explicit 0-based indexing
-   Bounds checking

No templates complexity.\
No macros.\
No hidden global state.

Just a deterministic connectivity primitive.

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/dsu
vix deps
```

### Manual

``` bash
git clone https://github.com/GaspardKirira/dsu.git
```

Add the `include/` directory to your project.

## Dependency

Requires C++17 or newer.

No external dependencies.

## Quick Examples

### Basic Connectivity

``` cpp
#include <dsu/dsu.hpp>
#include <iostream>

int main()
{
  dsu::DSU uf(6);

  uf.unite(0, 1);
  uf.unite(1, 2);

  std::cout << uf.same(0, 2) << "\n"; // 1 (true)
  std::cout << uf.same(0, 3) << "\n"; // 0 (false)
}
```

### Component Size

``` cpp
#include <dsu/dsu.hpp>
#include <iostream>

int main()
{
  dsu::DSU uf(5);

  uf.unite(0, 1);
  uf.unite(1, 2);

  std::cout << uf.component_size(0) << "\n"; // 3
}
```

### Cycle Detection (Undirected Graph)

``` cpp
#include <dsu/dsu.hpp>
#include <vector>
#include <iostream>

int main()
{
  std::vector<std::pair<int,int>> edges{
    {0,1},
    {1,2},
    {2,3},
    {3,1} // cycle
  };

  dsu::DSU uf(4);

  bool has_cycle = false;

  for (const auto& [u, v] : edges)
  {
    if (uf.same(u, v))
    {
      has_cycle = true;
      break;
    }
    uf.unite(u, v);
  }

  std::cout << has_cycle << "\n"; // 1
}
```

## API Overview

`dsu::DSU`

-   `DSU(std::size_t n)`

-   `DSU::reset(n)`

-   `DSU::find(x)`

-   `DSU::unite(a, b)`

-   `DSU::same(a, b)`

-   `DSU::component_size(x)`

-   `DSU::components()`

-   `DSU::n()`

## Complexity

Amortized time complexity:

-   `find` → almost O(1)
-   `unite` → almost O(1)

More formally:

`O(α(n))` where α is the inverse Ackermann function, which grows slower
than any practical function.

In real systems, operations are effectively constant time.

## Design Principles

-   Deterministic behavior
-   Explicit 0-based indexing
-   Bounds checking for safety
-   No implicit resizing
-   No dynamic memory beyond vectors
-   Header-only simplicity

This library intentionally focuses only on classic DSU.

If you need:

-   Rollback DSU
-   Persistent DSU
-   Weighted union constraints
-   Bipartite checks

Build them on top of this primitive.

## Tests

Run:

``` bash
vix build
vix tests
```

Tests verify:

-   Basic connectivity
-   Component count tracking
-   Component size tracking
-   Out-of-range safety

## License

MIT License\
Copyright (c) Gaspard Kirira

