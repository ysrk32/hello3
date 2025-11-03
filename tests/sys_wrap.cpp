#include <cstdarg>

#include "mock_sys_wrap.hpp"

struct syscall syscall_mock;

int wrap_open(char const* path, int flags, ...) {
  if (flags & O_CREAT) {
    va_list ap;
    va_start(ap, flags);
    mode_t mode = va_arg(ap, mode_t);
    va_end(ap);
    return syscall_mock.wrap_open_impl(path, flags, mode);
  } else {
    return syscall_mock.wrap_open_impl(path, flags, 0);
  }
}

ssize_t wrap_read(int fd, void* buf, size_t count) {
  return syscall_mock.wrap_read(fd, buf, count);
}
