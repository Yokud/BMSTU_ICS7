#ifndef TXT_TO_BIN_H
#define TXT_TO_BIN_H

#include "products.h"
#include "files.h"

typedef char filename[51];

void delete_txt_extention(filename name, char *txt_name);
int txt_to_bin(FILE *txt, char *txt_name, FILE *bin);
void fscan_prod(FILE *f, product *prod);
int fread_line(FILE *f, char *s, size_t n);
size_t count_of_prods_in_txt(FILE *txt);

#endif