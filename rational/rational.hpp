#ifndef RATIONAL_1311698112
#define RATIONAL_1311698112

#include "reduce.hpp"
#include <boost/mpl/apply.hpp>
#include <boost/mpl/quote.hpp>

namespace rational
{
  template <int64_t A, int64_t B>
  struct rational_t
  {
    static const int64_t a = A;
    static const int64_t b = B ? B:1;
    static double get() { return (double)a/b; }
    typedef rational_t type;
  };

  template <class R1_, class R2_>
  struct plus_
  {
    typedef typename R1_::type R1;
    typedef typename R2_::type R2;
    typedef rational_t<R1::a * R2::b + R2::a * R1::b, R1::b * R2::b> type1;
    typedef typename reduce<type1>::type type;
  };

  template <class R1_, class R2_>
  struct minus_
  {
    typedef typename R1_::type R1;
    typedef typename R2_::type R2;
    typedef rational_t<R1::a * R2::b - R2::a * R1::b, R1::b * R2::b> type1;
    typedef typename reduce<type1>::type type;
  };

  template <class R1_, class R2_>
  struct mult_
  {
    typedef typename R1_::type R1;
    typedef typename R2_::type R2;
    typedef rational_t<R1::a * R2::a, R1::b * R2::b> type1;
    typedef typename reduce<type1>::type type;
  };

  template <class R1_, class R2_>
  struct divide_
  {
    typedef typename R1_::type R1;
    typedef typename R2_::type R2;
    static const int64_t k = (R2::a > 0 ? 1 : -1);
    typedef rational_t<k * R1::a * R2::b, k * R1::b * R2::a> type1;
    typedef typename reduce<type1>::type type;
  };

  template <class R1_, class R2_>
  struct less_
  {
    typedef typename R1_::type R1;
    typedef typename R2_::type R2;
    static const bool value = (R1::a * R2::b - R2::a * R1::b) < 0;
    typedef boost::mpl::bool_<value> type;
  };

  typedef boost::mpl::quote2<plus_> plus;
  typedef boost::mpl::quote2<minus_> minus;
  typedef boost::mpl::quote2<mult_> mult;
  typedef boost::mpl::quote2<divide_> divide;
  typedef boost::mpl::quote2<less_> less;

  namespace detail
  {
    template <int V, unsigned D>
    struct pow
    {
      const static int value = V * pow<V, D - 1>::value;
    };
    template <int V>
    struct pow<V, 0>
    {
      const static int value = 1;
    };
  }
}

#define RATIONAL(A1, A2) rational::rational_t<(int)(A1##A2), rational::detail::pow<10, sizeof(#A2)-1>::value>

#endif  // RATIONAL_1311698112
