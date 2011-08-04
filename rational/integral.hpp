#ifndef RATIONAL_1312384320
#define RATIONAL_1312384320

#include <boost/mpl/apply.hpp>
#include <rational/rational.hpp>

namespace rational
{
  namespace detail_integral
  {
    namespace mpl = boost::mpl;
    using namespace mpl::placeholders;

    struct integral_eval
    {
#define VAR(V, WHAT) typedef WHAT V
#define CALL(ARGS...) typename mpl::apply<ARGS >::type

      template <class C, class F, class x0, class x, class h>
      struct apply
      {
        VAR(x_next, CALL(plus, x0, h));
        VAR(f1, CALL(F, x0));
        VAR(f2, CALL(F, x_next));
        VAR(f_, CALL(divide, CALL(plus, f1, f2), rational_t<2>));
        VAR(s, CALL(mult, h, f_));
        VAR(dist, CALL(minus, x, x0));
        VAR(cont, CALL(less, CALL(abs, h), CALL(abs,dist)));
        VAR(rest, CALL(integral_eval, cont, F, x_next, x, h));
        VAR(type, CALL(plus, s, rest));
      };

      template <class F, class x0, class x, class h>
      struct apply<mpl::bool_<false>, F, x0, x, h>
      {
        typedef rational_t<0> type;
      };
    };

    struct integral
    {
      template <class F, class x0, class x>
      struct apply
      {
        VAR(dist, CALL(minus, x, x0));
        VAR(h, CALL(divide, dist, rational_t<100>));
        VAR(cont, CALL(less, CALL(abs, h), CALL(abs,dist)));
        VAR(rest, CALL(integral_eval, cont, F, x0, x, h));
        VAR(type, CALL(plus, rational_t<0>, rest));
      };
    };

    struct integral_func
    {
      template <class F>
      struct apply
      {
        typedef mpl::bind<integral, F, _1, _2> type;
      };
    };
  }
#undef VAR
#undef CALL

  using detail_integral::integral;
  using detail_integral::integral_func;
}


#endif  // RATIONAL_1312384320
