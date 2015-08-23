#ifndef PRINT_FLOAT_H

#include <sstream>
#include <locale>
#include <algorithm>

class Print_float {
public:
  
  template <typename Tfl>
  static std::string print(Tfl d)
  {
    std::ostringstream oss;
    oss << std::setprecision(std::numeric_limits<Tfl>::max_digits10) << d;
    //const char deci_point = std::use_facet<std::numpunct<char>>(std::locale("")).decimal_point();
    const char deci_point = std::use_facet<std::numpunct<char>>(std::cout.getloc()).decimal_point();
    
    const std::string &str = oss.str();
    if (std::find(str.cbegin(), str.cend(), deci_point) == str.cend())
      return str + deci_point + suffix(Tfl{});
    else
      return str              + suffix(Tfl{});
  }
  
private:
  static constexpr const char * const suffix(float)
  {
    return "F";
  }
  
  static constexpr const char * const suffix(double)
  {
    return "";
  }
  
  static constexpr const char * const suffix(long double)
  {
    return "L";
  }
};

#endif
