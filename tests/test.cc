#include <catch2/catch_test_macros.hpp>
#include <catch2/trompeloeil.hpp>

#include "func.h"
#include "mock_posix_api.h"

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("DummyFunction opens file correctly") {
  MockPosixApi mock_posix_api;
  g_posix_api = &mock_posix_api;

  REQUIRE_CALL(mock_posix_api,
               open(trompeloeil::eq(std::string("test_input")), O_RDONLY))
      .RETURN(42);

  REQUIRE(DummyFunction("test_input") == 42);
}
