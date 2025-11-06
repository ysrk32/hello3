#pragma once

#include <fcntl.h>
#include <unistd.h>

struct PosixApi {
  virtual int open(const char* path, int flags) = 0;
  virtual int open(const char* path, int flags, mode_t mode) = 0;
  virtual ssize_t read(int fd, void* buf, size_t count) = 0;
  virtual ~PosixApi() = default;
};

struct RealPosixApi : PosixApi {
  int open(const char* path, int flags) override { return ::open(path, flags); }

  int open(const char* path, int flags, mode_t mode) override {
    return ::open(path, flags, mode);
  }

  ssize_t read(int fd, void* buf, size_t count) override {
    return ::read(fd, buf, count);
  }
};

extern PosixApi* g_posix_api;
