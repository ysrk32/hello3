#include "func.hpp"

unsigned Factorial(unsigned number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}
