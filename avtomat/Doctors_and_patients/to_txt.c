#include "to_txt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Doctor.h"
#include "Patient.h"

void save_to_txt(BaseoDocs *base_docs, BaseoPats *base_pats,
                 const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    fprintf(f, "%d\n", base_docs->count);

    for (int i = 0; i < base_docs->count; i++) {
        Doctor *doc = base_docs->doctors[i];
        fprintf(f, "%d\n", doc->ID);
        fprintf(f, "%s\n", doc->name);
        fprintf(f, "%s\n", doc->text);
        fprintf(f, "%d\n", doc->count);

        for (int j = 0; j < doc->count; j++) {
            fprintf(f, "%d ", doc->patients[j]->ID);
        }
        fprintf(f, "\n");
    }

    fprintf(f, "%d\n", base_pats->count);

    for (int i = 0; i < base_pats->count; i++) {
        Patient *pat = base_pats->patients[i];
        fprintf(f, "%d\n", pat->ID);
        fprintf(f, "%s\n", pat->name);
        fprintf(f, "%s\n", pat->text);

        // ID лечащего врача (или -1 если нет)
        int doc_id = (pat->doc != NULL) ? pat->doc->ID : -1;
        fprintf(f, "%d\n", doc_id);
    }

    fclose(f);
    printf("Данные сохранены в файл %s\n", filename);
}

void load_from_txt(BaseoDocs *base_docs, BaseoPats *base_pats,
                   const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Ошибка открытия файла %s\n", filename);
        return;
    }

    int n, m;
    char buffer[256];
    fscanf(f, "%d", &n);
    fgetc(f);

    for (int i = 0; i < n; i++) {
        Doctor *doc = (Doctor *)malloc(sizeof(Doctor));
        doc->patients = (Patient **)calloc(10, sizeof(Patient *));
        doc->count = 0;
        doc->capacity = 10;

        fscanf(f, "%d", &doc->ID);
        fgetc(f);

        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        doc->name = strdup(buffer);

        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        doc->text = strdup(buffer);

        int saved_count;
        fscanf(f, "%d", &saved_count);
        fgetc(f);
        fgets(buffer, sizeof(buffer), f);

        doc->count = 0;

        // Добавляем в базу
        if (base_docs->count >= base_docs->capacity) {
            base_docs->capacity *= 2;
            base_docs->doctors = (Doctor **)realloc(
                base_docs->doctors, base_docs->capacity * sizeof(Doctor *));
        }
        base_docs->doctors[base_docs->count] = doc;
        base_docs->count++;
    }

    fscanf(f, "%d", &m);
    fgetc(f);

    for (int i = 0; i < m; i++) {
        Patient *pat = (Patient *)malloc(sizeof(Patient));
        int doctor_id;

        fscanf(f, "%d", &pat->ID);
        fgetc(f);

        // Читаем имя
        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        pat->name = strdup(buffer);

        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        pat->text = strdup(buffer);

        fscanf(f, "%d", &doctor_id);
        fgetc(f);

        pat->doc = NULL;

        if (base_pats->count >= base_pats->capacity) {
            base_pats->capacity *= 2;
            base_pats->patients = (Patient **)realloc(
                base_pats->patients, base_pats->capacity * sizeof(Patient *));
        }
        base_pats->patients[base_pats->count] = pat;
        base_pats->count++;

        if (doctor_id != -1) {
            Doctor *doc = findDoc(base_docs, doctor_id);
            if (doc) {
                addPatient_to_doc(doc, pat);
            }
        }
    }

    fclose(f);
    printf("Загружено %d докторов и %d пациентов из файла %s\n", n, m,
           filename);
}