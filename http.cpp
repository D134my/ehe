#include "http.hpp"

http_client::http_client(boost::asio::io_context &ioc,
                         boost::asio::ip::tcp::socket &socket,
                         std::string const &host, std::string const &path,
                         std::string const &request, std::atomic<bool> &expire)
    : _ioc(ioc), _socket(socket), _host(host), _request(request),
      _resolver(ioc), _expire(expire) {

  _result.path = path;
  resolve();
}

void http_client::resolve() {

  _resolver.async_resolve(
      _host, "http", std::bind(&http_client::on_resolve, this, pl::_1, pl::_2));
}

void http_client::on_resolve(
    boost::system::error_code const &error,
    boost::asio::ip::tcp::resolver::results_type results) {
  if (error) {
    std::cerr << "Resolve Error : " << error.message() << std::endl;
    cancel_connection();
  }

  connect(results);
  _result.host_name = _host;
  _result.port = 443;
  ++results;

  _result.address = results->endpoint().address().to_string();
}

void http_client::cancel_connection() {
  boost::system::error_code ec;
  _socket.cancel(ec);
  _ioc.stop();
  std::exit(-1);
}

void http_client::connect(
    boost::asio::ip::tcp::resolver::results_type const &results) {
  boost::asio::async_connect(
      _socket, results,
      std::bind(&http_client::on_connect, this, pl::_1, pl::_2));
}

void http_client::on_connect(boost::system::error_code const &error,
                             boost::asio::ip::tcp::endpoint const &ep) {
  if (error) {
    std::cerr << "Connect Error : " << error.message() << std::endl;
    cancel_connection();
  }
  write();
}

void http_client::write() {
  boost::asio::async_write(
      _socket, boost::asio::buffer(_request),
      std::bind(&http_client::on_write, this, pl::_1, pl::_2));
}

void http_client::on_write(boost::system::error_code const &error,
                           std::size_t bytes_transferred) {
  if (error) {
    std::cerr << "Write Error : " << error.message() << std::endl;
    cancel_connection();
  }

  read();
}

void http_client::read() {

  boost::asio::async_read(
      _socket, _response,
      std::bind(&http_client::on_read, this, pl::_1, pl::_2));
}
void http_client::on_read(boost::system::error_code const &error,
                          std::size_t bytes_transferred) {

  if (!error) {
    std::cerr << "Read Error : " << error.message() << std::endl;
    cancel_connection();
  }

  std::ostringstream os;
  os << std::istream(&_response).rdbuf();

  _result.text = os.str();
  _expire.store(true);
}

ehe::result_type http_client::get_result() const noexcept { return _result; }
