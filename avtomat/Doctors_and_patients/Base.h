#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <stdlib.h>

#include "Doctor.h"
#include "Patient.h"

typedef struct BaseoDocs BaseoDocs;

typedef struct BaseoPats BaseoPats;

struct BaseoDocs {
    Doctor **doctors;
    int count;
    int capacity;
};

struct BaseoPats {
    Patient **patients;
    int count;
    int capacity;
};

void get_info_docs(BaseoDocs *base);

void get_info_pats(BaseoPats *base);

BaseoDocs *createBaseDocs();

BaseoPats *createBasePats();

void delete_base_of_docs(BaseoDocs **base);

void delete_base_of_pats(BaseoPats **base);

void sort_docs(BaseoDocs *base);

void sort_pats(BaseoPats *base);

void addDoctor(BaseoDocs *base);

void addPatient(BaseoPats *base);

Doctor *findDoc(BaseoDocs *base, int ID);

Patient *findPat(BaseoPats *base, int ID);

void eraseDoctor(BaseoDocs *base, int ID);

void erasePatient(BaseoPats *base, int ID);

#endif