#ifndef RATIONAL_1312222485
#define RATIONAL_1312222485

#include <stdint.h>

namespace rational
{
  namespace detail
  {
    template <int64_t m, int64_t n>
    struct nod;
    template <int64_t a>
    struct nod<a, 0>
    {
      static const int64_t value = a;
    };
    template <int64_t a, int64_t b>
    struct nod
    {
      static const int64_t value = nod<b, a % b>::value;
    };
  }

  using detail::nod;
}

#endif  // RATIONAL_1312222485
