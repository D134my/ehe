#include "get.hpp"
#include "http.hpp"
#include "https.hpp"
#include <atomic>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <thread>

namespace ehe {
namespace https {

// prefer https over http
result_type get(std::pair<std::string, std::string> const &url) {

  boost::asio::io_context ioc;
  boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tls);
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket(ioc,
                                                                ssl_context);

  // to check is request finished in less than 8 sec or not
  std::atomic<bool> expire = false;
  boost::asio::steady_timer timer(ioc, std::chrono::seconds(8));

  auto timer_thread = std::jthread([&] {
    timer.async_wait([&](boost::system::error_code error) {
      if (!expire) {
        std::cerr << "Connection timeout \n";
        ioc.stop();
      }
    });
  });

  timer_thread.join();

  auto request = make_request(url.first, url.second);
  https_client client(ioc, socket, url.first, url.second, request, expire);

  auto run_thread = std::jthread([&] { ioc.run(); });
  run_thread.join();

  return client.get_result();
}

} // namespace https

namespace http {

result_type get(std::pair<std::string, std::string> const &url) {

  boost::asio::io_context ioc;
  boost::asio::ip::tcp::socket socket(ioc);

  // to check is request finished in less than 8 sec or not
  std::atomic<bool> expire = false;
  boost::asio::steady_timer timer(ioc, std::chrono::seconds(8));

  auto timer_thread = std::jthread([&] {
    timer.async_wait([&](boost::system::error_code error) {
      if (!expire) {
        std::cerr << "Connection timeout \n";
        ioc.stop();
      }
    });
  });

  timer_thread.join();

  auto request = make_request(url.first, url.second);
  http_client client(ioc, socket, url.first, url.second, request, expire);

  auto run_thread = std::jthread([&] { ioc.run(); });
  run_thread.join();

  return client.get_result();
}

} // namespace http

} // namespace ehe