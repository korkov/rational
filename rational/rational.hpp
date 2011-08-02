#ifndef RATIONAL_1311698112
#define RATIONAL_1311698112

#include "reduce.hpp"

namespace rational
{
  namespace detail
  {
    template <int64_t A, int64_t B>
    struct rational_t
    {
      static const int64_t a = A;
      static const int64_t b = B;
      static double get() { return (double)a/b; }
      typedef rational_t type;
    };

    struct plus
    {
      template <class R1_, class R2_>
      struct apply
      {
        typedef typename R1_::type R1;
        typedef typename R2_::type R2;
        typedef rational_t<R1::a * R2::b + R2::a * R1::b, R1::b * R2::b> type1;
        typedef typename reduce<type1>::type type;
      };
    };

    struct minus
    {
      template <class R1_, class R2_>
      struct apply
      {
        typedef typename R1_::type R1;
        typedef typename R2_::type R2;
        typedef rational_t<R1::a * R2::b - R2::a * R1::b, R1::b * R2::b> type1;
        typedef typename reduce<type1>::type type;
      };
    };

    struct mult
    {
      template <class R1_, class R2_>
      struct apply
      {
        typedef typename R1_::type R1;
        typedef typename R2_::type R2;
        typedef rational_t<R1::a * R2::a, R1::b * R2::b> type1;
        typedef typename reduce<type1>::type type;
      };
    };

    struct divide
    {
      template <class R1_, class R2_>
      struct apply
      {
        typedef typename R1_::type R1;
        typedef typename R2_::type R2;
        typedef rational_t<R1::a * R2::b, R1::b * R2::a> type1;
        typedef typename reduce<type1>::type type;
      };
    };

    struct less
    {
      template <class R1_, class R2_>
      struct apply
      {
        typedef typename R1_::type R1;
        typedef typename R2_::type R2;
        static const bool value = (R1::a * R2::b - R2::a * R1::b) < 0;
      };
    };

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

  using detail::rational_t;
  using detail::plus;
  using detail::minus;
  using detail::mult;
  using detail::divide;  
  using detail::less;
}

#define RATIONAL(A1, A2) rational::rational_t<(int)(A1##A2), rational::detail::pow<10, sizeof(#A2)-1>::value>

#endif  // RATIONAL_1311698112
