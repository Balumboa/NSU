#ifndef TO_TXT_H
#define TO_TXT_H

#include "Base.h"

void save_to_txt(BaseoDocs *base_docs, BaseoPats *base_pats,
                 const char *filename);

void load_from_txt(BaseoDocs *base_docs, BaseoPats *base_pats,
                   const char *filename);

void print_to_file(BaseoDocs *base_docs, BaseoPats *base_pats,
                   const char *filename);

#endif