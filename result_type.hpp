#ifndef __ehe_result_type__
#define __ehe_result_type__
#include <string>

namespace ehe {
// request result
struct result_type {
  std::string host_name;
  std::string path;
  std::string address;
  std::string text;
  std::uint16_t port;
};
} // namespace ehe

#endif