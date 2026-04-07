#ifndef patient_H
#define patient_H

#include <stdio.h>
#include <stdlib.h>

#include "Doctor.h"
#include "str.h"

typedef struct Patient Patient;

struct Patient {
    int ID;
    char *name;
    char *text;
    Doctor *doc;
};

Patient *create_pat();

void delete_pat(Patient **pat);

void print_info_pat(Patient *pat);

void setDoctor(Doctor *doc, Patient *pat);
#endif