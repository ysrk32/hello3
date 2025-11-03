#include "func.hpp"

#include <fcntl.h>

#include "sys_wrap.hpp"

unsigned Factorial(unsigned number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

int DummyFunction(const std::string& input) {
  int fd = wrap_open(input.c_str(), O_RDONLY);
  return fd;
}
