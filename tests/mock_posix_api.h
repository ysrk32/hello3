#pragma once

#include <trompeloeil.hpp>

#include "posix_api.h"

struct MockPosixApi : PosixApi {
  MAKE_MOCK2(open, int(char const*, int));
  MAKE_MOCK3(open, int(char const*, int, mode_t mode));
  MAKE_MOCK3(read, ssize_t(int, void*, size_t));
};
