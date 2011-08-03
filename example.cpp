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

  std::cout.precision(15);

#if 0
  typedef mpl::apply<differential_func, sqrt>::type sqrt_d;
  typedef mpl::apply<sqrt_d, RATIONAL(1,0) >::type res;
#endif

#if 1
  typedef mpl::apply<integral, line, rational_t<0>, rational_t<3> >::type res;
#endif

  std::cout << res::get() << std::endl;
  //std::cout << 0.5-res::get() << std::endl;

  return 0;
}
