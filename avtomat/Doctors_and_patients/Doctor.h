#ifndef DOCTOR_H
#define DOCTOR_H

typedef struct Doctor Doctor;

typedef struct Patient Patient;

struct Doctor {
    int ID;
    char *name;
    char *text;
    int count;
    int capacity;
    struct Patient **patients;
};

Doctor *create_doc();

void delete_doc(Doctor **doc);

void print_info_doc(Doctor *doc);

void addPatient_to_doc(Doctor *doc, Patient *pat);

void erasePatient_from_doc(Doctor *doc, Patient *pat);

#endif