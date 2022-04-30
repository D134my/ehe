#include "request.hpp"

namespace ehe {
std::string make_request(std::string const &host, std::string const &path) {

  std::ostringstream request_stream{};
  request_stream << "GET " << path << " HTTP/1.1\n";
  request_stream << "Host: " << host << "\n";
  request_stream << "Connection: close\n\n";

  return request_stream.str();
}

} // namespace ehe