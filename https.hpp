#ifndef __ehe_https__
#define __ehe_https__

#include "result_type.hpp"
#include <atomic>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <functional>
#include <iostream>

namespace pl = std::placeholders;

class https_client {
public:
  https_client(boost::asio::io_context &ioc,
               boost::asio::ssl::stream<boost::asio::ip::tcp::socket> &socket,
               std::string const &host, std::string const &path,
               std::string const &request, std::atomic<bool> &expire);
  ehe::result_type get_result() const noexcept;

private:
  void resolve();
  void on_resolve(boost::system::error_code const &error,
                  boost::asio::ip::tcp::resolver::results_type results);

  void cancel_connection();

  void connect(boost::asio::ip::tcp::resolver::results_type const &results);
  void on_connect(boost::system::error_code const &error,
                  boost::asio::ip::tcp::endpoint const &ep);

  void handshake();
  void on_handshake(boost::system::error_code const &error);

  void write();
  void on_write(boost::system::error_code const &error,
                std::size_t bytes_transferred);

  void read();
  void on_read(boost::system::error_code const &error,
               std::size_t bytes_transferred);

  boost::asio::io_context &_ioc;
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket> &_socket;
  boost::asio::streambuf _response;
  std::string _request;
  std::string _host;
  boost::asio::ip::tcp::resolver _resolver;
  ehe::result_type _result;
  std::atomic<bool> &_expire;
};

#endif