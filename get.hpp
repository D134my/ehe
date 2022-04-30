#ifndef __ehe_get__
#define __ehe_get__

#include "request.hpp"
#include "result_type.hpp"
#include <map>
#include <string>

namespace ehe {
namespace https {

result_type get(std::pair<std::string, std::string> const &url);
} // namespace https

namespace http {

result_type get(std::pair<std::string, std::string> const &url);

} // namespace http

} // namespace ehe

#endif