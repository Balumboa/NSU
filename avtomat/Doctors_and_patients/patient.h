#ifndef PATIENT_H
#define PATIENT_H

#include <stdio.h>

// Структура пациента
typedef struct Patient {
    int id;          // уникальный ID пациента
    char name[100];  // ФИО пациента
    int age;         // возраст
    int doctorId;    // ID лечащего врача (для связи)
} Patient;

Patient* createPatient(int id, const char* name, int age, int doctorId);
void editPatient(Patient* p, const char* newName, int newAge, int newDoctorId);
void printPatient(const Patient* p);
void freePatient(Patient* p);
int comparePatientsByDoctorId(const void* a, const void* b);
int comparePatientsById(const void* a, const void* b);

#endif