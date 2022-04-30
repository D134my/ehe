#ifndef __ehe_request__
#define __ehe_request__

#include <sstream>
#include <string>

namespace ehe {
std::string make_request(std::string const &host, std::string const &path);
}
#endif