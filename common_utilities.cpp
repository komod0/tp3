#include "common_utilities.h"

bool is_uint16(const std::string& s) {
  bool isanumber = s.find_first_not_of("0123456789") == s.npos;
  bool not_too_long = s.length() < 6; // Me aseguro que no explote el stoi
  return isanumber && not_too_long && (std::stoi(s) < 65536); // 2^16
}

bool non_repeating_string(const std::string s) {
  for (size_t i = 0; i < (s.length() - 1); i++) {
    if (s.find(s[i], i+1) != std::string::npos) {
      return false;
    }
  }
  return true;
}