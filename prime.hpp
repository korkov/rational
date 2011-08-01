#ifndef RATIONAL_1311695274
#define RATIONAL_1311695274

namespace rational
{
  namespace prime_detail
  {
    template <bool, int res, int x>
    struct calc_res
    {
      const static int tmp = (res+x/res)/2;
      typedef calc_res<(res > tmp), (tmp<res)?tmp:res, x> a;
      static const int value = a::value;
    };

    template <int res, int x>
    struct calc_res<false, res, x>
    {
      static const int value = res;
    };

    template <int x>
    struct sqrt
    {
      static const int value = calc_res<true, (x+1)/2, x>::value;
    };

    template <>
    struct sqrt<0>
    {
      static const int value = 0;
    };

    template<int n, int div>
    struct is_prime_rec
    {
      static const bool value = (n % div != 0) && is_prime_rec<n, div - 1>::value;
    };

    template<int n>
    struct is_prime_rec<n, 1>
    {
      static const bool value = true;
    };

    template<int n>
    struct is_prime_rec<n, 0>
    {
      static const bool value = true;
    };

    template<int n>
    struct is_prime
    {
      static const bool value = is_prime_rec<n, sqrt<n>::value>::value;
    };

    template<int n>
    struct next_prime;

    template<int n, bool cond>
    struct next_prime_if
    {
      static const int value = n + 1;
    };

    template<int n>
    struct next_prime_if<n, false>
    {
      static const int value = next_prime<n + 1>::value;
    };

    template<int n>
    struct next_prime
    {
      static const int value = next_prime_if<n, is_prime<n + 1>::value>::value;
    };

    template<int i>
    struct prime
    {
      static const int value = next_prime<prime<i - 1>::value >::value;
    };

    template<>
    struct prime<0>
    {
      static const int value = 2;
    };
  }

  using prime_detail::prime;
  using prime_detail::is_prime;
}

#endif  // RATIONAL_1311695274
