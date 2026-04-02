#ifndef DOCTOR_H
#define DOCTOR_H

#include <stdio.h>

#define MAX_PATIENTS 100  // максимальное количество пациентов у одного доктора

// Структура доктора
typedef struct Doctor {
    int id;                        // уникальный ID доктора
    char name[100];                // ФИО доктора
    char specialization[50];       // специализация
    int patientIds[MAX_PATIENTS];  // массив ID пациентов
    int patientCount;              // количество пациентов
} Doctor;

// Прототипы функций
Doctor* createDoctor(int id, const char* name, const char* specialization);
void addPatientToDoctor(Doctor* d, int patientId);
void removePatientFromDoctor(Doctor* d, int patientId);
void editDoctor(Doctor* d, const char* newName, const char* newSpecialization);
void printDoctor(const Doctor* d);
void freeDoctor(Doctor* d);
int compareDoctorsById(const void* a, const void* b);

#endif