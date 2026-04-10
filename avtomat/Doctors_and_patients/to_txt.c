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

    // Записываем количество докторов
    fprintf(f, "%d\n", base_docs->count);

    // Записываем докторов
    for (int i = 0; i < base_docs->count; i++) {
        Doctor *doc = base_docs->doctors[i];
        fprintf(f, "%d\n", doc->ID);
        fprintf(f, "%s\n", doc->name);
        fprintf(f, "%s\n", doc->text);
        fprintf(f, "%d\n", doc->count);

        // Записываем ID пациентов через пробел
        for (int j = 0; j < doc->count; j++) {
            fprintf(f, "%d ", doc->patients[j]->ID);
        }
        fprintf(f, "\n");
    }

    // Записываем количество пациентов
    fprintf(f, "%d\n", base_pats->count);

    // Записываем пациентов
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

    // Читаем количество докторов
    fscanf(f, "%d", &n);
    fgetc(f);

    // Читаем докторов
    for (int i = 0; i < n; i++) {
        Doctor *doc = (Doctor *)malloc(sizeof(Doctor));
        doc->patients = (Patient **)calloc(10, sizeof(Patient *));
        doc->count = 0;
        doc->capacity = 10;

        // Читаем ID
        fscanf(f, "%d", &doc->ID);
        fgetc(f);

        // Читаем имя
        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        doc->name = strdup(buffer);

        // Читаем текст
        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        doc->text = strdup(buffer);

        // Читаем количество пациентов
        fscanf(f, "%d", &doc->count);
        fgetc(f);

        // Читаем ID пациентов (пропускаем, связи восстановим позже)
        fgets(buffer, sizeof(buffer), f);

        // Добавляем в базу
        if (base_docs->count >= base_docs->capacity) {
            base_docs->capacity *= 2;
            base_docs->doctors = (Doctor **)realloc(
                base_docs->doctors, base_docs->capacity * sizeof(Doctor *));
        }
        base_docs->doctors[base_docs->count] = doc;
        base_docs->count++;
    }

    // Читаем количество пациентов
    fscanf(f, "%d", &m);
    fgetc(f);

    // Читаем пациентов
    for (int i = 0; i < m; i++) {
        Patient *pat = (Patient *)malloc(sizeof(Patient));
        int doctor_id;

        // Читаем ID
        fscanf(f, "%d", &pat->ID);
        fgetc(f);

        // Читаем имя
        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        pat->name = strdup(buffer);

        // Читаем текст
        fgets(buffer, sizeof(buffer), f);
        buffer[strcspn(buffer, "\n")] = 0;
        pat->text = strdup(buffer);

        // Читаем ID доктора
        fscanf(f, "%d", &doctor_id);
        fgetc(f);

        pat->doc = NULL;

        // Добавляем в базу
        if (base_pats->count >= base_pats->capacity) {
            base_pats->capacity *= 2;
            base_pats->patients = (Patient **)realloc(
                base_pats->patients, base_pats->capacity * sizeof(Patient *));
        }
        base_pats->patients[base_pats->count] = pat;
        base_pats->count++;

        // Восстанавливаем связь с доктором
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

// void print_to_file(BaseoDocs *base_docs, BaseoPats *base_pats,
//                    const char *filename) {
//     FILE *f = fopen(filename, "w");
//     if (!f) {
//         printf("Ошибка создания файла для печати\n");
//         return;
//     }

//     fprintf(
//         f,
//         "==================== МЕДИЦИНСКАЯ БАЗА ДАННЫХ
//         ====================\n");
//     fprintf(f, "Дата печати: %s\n\n", __DATE__);

//     // Печатаем докторов
//     fprintf(f, "ДОКТОРА (всего: %d)\n", base_docs->count);
//     fprintf(f, "------------------------------------------------\n");

//     for (int i = 0; i < base_docs->count; i++) {
//         Doctor *doc = base_docs->doctors[i];
//         fprintf(f, "\n%d. ID: %d\n", i + 1, doc->ID);
//         fprintf(f, "   Имя: %s\n", doc->name);
//         fprintf(f, "   Специализация: %s\n", doc->text);
//         fprintf(f, "   Пациентов: %d\n", doc->count);

//         if (doc->count > 0) {
//             fprintf(f, "   Список пациентов: ");
//             for (int j = 0; j < doc->count; j++) {
//                 fprintf(f, "%s", doc->patients[j]->name);
//                 if (j < doc->count - 1)
//                     fprintf(f, ", ");
//             }
//             fprintf(f, "\n");
//         }
//     }

//     // Печатаем пациентов
//     fprintf(f, "\n\nПАЦИЕНТЫ (всего: %d)\n", base_pats->count);
//     fprintf(f, "------------------------------------------------\n");

//     for (int i = 0; i < base_pats->count; i++) {
//         Patient *pat = base_pats->patients[i];
//         fprintf(f, "\n%d. ID: %d\n", i + 1, pat->ID);
//         fprintf(f, "   Имя: %s\n", pat->name);
//         fprintf(f, "   Жалобы: %s\n", pat->text);
//         fprintf(f, "   Лечащий врач: %s\n",
//                 pat->doc ? pat->doc->name : "Не назначен");
//     }

//     fprintf(f, "\n==================== КОНЕЦ ДОКУМЕНТА
//     ====================\n"); fclose(f);

//     printf("Данные отправлены на печать (файл: %s)\n", filename);
// }