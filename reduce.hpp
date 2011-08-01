#ifndef RATIONAL_1311695677
#define RATIONAL_1311695677

#include "prime.hpp"
#include <stdint.h>
#include "rational.hpp"

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

    template <bool, int i, class R>
    struct reduce_accurate;

    template <bool, class R>
    struct reduce_inaccurate
    {
      typedef rational_t<(R::a >> 1), (R::b >> 1)> type_;
      typedef typename reduce_accurate<require_reduce<type_>::value, 0, type_>::type type;
    };

    template <class R>
    struct reduce_inaccurate<false, R>
    {
      typedef R type;
    };

    template <bool, int i, class R>
    struct reduce_accurate
    {
      const static int64_t divider = prime<i>::value;
      const static bool divisible = !(R::a % divider) && !(R::b % divider);

      const static int64_t new_a = divisible ? (R::a / divider) : R::a;
      const static int64_t new_b = divisible ? (R::b / divider) : R::b;

      typedef rational_t<new_a, new_b> new_type;
      const static bool continue_reduce = divider <= 100 && require_reduce<new_type>::value;

      typedef typename reduce_accurate<
        continue_reduce,
        divisible ? i : i+1,
        new_type
        >::type type;
    };

    template <int i, class R>
    struct reduce_accurate<false, i, R>
    {
      typedef typename reduce_inaccurate<require_reduce<R>::value, R>::type type;
    };

    template <class R>
    struct reduce
    {
      typedef typename reduce_accurate<require_reduce<R>::value, 0, R>::type type;
    };
  }

  using detail::reduce;
}

#endif  // RATIONAL_1311695677
