#include "doctor.h"

#include <stdlib.h>
#include <string.h>

Doctor* createDoctor(int id, const char* name, const char* specialization) {
    Doctor* d = (Doctor*)malloc(sizeof(Doctor));
    if (!d)
        return NULL;

    d->id = id;
    strcpy(d->name, name);
    strcpy(d->specialization, specialization);
    d->patientCount = 0;

    // Инициализируем массив пациентов
    for (int i = 0; i < MAX_PATIENTS; i++) {
        d->patientIds[i] = -1;
    }

    return d;
}

void addPatientToDoctor(Doctor* d, int patientId) {
    if (!d || d->patientCount >= MAX_PATIENTS)
        return;

    // Проверяем, нет ли уже такого пациента
    for (int i = 0; i < d->patientCount; i++) {
        if (d->patientIds[i] == patientId)
            return;
    }

    d->patientIds[d->patientCount++] = patientId;
}

void removePatientFromDoctor(Doctor* d, int patientId) {
    if (!d)
        return;

    for (int i = 0; i < d->patientCount; i++) {
        if (d->patientIds[i] == patientId) {
            // Сдвигаем оставшихся пациентов
            for (int j = i; j < d->patientCount - 1; j++) {
                d->patientIds[j] = d->patientIds[j + 1];
            }
            d->patientCount--;
            d->patientIds[d->patientCount] = -1;
            break;
        }
    }
}

void editDoctor(Doctor* d, const char* newName, const char* newSpecialization) {
    if (!d)
        return;

    if (newName)
        strcpy(d->name, newName);
    if (newSpecialization)
        strcpy(d->specialization, newSpecialization);
}

void printDoctor(const Doctor* d) {
    if (!d)
        return;

    printf("Doctor ID: %d | Name: %s | Specialization: %s | Patients: ", d->id,
           d->name, d->specialization);

    for (int i = 0; i < d->patientCount; i++) {
        printf("%d ", d->patientIds[i]);
    }
    printf("\n");
}

void freeDoctor(Doctor* d) {
    if (d)
        free(d);
}

int compareDoctorsById(const void* a, const void* b) {
    Doctor* da = (Doctor*)a;
    Doctor* db = (Doctor*)b;
    return da->id - db->id;
}