#include "ehe.hpp"
#include <iostream>

int main() {

  const ehe::result_type result = ehe::https::get(ehe::url("www.google.com/"));

  std::cout << "\tText : " << result.text << std::endl;

  return 0;
}