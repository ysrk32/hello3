#include <CLI/CLI.hpp>
#include <iostream>
#include <string>

#include "func.hpp"

int main(int argc, char* argv[]) {
  CLI::App app{"Factorial Calculator"};
  std::string file;
  app.add_option("file", file, "Input file")->required();
  CLI11_PARSE(app, argc, argv);

  std::cout << "Factorial of 5 is " << Factorial(5) << std::endl;

  DummyFunction(file);

  return 0;
}
