#pragma once

#include <trompeloeil.hpp>

#include "sys_wrap.hpp"

struct syscall {
  MAKE_MOCK3(wrap_open_impl, int(char const*, int, mode_t mode));
  MAKE_MOCK3(wrap_read, ssize_t(int, void*, size_t));
};

extern struct syscall syscall_mock;
