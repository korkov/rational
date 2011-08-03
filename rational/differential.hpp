#ifndef RATIONAL_1312305850
#define RATIONAL_1312305850

#include <rational/rational.hpp>

namespace rational
{
  namespace detail
  {
    namespace mpl = boost::mpl;

    typedef rational_t<1, 1000> lim;
    typedef rational_t<1, 10> lim_n;

#define VAR(V, WHAT) typedef WHAT V;
#define CALL(ARGS...) typename mpl::apply<ARGS >::type

    struct differential_eval
    {
      // f1 = f(x+delta)
      // f2 = f(x-delta)
      // type = (f1-f2)/(2*delta)
      template <class f, class x, class delta>
      struct apply
      {
        VAR(f1, CALL(f, CALL(plus, x, delta)));
        VAR(f2, CALL(f, CALL(minus, x, delta)));
        VAR(type, CALL(divide, CALL(minus, f1, f2), CALL(mult, rational_t<2>, delta)));
      };
    };

    struct differential_algo
    {
      // diff = f'(x)
      // f1 = diff*delta + f(x)
      // f2 = f(x+delta)
      // err = f1/f2 - 1
      // cont = lim < abs(err)
      // new_delta = delta * lim_n
      // while (cont) differential_algo(f, x, new_delta)
      template <class, class f, class x, class delta>
      struct apply
      {
        VAR(diff, CALL(differential_eval, f, x, delta));
        VAR(f1, CALL(plus, CALL(mult, diff, delta), CALL(f, x)));
        VAR(f2, CALL(f, CALL(plus, x, delta)));
        VAR(err, CALL(minus, CALL(divide, f1, f2), rational_t<1>));
        VAR(cont, CALL(less, lim, CALL(abs, err)));
        VAR(new_delta, CALL(mult, delta, lim_n));
        VAR(type, CALL(differential_algo, mpl::bool_<cont::value>, f, x, new_delta));
      };

      // type = f'(x)
      template <class f, class x, class delta>
      struct apply<mpl::bool_<false>, f, x, delta>
      {
        VAR(type, CALL(differential_eval, f, x, delta));
      };
    };

    struct differential
    {
      template <class f, class x>
      struct apply
      {
        VAR(type, CALL(differential_algo, mpl::bool_<true>, f, x, rational_t<1>));
      };
    };

    struct differential_func
    {
      template <class F>
      struct apply
      {
        typedef mpl::bind<differential, F, mpl::placeholders::_1> type;
      };
    };
  }

  using detail::differential;
  using detail::differential_func;
}

#endif  // RATIONAL_1312305850
