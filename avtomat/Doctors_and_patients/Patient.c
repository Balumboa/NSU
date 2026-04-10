#include "Patient.h"

#include <stdio.h>
#include <stdlib.h>

#include "Doctor.h"
#include "str.h"

typedef struct Patient Patient;

typedef struct Doctor Doctor;

Patient *create_pat() {
    Patient *pat = (Patient *)malloc(sizeof(Patient));
    printf("Введите ID пациента: ");
    scanf("%d", &pat->ID);
    printf("Введите имя пациента: ");
    pat->name = get_string(30);
    printf("Введите нужный текст: ");
    pat->text = get_string(100);
    pat->doc = NULL;
    return pat;
}

void delete_pat(Patient **pat) {
    if ((*pat)->doc != NULL) {
        erasePatient_from_doc((*pat)->doc, *pat);
    }
    free((*pat)->name);
    free((*pat)->text);
    free(*pat);
}

void print_info_pat(Patient *pat) {
    printf("==========ИНФОРМАЦИЯ ПРО ПАЦИЕНТА==========\n");
    printf("ID Пациента: %d\n", pat->ID);
    printf("Имя Пациента: ");
    print_string(pat->name);
    printf("Текст Пациента: ");
    print_string(pat->text);
    printf("Лечащий доктор: %s\n", (pat->doc != NULL)
                                       ? pat->doc->name
                                       : "Пока лечащий врач не назначен");
}

void setDoctor(Doctor *doc, Patient *pat) {
    if (doc == NULL) {
        pat->doc = doc;
        return;
    } else if (pat->doc != NULL) {
        erasePatient_from_doc(pat->doc, pat);
    }
    addPatient_to_doc(doc, pat);
}