#include "sys_wrap.hpp"

#include <cstdarg>

int wrap_open(char const* path, int flags, ...) {
  if (flags & O_CREAT) {
    va_list ap;
    va_start(ap, flags);
    mode_t mode = va_arg(ap, mode_t);
    va_end(ap);
    return ::open(path, flags, mode);
  } else {
    return ::open(path, flags);
  }
}

ssize_t wrap_read(int fd, void* buf, size_t count) {
  return ::read(fd, buf, count);
}
