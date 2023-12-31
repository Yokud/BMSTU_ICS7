#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OK 0
#define ALLOCATION_ERROR 2

char *join_path(const char *base, const char *const file);

int print_dir_fork(const char *const filename, size_t offset, ino_t inode);

char *get_dynamic_str(const char *const string, const size_t size);

#endif
