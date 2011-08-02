#include <iostream>

#include "rational/math.hpp"

int main()
{
  using namespace rational;
  namespace mpl = boost::mpl;

  std::cout.precision(15);

  typedef RATIONAL(2,0) x;
  typedef mpl::apply<sqrt, x> result;

  const double s = result::type::get();
  std::cout << s << std::endl;
  std::cout << 2-s*s << std::endl;

  return 0;
}
