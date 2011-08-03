#include <iostream>

#include <rational/math.hpp>
#include <rational/differential.hpp>

int main()
{
  using namespace rational;
  namespace mpl = boost::mpl;

  std::cout.precision(15);

  typedef mpl::apply<differential_func, sqrt>::type sqrt_d;
  typedef mpl::apply<sqrt_d, RATIONAL(1,0) >::type res;

  std::cout << res::get() << std::endl;
  std::cout << 0.5-res::get() << std::endl;

  return 0;
}
