#include "database.h"

#include <stdlib.h>
#include <string.h>

// ============ ТЕКСТОВАЯ РАБОТА С ПАЦИЕНТАМИ ============

int savePatientsToText(const char* filename, Patient* patients, int count) {
    FILE* f = fopen(filename, "w");
    if (!f)
        return 0;

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%d|%d\n", patients[i].id, patients[i].name,
                patients[i].age, patients[i].doctorId);
    }

    fclose(f);
    return 1;
}

int loadPatientsFromText(const char* filename, Patient** patients, int* count) {
    FILE* f = fopen(filename, "r");
    if (!f)
        return 0;

    // Временный массив для чтения
    Patient* tempArray = NULL;
    int capacity = 10;
    int size = 0;

    tempArray = (Patient*)malloc(sizeof(Patient) * capacity);
    if (!tempArray) {
        fclose(f);
        return 0;
    }

    char line[200];
    while (fgets(line, sizeof(line), f)) {
        if (size >= capacity) {
            capacity *= 2;
            tempArray =
                (Patient*)realloc(tempArray, sizeof(Patient) * capacity);
            if (!tempArray) {
                fclose(f);
                return 0;
            }
        }

        // Парсим строку: id|name|age|doctorId
        sscanf(line, "%d|%[^|]|%d|%d", &tempArray[size].id,
               tempArray[size].name, &tempArray[size].age,
               &tempArray[size].doctorId);
        size++;
    }

    *patients = tempArray;
    *count = size;

    fclose(f);
    return 1;
}

// ============ ТЕКСТОВАЯ РАБОТА С ДОКТОРАМИ ============

