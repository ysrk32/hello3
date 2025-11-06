#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

#include "func.h"
#include "posix_api.h"

RealPosixApi real_posix_api;
PosixApi* g_posix_api = &real_posix_api;

int main(int argc, char* argv[]) {
  CLI::App app{"Factorial Calculator"};
  std::string file;
  app.add_option("file", file, "Input file")->required();
  CLI11_PARSE(app, argc, argv);

  std::cout << "Factorial of 5 is " << Factorial(5) << std::endl;

  DummyFunction(file);

  return 0;
}
