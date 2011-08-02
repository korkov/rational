#ifndef RATIONAL_1311698245
#define RATIONAL_1311698245

#include "rational.hpp"

namespace rational
{
  namespace detail
  {
    template <int64_t p, class res, class x>
    struct sqrt_eval
    {
      typedef typename divide<x, res>::type t1;
      typedef typename plus<res, t1>::type t2;
      typedef typename divide<t2, rational_t<2,1> >::type tmp;
      typedef typename sqrt_eval<p-1, tmp, x>::type type;
    };

    template <class res, class x>
    struct sqrt_eval<0, res, x>
    {
      typedef res type;
    };

    template <class x>
    struct sqrt
    {
      typedef typename divide< typename plus<x, rational_t<1,1> >::type, rational_t<2,1> >::type res;
      typedef typename sqrt_eval<15, res, x>::type type;
    };

    template <int64_t a>
    struct sqrt< rational_t<0, a> >
    {
      static const int64_t value = 0;
    };
  }

  using detail::sqrt;
}

#endif  // RATIONAL_1311698245
