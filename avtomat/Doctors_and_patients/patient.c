#include "patient.h"

#include <stdlib.h>
#include <string.h>

Patient* createPatient(int id, const char* name, int age, int doctorId) {
    Patient* p = (Patient*)malloc(sizeof(Patient));

    p->id = id;
    strcpy(p->name, name);
    p->age = age;
    p->doctorId = doctorId;

    return p;
}

void editPatient(Patient* p, const char* newName, int newAge, int newDoctorId) {
    if (newName)
        strcpy(p->name, newName);
    if (newAge > 0)
        p->age = newAge;
    if (newDoctorId >= 0)
        p->doctorId = newDoctorId;
}

void printPatient(const Patient* p) {
    printf("Patient ID: %d | Name: %s | Age: %d | Doctor ID: %d\n", p->id,
           p->name, p->age, p->doctorId);
}

void freePatient(Patient* p) {
    if (p)
        free(p);
}

// Функция сравнения для сортировки по doctorId (для qsort)
int comparePatientsByDoctorId(const void* a, const void* b) {
    Patient* pa = (Patient*)a;
    Patient* pb = (Patient*)b;
    return pa->doctorId - pb->doctorId;
}

// Функция сравнения по id
int comparePatientsById(const void* a, const void* b) {
    Patient* pa = (Patient*)a;
    Patient* pb = (Patient*)b;
    return pa->id - pb->id;
}