#ifndef SSCAN_H
#define SSCAN_H

#define __USE_MINGW_ANSI_STDIO 1
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define SSC_OVERFLOW 1
#define SSC_NDIGIT 2
#define SSC_EMPTY 3

int int_sscan(FILE *f, int *dst);

int bool_sscan(FILE *f, bool *dst);

#endif