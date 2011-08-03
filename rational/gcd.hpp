#ifndef RATIONAL_1312222485
#define RATIONAL_1312222485

#include <stdint.h>

namespace rational
{
  namespace detail
  {
    /// вычисление НОД
    template <int64_t m, int64_t n>
    struct gcd;
    template <int64_t a>
    struct gcd<a, 0>
    {
      static const int64_t value = a;
    };
    template <int64_t a_, int64_t b_>
    struct gcd
    {
      static const int64_t a = a_ > 0 ? a_ : -a_;
      static const int64_t b = b_ > 0 ? b_ : -b_;
      static const int64_t value = gcd<b, a % b>::value;
    };
  }

  using detail::gcd;
}

#endif  // RATIONAL_1312222485
