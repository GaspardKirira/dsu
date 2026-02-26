#include <dsu/dsu.hpp>
#include <iostream>

/*
  Example:
  Basic connectivity checks using DSU.
*/

int main()
{
  dsu::DSU uf(6);

  uf.unite(0, 1);
  uf.unite(1, 2);
  uf.unite(3, 4);

  std::cout << "0 and 2 connected? "
            << (uf.same(0, 2) ? "yes" : "no") << "\n";

  std::cout << "2 and 3 connected? "
            << (uf.same(2, 3) ? "yes" : "no") << "\n";

  uf.unite(2, 3);

  std::cout << "2 and 3 connected after union? "
            << (uf.same(2, 3) ? "yes" : "no") << "\n";

  std::cout << "Number of components: "
            << uf.components() << "\n";

  return 0;
}
