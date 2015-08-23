#include <iostream>
#include <iomanip>
#include <cassert>
#include <sstream>

#include "print_float.h"
#include "fractionizer.h"

// 22.345 ==   22 + (1 / (2 + (1 / (1 + (1 / (8 + (1 / (1 + (1 / (6.))))))))))
//           [ 22,        2,        1,        8,        1,        6 ]

template <typename Tfl>
void check(const char *str, Tfl d)
{
  Tfl num;
  Tfl denom;
  Fractionizer::fractionize(d, num, denom);
  std::cout << "as text:                  " << str << '\n'
	    << "to type and back to text: " << Print_float::print(d) << '\n';

  
  Tfl orig;
  if (std::istringstream(                              str) >> orig) {
    Tfl round_trip;
    assert(std::istringstream(Print_float::print(d))                  >> round_trip); /* round-trip: from floating to text and back to floating */
    assert(                                            orig      ==      round_trip);
    std::cout << "check assert:             assert(" << str << " == " << Print_float::print(d) << ")\n";
  }
  
  std::cout << "Approx via FRACTION:      (" << Print_float::print(num) << ")/(" << Print_float::print(denom) << ")\n";
  assert((num/denom) == d);  

  {
    assert(std::istringstream(Print_float::print(num))   >> num);    /* round-trip: from floating to text and back to floating */
    assert(std::istringstream(Print_float::print(denom)) >> denom);  /* round-trip: from floating to text and back to floating */
    assert((num/denom) == d);
    assert(std::istringstream(Print_float::print(d))     >> d);      /* round-trip: from floating to text and back to floating */
    assert((num/denom) == d);
    std::cout << "check assert:             assert((" << Print_float::print(num) << ")/(" << Print_float::print(denom) << ") == " << Print_float::print(d) << ")\n" << std::endl;
  }
}

template <size_t N>
constexpr size_t str_len(const char (&)[N])
{
  return N-1;
}

#define mycheck(VAL) check(#VAL, VAL)

#include <cfloat>

int main()
{
  mycheck(std::numeric_limits<float>::min());
  mycheck(std::numeric_limits<double>::min());
  mycheck(std::numeric_limits<long double>::min());

  std::cout << "------\n" << std::endl;

  mycheck(std::numeric_limits<float>::max());
  mycheck(std::numeric_limits<double>::max());
  mycheck(std::numeric_limits<long double>::max());

  std::cout << "------\n" << std::endl;
  
  mycheck(0.);
  mycheck(-0.);
  mycheck(-0.5);
  mycheck(-0.3);
  mycheck(-0.4);

  std::cout << "------\n" << std::endl;
  
  mycheck(0.6);
  mycheck(0.6);
  mycheck(0.3);
  mycheck(0.9);
  mycheck(12.34F);
  mycheck(12.34);
  mycheck(12.34L);
  mycheck(1.2345);
  mycheck(7.40200133400F);
  mycheck(7.40200133400);
  mycheck(7.40200133400L);
  mycheck(1.2345678901234L);
  mycheck(1.23456789012345678987656789L);
  mycheck(8.589973e9F);
  mycheck(8.589973e9);
  mycheck(8.589973e9L);
  mycheck(8.589974e9F);
  mycheck(8.589974e9);
  mycheck(8.589974e9L);
  mycheck(22.345F);
  mycheck(22.345);
  mycheck(22.345L);

  return 0;
}
