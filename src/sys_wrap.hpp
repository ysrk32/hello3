/**
 * システムコールラッパー
 */

#pragma once

#include <fcntl.h>
#include <unistd.h>

int wrap_open(char const* path, int flags, ...);
ssize_t wrap_read(int fd, void* buf, size_t count);
