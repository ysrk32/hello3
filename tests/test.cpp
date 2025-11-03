#include <catch2/catch_test_macros.hpp>
#include <catch2/trompeloeil.hpp>

#include "func.hpp"
#include "mock_sys_wrap.hpp"

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("DummyFunction opens file correctly") {
  REQUIRE_CALL(syscall_mock,
               wrap_open_impl(trompeloeil::eq(std::string("test_input")),
                              O_RDONLY, trompeloeil::_))
      .RETURN(42);

  REQUIRE(DummyFunction("test_input") == 42);
}
