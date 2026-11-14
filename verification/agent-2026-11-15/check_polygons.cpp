// Independent, exact enumeration of convex equilateral p-gon turn tuples.
// Copyright (c) 2026 independent verification; MIT license per repository.
// Usage: c++ -O3 -std=c++17 check_polygons.cpp -o check_polygons && ./check_polygons
// No downloaded code/data or floating-point tolerance is used.
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdexcept>

class Enumerator {
  int p;
  std::array<int, 32> multiplicity{};
  std::array<int, 32> turns{};
  uint64_t candidates = 0;
  uint64_t closed = 0;
  uint64_t nonregular = 0;

  // z = exp(pi*i/p).  z^(p+k) = -z^k, and the minimal polynomial is
  // Phi_(2p)(z) = 1-z+z^2-...+z^(p-1), p odd.
  // Thus sum_j z^(exponent_j) = 0 iff the signed coefficient of z^k
  // equals (-1)^k times a single integer for every 0 <= k < p.
  bool vanishes() const {
    const int value = multiplicity[0];
    for (int k = 1; k < p; ++k)
      if (multiplicity[k] != ((k & 1) ? -value : value)) return false;
    return true;
  }

  void recurse(int edge, int heading, int total) {
    if (edge == p) { // p-1 turns (t_1,...,t_(p-1)) chosen.
      int closing_turn = 2*p - total; // t_0, from last edge back to first.
      if (closing_turn < 0 || closing_turn >= p) return;
      ++candidates;
      if (!vanishes()) return;
      ++closed;
      bool regular = closing_turn == 2;
      for (int j=1; j<p; ++j) regular &= turns[j] == 2;
      if (!regular) ++nonregular;
      return;
    }
    const int remaining_turns = p - edge - 1;
    for (int t = 0; t < p && total+t <= 2*p; ++t) {
      const int next_total = total+t;
      // Enough remaining turns must be available to keep t_0 < p.
      if (next_total + remaining_turns*(p-1) < p+1) continue;
      turns[edge] = t;
      const int next_heading = heading+t;
      const int index = next_heading % p;
      const int sign = (next_heading < p) ? 1 : -1;
      multiplicity[index] += sign;
      recurse(edge+1, next_heading, next_total);
      multiplicity[index] -= sign;
    }
  }

public:
  explicit Enumerator(int prime): p(prime) {
    if (p < 3 || p > 31 || p % 2 == 0) throw std::invalid_argument("odd prime 3..31 required");
  }
  void run() {
    multiplicity[0] = 1; // normalize first edge to exponent zero.
    const auto start = std::chrono::steady_clock::now();
    recurse(1, 0, 0);
    const auto finish = std::chrono::steady_clock::now();
    const double seconds = std::chrono::duration<double>(finish-start).count();
    std::cout << "p=" << p << " candidates=" << candidates
              << " exact_closed=" << closed
              << " nonregular=" << nonregular
              << " a(p)=" << closed << " oeis_a(p)=1"
              << " match=" << (closed == 1 && nonregular == 0 ? "yes" : "NO")
              << " runtime_seconds=" << seconds << '\n';
    if (closed != 1 || nonregular != 0) throw std::runtime_error("nonunique prime polygon");
  }
};

int main() {
  std::cout << "Algorithm: enumerate t_i=p-m_i in [0,p-1] with sum 2p; "
               "test exact cyclotomic zero (no floating point).\n";
  std::cout << "Indexing: OEIS offset=3, prime n=p, observed OEIS a(p)=1.\n";
  for (int p : {3, 5, 7, 11, 13}) Enumerator(p).run();
}