int saveDoctorsToText(const char* filename, Doctor* doctors, int count) {
    FILE* f = fopen(filename, "w");
    if (!f)
        return 0;

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%s|", doctors[i].id, doctors[i].name,
                doctors[i].specialization);

        // Записываем пациентов
        for (int j = 0; j < doctors[i].patientCount; j++) {
            fprintf(f, "%d", doctors[i].patientIds[j]);
            if (j < doctors[i].patientCount - 1)
                fprintf(f, ",");
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

int loadDoctorsFromText(const char* filename, Doctor** doctors, int* count) {
    FILE* f = fopen(filename, "r");
    if (!f)
        return 0;

    Doctor* tempArray = NULL;
    int capacity = 10;
    int size = 0;

    tempArray = (Doctor*)malloc(sizeof(Doctor) * capacity);
    if (!tempArray) {
        fclose(f);
        return 0;
    }

    char line[500];
    while (fgets(line, sizeof(line), f)) {
        if (size >= capacity) {
            capacity *= 2;
            tempArray = (Doctor*)realloc(tempArray, sizeof(Doctor) * capacity);
            if (!tempArray) {
                fclose(f);
                return 0;
            }
        }

        char patientsStr[300];
        // Парсим строку: id|name|specialization|patients
        sscanf(line, "%d|%[^|]|%[^|]|%s", &tempArray[size].id,
               tempArray[size].name, tempArray[size].specialization,
               patientsStr);

        // Парсим список пациентов
        tempArray[size].patientCount = 0;
        char* token = strtok(patientsStr, ",");
        while (token != NULL && tempArray[size].patientCount < MAX_PATIENTS) {
            tempArray[size].patientIds[tempArray[size].patientCount++] =
                atoi(token);
            token = strtok(NULL, ",");
        }

        size++;
    }

    *doctors = tempArray;
    *count = size;

    fclose(f);
    return 1;
}

// ============ БИНАРНАЯ РАБОТА С ПАЦИЕНТАМИ ============

int savePatientsToBinary(const char* filename, Patient* patients, int count) {
    FILE* f = fopen(filename, "wb");
    if (!f)
        return 0;

    // Сначала записываем количество записей
    fwrite(&count, sizeof(int), 1, f);
    // Затем все структуры
    fwrite(patients, sizeof(Patient), count, f);

    fclose(f);
    return 1;
}

int loadPatientsFromBinary(const char* filename, Patient** patients,
                           int* count) {
    FILE* f = fopen(filename, "rb");
    if (!f)
        return 0;

    // Читаем количество записей
    fread(count, sizeof(int), 1, f);

    // Выделяем память
    *patients = (Patient*)malloc(sizeof(Patient) * (*count));
    if (!*patients) {
        fclose(f);
        return 0;
    }

    // Читаем все структуры
    fread(*patients, sizeof(Patient), *count, f);

    fclose(f);
    return 1;
}

// ============ БИНАРНАЯ РАБОТА С ДОКТОРАМИ ============

int saveDoctorsToBinary(const char* filename, Doctor* doctors, int count) {
    FILE* f = fopen(filename, "wb");
    if (!f)
        return 0;

    fwrite(&count, sizeof(int), 1, f);
    fwrite(doctors, sizeof(Doctor), count, f);

    fclose(f);
    return 1;
}

int loadDoctorsFromBinary(const char* filename, Doctor** doctors, int* count) {
    FILE* f = fopen(filename, "rb");
    if (!f)
        return 0;

    fread(count, sizeof(int), 1, f);

    *doctors = (Doctor*)malloc(sizeof(Doctor) * (*count));
    if (!*doctors) {
        fclose(f);
        return 0;
    }

    fread(*doctors, sizeof(Doctor), *count, f);

    fclose(f);
    return 1;
}

// ============ СОРТИРОВКА БИНАРНЫХ ФАЙЛОВ ============

int sortPatientsFileByDoctorId(const char* filename) {
    // Загружаем всех пациентов
    Patient* patients;
    int count;

    if (!loadPatientsFromBinary(filename, &patients, &count)) {
        return 0;
    }

    // Сортируем в памяти
    qsort(patients, count, sizeof(Patient), comparePatientsByDoctorId);

    // Сохраняем обратно
    int result = savePatientsToBinary(filename, patients, count);

    free(patients);
    return result;
}

int sortDoctorsFileById(const char* filename) {
    Doctor* doctors;
    int count;

    if (!loadDoctorsFromBinary(filename, &doctors, &count)) {
        return 0;
    }

    qsort(doctors, count, sizeof(Doctor), compareDoctorsById);

    int result = saveDoctorsToBinary(filename, doctors, count);

    free(doctors);
    return result;
}

// ============ БИНАРНЫЙ ПОИСК В ФАЙЛЕ ============

// Бинарный поиск пациента по doctorId в отсортированном файле
int findPatientByDoctorInBinary(const char* filename, int doctorId,
                                Patient* result) {
    FILE* f = fopen(filename, "rb");
    if (!f)
        return 0;

    // Читаем количество записей
    int count;
    fread(&count, sizeof(int), 1, f);

    if (count == 0) {
        fclose(f);
        return 0;
    }

    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        // Перемещаемся к mid-записи
        // Пропускаем заголовок (sizeof(int)) + смещение до mid-записи
        long offset = sizeof(int) + mid * sizeof(Patient);
        fseek(f, offset, SEEK_SET);

        Patient temp;
        fread(&temp, sizeof(Patient), 1, f);

        if (temp.doctorId == doctorId) {
            *result = temp;
            fclose(f);
            return 1;
        } else if (temp.doctorId < doctorId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    fclose(f);
    return 0;
}

// Бинарный поиск доктора по ID (для последующего поиска пациента)
int findDoctorByIdInBinary(const char* filename, int doctorId, Doctor* result) {
    FILE* f = fopen(filename, "rb");
    if (!f)
        return 0;

    int count;
    fread(&count, sizeof(int), 1, f);

    if (count == 0) {
        fclose(f);
        return 0;
    }

    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        long offset = sizeof(int) + mid * sizeof(Doctor);
        fseek(f, offset, SEEK_SET);

        Doctor temp;
        fread(&temp, sizeof(Doctor), 1, f);

        if (temp.id == doctorId) {
            *result = temp;
            fclose(f);
            return 1;
        } else if (temp.id < doctorId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    fclose(f);
    return 0;
}

// Поиск доктора по ID пациента (нужно проверить всех пациентов доктора)
int findDoctorByPatientInBinary(const char* doctorsFile, int patientId,
                                Doctor* result) {
    FILE* f = fopen(doctorsFile, "rb");
    if (!f)
        return 0;

    int count;
    fread(&count, sizeof(int), 1, f);

    for (int i = 0; i < count; i++) {
        long offset = sizeof(int) + i * sizeof(Doctor);
        fseek(f, offset, SEEK_SET);

        Doctor temp;
        fread(&temp, sizeof(Doctor), 1, f);

        // Проверяем, есть ли у этого доктора нужный пациент
        for (int j = 0; j < temp.patientCount; j++) {
            if (temp.patientIds[j] == patientId) {
                *result = temp;
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}