#ifndef DATABASE_H
#define DATABASE_H

#include "doctor.h"
#include "patient.h"

// ============ ОСНОВНЫЕ ФУНКЦИИ ============

// Текстовая работа с пациентами
int savePatientsToText(const char* filename, Patient* patients, int count);
int loadPatientsFromText(const char* filename, Patient** patients, int* count);

// Текстовая работа с докторами
int saveDoctorsToText(const char* filename, Doctor* doctors, int count);
int loadDoctorsFromText(const char* filename, Doctor** doctors, int* count);

// Бинарная работа с пациентами
int savePatientsToBinary(const char* filename, Patient* patients, int count);
int loadPatientsFromBinary(const char* filename, Patient** patients,
                           int* count);

// Бинарная работа с докторами
int saveDoctorsToBinary(const char* filename, Doctor* doctors, int count);
int loadDoctorsFromBinary(const char* filename, Doctor** doctors, int* count);

// ============ ПОИСК БЕЗ ЗАГРУЗКИ В ПАМЯТЬ ============

// Поиск пациента по ID доктора (O(log n) с использованием бинарного поиска)
int findPatientByDoctorInBinary(const char* filename, int doctorId,
                                Patient* result);

// Поиск доктора по ID пациента (O(log n))
int findDoctorByPatientInBinary(const char* filename, int patientId,
                                Doctor* result);

// ============ СОРТИРОВКА ФАЙЛОВ ДЛЯ БИНАРНОГО ПОИСКА ============

// Сортировка бинарного файла пациентов по полю doctorId
int sortPatientsFileByDoctorId(const char* filename);

// Сортировка бинарного файла докторов по полю id
int sortDoctorsFileById(const char* filename);

#endif