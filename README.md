# ehe
 One Line HTTP Get ? ehe.

## Usage


```cpp

#include "ehe.hpp"
#include <iostream>

int main() {

  const ehe::result_type result = ehe::https::get(ehe::url("your url"));

  std::cout << result.text << std::endl;

  return 0;
}
```

## Dependencies

1. Boost.Asio
2. OpenSSL
