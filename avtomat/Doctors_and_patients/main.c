#include <stdio.h>
#include <stdlib.h>

#include "database.h"
#include "doctor.h"
#include "patient.h"

void printMenu() {
    printf("\n========== MEDICAL DATABASE ==========\n");
    printf("1. Add patient\n");
    printf("2. Add doctor\n");
    printf("3. Show all patients\n");
    printf("4. Show all doctors\n");
    printf("5. Save to text files\n");
    printf("6. Load from text files\n");
    printf("7. Save to binary files\n");
    printf("8. Load from binary files\n");
    printf("9. Sort binary files for fast search\n");
    printf("10. Find patient by doctor (binary search in file)\n");
    printf("11. Find doctor by patient (sequential in file)\n");
    printf("0. Exit\n");
    printf("=====================================\n");
    printf("Your choice: ");
}

int main() {
    Patient* patients = NULL;
    Doctor* doctors = NULL;
    int patientCount = 0;
    int doctorCount = 0;

    int choice;
    int id, age, doctorId;
    char name[100], spec[50];

    do {
        printMenu();
        scanf("%d", &choice);
        getchar();  // очистка буфера

        switch (choice) {
            case 1:  // Добавить пациента
                printf("Enter patient ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter patient name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter patient age: ");
                scanf("%d", &age);
                printf("Enter doctor ID: ");
                scanf("%d", &doctorId);

                // Добавляем в массив
                patients = (Patient*)realloc(
                    patients, sizeof(Patient) * (patientCount + 1));
                patients[patientCount].id = id;
                strcpy(patients[patientCount].name, name);
                patients[patientCount].age = age;
                patients[patientCount].doctorId = doctorId;
                patientCount++;

                printf("Patient added successfully!\n");
                break;

            case 2:  // Добавить доктора
                printf("Enter doctor ID: ");
                scanf("%d", &id);
                getchar();
                printf("Enter doctor name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter specialization: ");
                fgets(spec, sizeof(spec), stdin);
                spec[strcspn(spec, "\n")] = 0;

                doctors = (Doctor*)realloc(doctors,
                                           sizeof(Doctor) * (doctorCount + 1));
                doctors[doctorCount].id = id;
                strcpy(doctors[doctorCount].name, name);
                strcpy(doctors[doctorCount].specialization, spec);
                doctors[doctorCount].patientCount = 0;
                doctorCount++;

                printf("Doctor added successfully!\n");
                break;

            case 3:  // Показать всех пациентов
                printf("\n=== ALL PATIENTS ===\n");
                for (int i = 0; i < patientCount; i++) {
                    printPatient(&patients[i]);
                }
                break;

            case 4:  // Показать всех докторов
                printf("\n=== ALL DOCTORS ===\n");
                for (int i = 0; i < doctorCount; i++) {
                    printDoctor(&doctors[i]);
                }
                break;

            case 5:  // Сохранить в текстовые файлы
                if (savePatientsToText("patients.txt", patients,
                                       patientCount)) {
                    printf("Patients saved to patients.txt\n");
                }
                if (saveDoctorsToText("doctors.txt", doctors, doctorCount)) {
                    printf("Doctors saved to doctors.txt\n");
                }
                break;

            case 6:  // Загрузить из текстовых файлов
                if (loadPatientsFromText("patients.txt", &patients,
                                         &patientCount)) {
                    printf("Patients loaded from patients.txt (%d records)\n",
                           patientCount);
                }
                if (loadDoctorsFromText("doctors.txt", &doctors,
                                        &doctorCount)) {
                    printf("Doctors loaded from doctors.txt (%d records)\n",
                           doctorCount);
                }
                break;

            case 7:  // Сохранить в бинарные файлы
                if (savePatientsToBinary("patients.bin", patients,
                                         patientCount)) {
                    printf("Patients saved to patients.bin\n");
                }
                if (saveDoctorsToBinary("doctors.bin", doctors, doctorCount)) {
                    printf("Doctors saved to doctors.bin\n");
                }
                break;

            case 8:  // Загрузить из бинарных файлов
                if (loadPatientsFromBinary("patients.bin", &patients,
                                           &patientCount)) {
                    printf("Patients loaded from patients.bin (%d records)\n",
                           patientCount);
                }
                if (loadDoctorsFromBinary("doctors.bin", &doctors,
                                          &doctorCount)) {
                    printf("Doctors loaded from doctors.bin (%d records)\n",
                           doctorCount);
                }
                break;

            case 9:  // Сортировка для быстрого поиска
                if (sortPatientsFileByDoctorId("patients.bin")) {
                    printf("Patients file sorted by doctor ID\n");
                }
                if (sortDoctorsFileById("doctors.bin")) {
                    printf("Doctors file sorted by ID\n");
                }
                break;

            case 10:  // Поиск пациента по доктору (бинарный поиск)
                printf("Enter doctor ID: ");
                scanf("%d", &doctorId);
                Patient foundPatient;
                if (findPatientByDoctorInBinary("patients.bin", doctorId,
                                                &foundPatient)) {
                    printf("Found patient:\n");
                    printPatient(&foundPatient);
                } else {
                    printf("No patient found for doctor ID %d\n", doctorId);
                }
                break;

            case 11:  // Поиск доктора по пациенту
                printf("Enter patient ID: ");
                scanf("%d", &id);
                Doctor foundDoctor;
                if (findDoctorByPatientInBinary("doctors.bin", id,
                                                &foundDoctor)) {
                    printf("Found doctor:\n");
                    printDoctor(&foundDoctor);
                } else {
                    printf("No doctor found for patient ID %d\n", id);
                }
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    // Очистка памяти
    free(patients);
    free(doctors);

    return 0;
}