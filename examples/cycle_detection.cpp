#include <dsu/dsu.hpp>
#include <iostream>
#include <vector>

/*
  Example:
  Detecting a cycle in an undirected graph.
*/

int main()
{
  // Graph edges (u, v)
  std::vector<std::pair<int, int>> edges{
      {0, 1},
      {1, 2},
      {2, 3},
      {3, 4},
      {4, 1} // creates a cycle
  };

  dsu::DSU uf(5);

  bool has_cycle = false;

  for (const auto &[u, v] : edges)
  {
    if (uf.same(u, v))
    {
      has_cycle = true;
      break;
    }
    uf.unite(u, v);
  }

  std::cout << "Cycle detected? "
            << (has_cycle ? "yes" : "no") << "\n";

  return 0;
}
