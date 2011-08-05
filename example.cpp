#include <iostream>

#include <rational/math.hpp>
#include <rational/differential.hpp>
#include <rational/integral.hpp>

struct line
{
  template <class X>
  struct apply
  {
    typedef X type;
  };
};

int main()
{
  using namespace rational;
  namespace mpl = boost::mpl;
  using namespace mpl::placeholders;

  std::cout.precision(15);

#if 0
  typedef mpl::apply<integral_func, sqrt>::type sqrt_i2;
  //typedef mpl::bind<sqrt_i2, RATIONAL(0,0), _1> sqrt_i;

  //typedef mpl::apply<differential_func, sqrt_i>::type sqrt2;

  typedef RATIONAL(3,0) x;
  //typedef mpl::apply<sqrt_i, x> res;

  typedef mpl::apply<sqrt_i2, rational_t<0>, x> res;

  //typedef mpl::apply<sqrt2, x> res;
#endif

#if 0
  typedef mpl::apply<differential_func, sqrt>::type sqrt_d;
  typedef mpl::apply<sqrt_d, RATIONAL(1,0) >::type res;
#endif

#if 1
  typedef mpl::apply<integral_func, line>::type line_i;
  typedef mpl::apply<line_i, RATIONAL(0,0), RATIONAL(3,0)>::type res;
#endif

  std::cout << res::get() << std::endl;
  //std::cout << 2-res::get()*res::get() << std::endl;

  return 0;
}
