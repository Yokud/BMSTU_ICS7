#ifndef TXT_TO_BIN_H
#define TXT_TO_BIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char filename[16];

void delete_txt_extention(filename name, char *txt_name);
int txt_to_bin(FILE *txt, char *txt_name, FILE *bin);

#endif