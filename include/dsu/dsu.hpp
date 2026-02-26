#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <cstdint>

namespace dsu
{
  /**
   * @brief Disjoint Set Union (Union-Find) data structure.
   *
   * Provides near O(1) amortized operations for:
   * - finding a representative (root) of a set
   * - merging two sets
   * - checking connectivity
   *
   * Uses:
   * - Path compression (in find)
   * - Union by rank
   *
   * Indices are 0-based: [0, n).
   */
  class DSU final
  {
  public:
    /**
     * @brief Construct an empty DSU.
     */
    DSU() = default;

    /**
     * @brief Construct a DSU with n singleton sets.
     * @param n Number of elements.
     */
    explicit DSU(std::size_t n)
    {
      reset(n);
    }

    /**
     * @brief Reset DSU to n singleton sets.
     * @param n Number of elements.
     */
    void reset(std::size_t n)
    {
      parent_.resize(n);
      rank_.assign(n, 0);
      size_.assign(n, 1);
      components_ = n;

      for (std::size_t i = 0; i < n; ++i)
      {
        parent_[i] = i;
      }
    }

    /**
     * @brief Number of elements tracked by DSU.
     */
    std::size_t n() const noexcept
    {
      return parent_.size();
    }

    /**
     * @brief Number of connected components.
     */
    std::size_t components() const noexcept
    {
      return components_;
    }

    /**
     * @brief Find the root representative of x.
     *
     * Path compression is applied.
     *
     * @param x Element index.
     * @return Root representative.
     * @throws std::out_of_range if x is out of bounds.
     */
    std::size_t find(std::size_t x)
    {
      require_in_range(x);

      if (parent_[x] == x)
      {
        return x;
      }

      parent_[x] = find(parent_[x]);
      return parent_[x];
    }

    /**
     * @brief Check whether a and b are in the same set.
     * @throws std::out_of_range if a or b is out of bounds.
     */
    bool same(std::size_t a, std::size_t b)
    {
      return find(a) == find(b);
    }

    /**
     * @brief Union the sets containing a and b.
     *
     * Uses union by rank, and maintains component sizes.
     *
     * @param a Element index.
     * @param b Element index.
     * @return true if a merge happened, false if already in same set.
     * @throws std::out_of_range if a or b is out of bounds.
     */
    bool unite(std::size_t a, std::size_t b)
    {
      std::size_t ra = find(a);
      std::size_t rb = find(b);

      if (ra == rb)
      {
        return false;
      }

      // Union by rank.
      if (rank_[ra] < rank_[rb])
      {
        std::swap(ra, rb);
      }

      parent_[rb] = ra;
      size_[ra] += size_[rb];

      if (rank_[ra] == rank_[rb])
      {
        ++rank_[ra];
      }

      if (components_ > 0)
      {
        --components_;
      }

      return true;
    }

    /**
     * @brief Size of the component containing x.
     * @throws std::out_of_range if x is out of bounds.
     */
    std::size_t component_size(std::size_t x)
    {
      const std::size_t r = find(x);
      return size_[r];
    }

    /**
     * @brief Root check (no compression), mostly for debugging.
     * @throws std::out_of_range if x is out of bounds.
     */
    bool is_root(std::size_t x) const
    {
      require_in_range_const(x);
      return parent_[x] == x;
    }

  private:
    std::vector<std::size_t> parent_{};
    std::vector<std::uint8_t> rank_{};
    std::vector<std::size_t> size_{};
    std::size_t components_{0};

    void require_in_range(std::size_t x) const
    {
      if (x >= parent_.size())
      {
        throw std::out_of_range("dsu::DSU: index out of range");
      }
    }

    void require_in_range_const(std::size_t x) const
    {
      if (x >= parent_.size())
      {
        throw std::out_of_range("dsu::DSU: index out of range");
      }
    }
  };

} // namespace dsu
