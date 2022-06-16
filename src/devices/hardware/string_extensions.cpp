#include "shapechangeable-simulation/devices/hardware/string_extensions.h"

string_extensions::string ItoString(int x) {
  string_extensions::string s;
  if (x == 0)
    s = string_extensions::string("0");
  else if (x < 0) {
    x = -x;
    while (x) {
      int a = x % 10;
      x /= 10;
      char digit[] = {'0' + a, '\0'};
      s += string_extensions::string(digit);
    }
    s += "-";
  } else {
    while (x) {
      int a = x % 10;
      x /= 10;
      char digit[] = {'0' + a, '\0'};
      s += string_extensions::string(digit);
    }
  }
  reverse(s.begin(), s.end());
  return s;
}
