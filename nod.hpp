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
    template <int64_t a, int64_t b>
    struct gcd
    {
      static const int64_t value = gcd<b, a % b>::value;
    };
  }

  using detail::gcd;
}

#endif  // RATIONAL_1312222485
