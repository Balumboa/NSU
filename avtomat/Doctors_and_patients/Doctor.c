#include "Doctor.h"

#include <stdio.h>
#include <stdlib.h>

#include "Patient.h"
#include "str.h"

/*
struct Doctor {
    int ID;
    char name[30];
    char text[100];
    int count;
    int capacity;
    struct Patient **patients;
};
*/

Doctor *create_doc() {
    Doctor *doc = (Doctor *)malloc(sizeof(Doctor));
    printf("Введите ID доктора: ");
    scanf("%d", &doc->ID);
    printf("Введите имя доктора: ");
    doc->name = get_string(30);
    printf("Введите нужный текст: ");
    doc->text = get_string(100);
    doc->count = 0;
    doc->capacity = 10;
    doc->patients = (Patient **)calloc(10, sizeof(Patient *));
    return doc;
}

void delete_doc(Doctor **doc) {
    free((*doc)->name);
    free((*doc)->text);
    for (int i = 0; i < (*doc)->count; i++) {
        (*doc)->patients[i]->doc = NULL;
    }
    free((*doc)->patients);
    free(*doc);
}

void print_info_doc(Doctor *doc) {
    printf("==========ИНФОРМАЦИЯ ПРО ДОКТОРА==========\n");
    printf("ID Доктора: %d\n", doc->ID);
    printf("Имя Доктора: ");
    print_string(doc->name);
    printf("Текст Доктора: ");
    print_string(doc->text);
    printf("Количество Пациентов: %d\n", doc->count);
    printf("Список Пациентов: ");
    for (int i = 0; i < doc->count; i++) {
        printf("%s ", doc->patients[i]->name);
    }
    printf("\n");
}

void addPatient_to_doc(Doctor *doc, Patient *pat) {
    if (pat->doc != doc) {
        if (doc->count == doc->capacity) {
            doc->capacity = 2 * doc->capacity + 1;
            doc->patients = (Patient **)realloc(
                doc->patients, doc->capacity * sizeof(Patient *));
        }
        doc->patients[doc->count] = pat;
        doc->count++;
        pat->doc = doc;
    }
}

void erasePatient_from_doc(Doctor *doc, Patient *pat) {
    if (doc != NULL) {
        for (int i = 0; i < doc->count - 1; i++) {
            if (doc->patients[i]->ID == pat->ID) {
                Patient *c = doc->patients[i];
                doc->patients[i] = doc->patients[i + 1];
                doc->patients[i + 1] = c;
            }
        }
        if (doc->patients[doc->count - 1]->ID == pat->ID) {
            doc->count--;
        }
    }
}