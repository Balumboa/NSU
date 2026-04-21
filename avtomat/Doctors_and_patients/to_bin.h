#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Base.h"
#include "Doctor.h"
#include "Patient.h"

typedef struct {
    int ID;
    int count;
    char name[30];
    char text[100];
    int ID_patients[20];
} Data_Doctor;

typedef struct {
    int ID;
    char name[30];
    char text[100];
    int ID_doctor;
} Data_Patient;

void save_patient_to_file(Patient *pat, int index);

Data_Patient get_patient_by_index(int index);

int find_patient_pos_by_id(int targetID);

void save_doctor_to_file(Doctor *src, int index);

Data_Doctor get_doctor_by_index(int index);

int find_doctor_pos_by_id(int targetID);

void base_docs_to_bin(BaseoDocs *base);

void base_pats_to_bin(BaseoPats *base);

void load_doctors_from_bin(BaseoDocs *docs);

void load_patients_from_bin(BaseoPats *pats, BaseoDocs *docs);