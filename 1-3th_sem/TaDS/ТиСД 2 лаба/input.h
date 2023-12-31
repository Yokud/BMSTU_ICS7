#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>

int fread_line(FILE *f, char s[], size_t n);
void input_string(char *msg, char *str, int max_len);
void input_number(char *msg, int *num, int beg, int end);
void input_bool(char *msg, int *num);
void input_type (char *msg, int *num);
void input_dur (char *msg, double *num, double beg, double end);

#endif
