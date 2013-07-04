Rational
========

C++ library for compile time floating point computations.


```c++
#include <iostream>
#include "rational/math.hpp"

int main()
{
  std::cout.precision(15);
  const double s = rational::sqrt<RATIONAL(2,0)>::type::get();

  std::cout << s << std::endl;
  std::cout << 2-s*s << std::endl;

  return 0;
}
```

Read for details http://habrahabr.ru/post/124963/
