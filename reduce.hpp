#ifndef RATIONAL_1311695677
#define RATIONAL_1311695677

#include <stdint.h>
#include "rational.hpp"
#include "gcd.hpp"

namespace rational
{
  namespace detail
  {
    template <int64_t A, int64_t B>
    struct rational_t;

    template <class R>
    struct require_reduce
    {
      const static int64_t max = (1ll<<31);
      const static bool value = (R::a >= max) || (R::b >= max);
    };

    template <bool, class R>
    struct reduce_accurate;

    template <bool, class R>
    struct reduce_inaccurate
    {
      typedef rational_t<(R::a >> 1), (R::b >> 1)> type_;
      typedef typename reduce_accurate<require_reduce<type_>::value, type_>::type type;
    };

    template <class R>
    struct reduce_inaccurate<false, R>
    {
      typedef R type;
    };

    template <bool, class R>
    struct reduce_accurate
    {
      const static int64_t new_a = R::a / gcd<R::a, R::b>::value;
      const static int64_t new_b = R::b / gcd<R::a, R::b>::value;

      typedef rational_t<new_a, new_b> new_type;
      typedef typename reduce_inaccurate<require_reduce<new_type>::value, new_type>::type type;
    };

    template <class R>
    struct reduce_accurate<false, R>
    {
      typedef typename reduce_inaccurate<require_reduce<R>::value, R>::type type;
    };

    template <class R>
    struct reduce
    {
      typedef typename reduce_accurate<require_reduce<R>::value, R>::type type;
    };
  }

  using detail::reduce;
}

#endif  // RATIONAL_1311695677
