#include "func.h"

#include "posix_api.h"

unsigned Factorial(unsigned number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

int DummyFunction(const std::string& input) {
  return g_posix_api->open(input.c_str(), O_RDONLY);
}
