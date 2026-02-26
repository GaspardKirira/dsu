#include <dsu/dsu.hpp>
#include <iostream>

/*
  Example:
  Querying component sizes.
*/

int main()
{
  dsu::DSU uf(7);

  uf.unite(0, 1);
  uf.unite(1, 2); // component {0,1,2}

  uf.unite(3, 4); // component {3,4}
  uf.unite(5, 6); // component {5,6}

  std::cout << "size of component containing 0: "
            << uf.component_size(0) << "\n";

  std::cout << "size of component containing 3: "
            << uf.component_size(3) << "\n";

  uf.unite(2, 4); // merge two components

  std::cout << "size of component containing 0 after merge: "
            << uf.component_size(0) << "\n";

  std::cout << "Number of components: "
            << uf.components() << "\n";

  return 0;
}
