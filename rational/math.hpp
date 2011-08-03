#ifndef RATIONAL_1311698245
#define RATIONAL_1311698245

#include "rational.hpp"
#include <boost/mpl/apply.hpp>

namespace rational
{
  namespace detail_math
  {
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;

    struct sqrt
    {
      template <
        class x,
        class p = mpl::int_<15>,
        class res = mpl::apply<divide, mpl::apply<plus, x, rational_t<1,1> >, rational_t<2,1> >
        >
      struct apply
      {
        typedef typename mpl::apply<divide, x, res>::type t1;
        typedef typename mpl::apply<plus, res, t1>::type t2;
        typedef typename mpl::apply<divide, t2, rational_t<2,1> >::type tmp;
        typedef typename mpl::apply<sqrt, x, mpl::int_<p::value-1>, tmp>::type type;
      };

      template <class x, class res>
      struct apply<x, mpl::int_<0>, res>
      {
        typedef typename res::type type;
      };

      template <int64_t a>
      struct apply< rational_t<0, a> >
      {
        typedef rational_t<0, 1> type;
      };
    };

    struct abs
    {
      typedef rational_t<0> null;

      template <bool, class x>
      struct eval
      {
        typedef typename mpl::apply<minus, null, x>::type type;
      };
      template <class x>
      struct eval<false, x>
      {
        typedef typename x::type type;
      };

      template <class x>
      struct apply
      {
        static const bool neg = mpl::apply<less, x, null>::value;
        typedef typename eval<neg, x>::type type;
      };
    };
  }

  using detail_math::sqrt;
  using detail_math::abs;
}

#endif  // RATIONAL_1311698245
