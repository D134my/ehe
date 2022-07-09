cmake_minimum_required(VERSION 3.14)
project(ehe LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost  COMPONENTS  REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()



add_executable(ehe
  ehe.hpp result_type.hpp 
  get.cpp get.hpp
  http.cpp http.hpp
  https.cpp https.hpp
  url.hpp url.cpp
  request.hpp request.cpp 
  main.cpp 
)

target_link_libraries(ehe ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

