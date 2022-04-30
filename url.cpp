#include "url.hpp"

namespace ehe {
// validate host address and path
std::pair<std::string, std::string> url(std::string const &url) {

  std::string host;
  std::string path;
  try {

    std::regex host_re("^((http[s]?|ftp):/)?/?([^//]+)");

    std::regex path_re("/.*");

    host = url;
    std::smatch sm;

    if (std::regex_search(host, sm, host_re))
      host = sm.str();

    else
      throw std::invalid_argument("bad host");

    if (std::regex_search(url, sm, path_re))
      path = sm.str();
    else
      throw std::invalid_argument("bad path");

    std::cout << "host : " << host << "\tpath : " << path << '\n';

  } catch (std::exception const &error) {
    std::cerr << "error occurred : " << error.what() << std::endl;
    exit(EXIT_FAILURE);
  }

  return std::pair<std::string, std::string>{host, path};
}
} // namespace ehe