#ifndef RATIONAL_1312305850
#define RATIONAL_1312305850

#include <rational/rational.hpp>

namespace rational
{
  namespace detail
  {
    namespace mpl = boost::mpl;
    using namespace boost::mpl::placeholders;

    typedef rational_t<1, 1000> lim;
    typedef rational_t<1, 10> lim_n;

    struct differential_eval
    {
      template <class f, class x, class delta>
      struct apply
      {
        typedef typename mpl::apply<f, typename mpl::apply<plus, x, delta >::type >::type f1;
        typedef typename mpl::apply<f, typename mpl::apply<minus, x, delta >::type >::type f2;
        typedef typename mpl::apply<divide, typename mpl::apply<minus, f1, f2 >::type, typename mpl::apply<mult, rational_t<2>, delta >::type >::type type;
      };
    };

    struct differential_algo
    {
      template <class, class f, class x, class delta>
      struct apply
      {
        typedef typename mpl::apply<differential_eval, f, x, delta >::type diff;
        typedef typename mpl::apply<plus, typename mpl::apply<mult, diff, delta >::type, typename mpl::apply<f, x >::type >::type f1;
        typedef typename mpl::apply<f, typename mpl::apply<plus, x, delta >::type >::type f2;
        typedef typename mpl::apply<minus, typename mpl::apply<divide, f1, f2 >::type, rational_t<1> >::type err;
        typedef typename mpl::apply<less, lim, typename mpl::apply<abs, err >::type >::type cont;
        typedef typename mpl::apply<mult, delta, lim_n >::type new_delta;
        typedef typename mpl::apply<differential_algo, cont, f, x, new_delta >::type type;
      };

      template <class f, class x, class delta>
      struct apply<mpl::bool_<false>, f, x, delta>
      {
        typedef typename mpl::apply<differential_eval, f, x, delta >::type type;
      };
    };

    struct differential
    {
      template <class f, class x>
      struct apply
      {
        typedef typename mpl::apply<differential_algo, mpl::bool_<true>, f, x, rational_t<1> >::type type;
      };
    };

    struct differential_func
    {
      template <class F>
      struct apply
      {
        typedef mpl::bind<differential, F, _1> type;
      };
    };
  }

  using detail::differential;
  using detail::differential_func;
}

#endif  // RATIONAL_1312305850
