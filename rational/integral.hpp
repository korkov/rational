#ifndef RATIONAL_1312384320
#define RATIONAL_1312384320

#include <boost/mpl/apply.hpp>
#include <rational/rational.hpp>

namespace rational
{
  namespace detail_integral
  {
    namespace mpl = boost::mpl;
    using namespace boost::mpl::placeholders;

    struct integral_eval
    {
      template <class C, class F, class x0, class x, class h>
      struct apply
      {
        typedef typename mpl::apply<plus, x0, h >::type x_next;
        typedef typename mpl::apply<F, x0 >::type f1;
        typedef typename mpl::apply<F, x_next >::type f2;
        typedef typename mpl::apply<divide, typename mpl::apply<plus, f1, f2 >::type, rational_t<2> >::type f_;
        typedef typename mpl::apply<mult, h, f_ >::type s;
        typedef typename mpl::apply<minus, x, x0 >::type dist;
        typedef typename mpl::apply<less, typename mpl::apply<abs, h >::type, typename mpl::apply<abs,dist >::type >::type cont;
        typedef typename mpl::apply<integral_eval, cont, F, x_next, x, h >::type rest;
        typedef typename mpl::apply<plus, s, rest >::type type;
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
        typedef typename mpl::apply<minus, x, x0 >::type dist;
        typedef typename mpl::apply<divide, dist, rational_t<100> >::type h;
        typedef typename mpl::apply<less, typename mpl::apply<abs, h >::type, typename mpl::apply<abs,dist >::type >::type cont;
        typedef typename mpl::apply<integral_eval, cont, F, x0, x, h >::type rest;
        typedef typename mpl::apply<plus, rational_t<0>, rest >::type type;
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

  using detail_integral::integral;
  using detail_integral::integral_func;
}


#endif  // RATIONAL_1312384320
