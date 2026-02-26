#include <dsu/dsu.hpp>

#include <cassert>
#include <iostream>
#include <stdexcept>

static void test_basic_unions()
{
  dsu::DSU uf(6);

  assert(uf.n() == 6);
  assert(uf.components() == 6);

  assert(!uf.same(1, 2));
  assert(uf.unite(1, 2));
  assert(uf.same(1, 2));
  assert(uf.components() == 5);

  // Unite again: no-op
  assert(!uf.unite(1, 2));
  assert(uf.components() == 5);

  assert(uf.unite(2, 3));
  assert(uf.same(1, 3));
  assert(uf.components() == 4);

  assert(uf.unite(4, 5));
  assert(uf.components() == 3);

  assert(!uf.same(0, 5));
  assert(uf.unite(0, 5));
  assert(uf.same(0, 4));
  assert(uf.components() == 2);
}

static void test_component_sizes()
{
  dsu::DSU uf(7);

  uf.unite(0, 1);
  uf.unite(1, 2); // {0,1,2} size 3

  uf.unite(3, 4); // {3,4} size 2
  uf.unite(5, 6); // {5,6} size 2

  assert(uf.component_size(0) == 3);
  assert(uf.component_size(2) == 3);

  assert(uf.component_size(3) == 2);
  assert(uf.component_size(4) == 2);

  assert(uf.component_size(5) == 2);
  assert(uf.component_size(6) == 2);

  // Merge two components
  uf.unite(2, 4); // {0,1,2,3,4} size 5
  assert(uf.component_size(0) == 5);
  assert(uf.component_size(3) == 5);

  assert(uf.components() == 2);
}

static void test_out_of_range()
{
  dsu::DSU uf(3);

  bool threw = false;
  try
  {
    (void)uf.find(10);
  }
  catch (const std::out_of_range &)
  {
    threw = true;
  }
  assert(threw);
}

int main()
{
  test_basic_unions();
  test_component_sizes();
  test_out_of_range();

  std::cout << "OK\n";
  return 0;
}
