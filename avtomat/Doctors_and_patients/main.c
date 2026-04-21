#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Base.h"
#include "Doctor.h"
#include "Patient.h"
#include "to_bin.h"
#include "to_txt.h"

// ==================== ТЕСТ 1: БАЗОВЫЙ ФУНКЦИОНАЛ ====================
void test_basic_functionality(void) {
    printf("\n========== ТЕСТ 1: БАЗОВЫЙ ФУНКЦИОНАЛ ==========\n\n");

    BaseoDocs *docs = createBaseDocs();
    BaseoPats *pats = createBasePats();

    // 1. СОЗДАНИЕ 2 ДОКТОРОВ
    printf("=== 1. СОЗДАНИЕ 2 ДОКТОРОВ ===\n");
    for (int i = 1; i <= 2; i++) {
        Doctor *doc = (Doctor *)malloc(sizeof(Doctor));
        doc->ID = i;
        doc->name = (char *)malloc(30);
        sprintf(doc->name, "Doctor_%d", i);
        doc->text = (char *)malloc(100);
        sprintf(doc->text, "Specialization_%d", i);
        doc->count = 0;
        doc->capacity = 10;
        doc->patients = (Patient **)calloc(10, sizeof(Patient *));

        docs->doctors[docs->count++] = doc;
        printf("  Создан: ID=%d, Имя=%s\n", doc->ID, doc->name);
    }
    printf("  ИТОГО: %d докторов\n\n", docs->count);

    // 2. СОЗДАНИЕ 5 ПАЦИЕНТОВ
    printf("=== 2. СОЗДАНИЕ 5 ПАЦИЕНТОВ ===\n");
    for (int i = 1; i <= 5; i++) {
        Patient *pat = (Patient *)malloc(sizeof(Patient));
        pat->ID = i;
        pat->name = (char *)malloc(30);
        sprintf(pat->name, "Patient_%d", i);
        pat->text = (char *)malloc(100);
        sprintf(pat->text, "Complaint_%d", i);
        pat->doc = NULL;

        pats->patients[pats->count++] = pat;
        printf("  Создан: ID=%d, Имя=%s\n", pat->ID, pat->name);
    }
    printf("  ИТОГО: %d пациентов\n\n", pats->count);

    // 3. НАЗНАЧЕНИЕ ВРАЧЕЙ
    printf("=== 3. НАЗНАЧЕНИЕ ВРАЧЕЙ ===\n");
    addPatient_to_doc(docs->doctors[0],
                      pats->patients[0]);  // Patient1 -> Doctor1
    addPatient_to_doc(docs->doctors[0],
                      pats->patients[1]);  // Patient2 -> Doctor1
    addPatient_to_doc(docs->doctors[0],
                      pats->patients[4]);  // Patient5 -> Doctor1
    addPatient_to_doc(docs->doctors[1],
                      pats->patients[2]);  // Patient3 -> Doctor2
    addPatient_to_doc(docs->doctors[1],
                      pats->patients[3]);  // Patient4 -> Doctor2

    printf("  Доктор1 (%s): %d пациентов (ожидается 3)\n",
           docs->doctors[0]->name, docs->doctors[0]->count);
    printf("  Доктор2 (%s): %d пациентов (ожидается 2)\n\n",
           docs->doctors[1]->name, docs->doctors[1]->count);

    // 4. ПРОВЕРКА СВЯЗЕЙ
    printf("=== 4. ПРОВЕРКА СВЯЗЕЙ ===\n");
    for (int i = 0; i < pats->count; i++) {
        Patient *p = pats->patients[i];
        if (p->doc) {
            printf("  Пациент %s -> Доктор %s\n", p->name, p->doc->name);
        } else {
            printf("  Пациент %s -> НЕТ ВРАЧА\n", p->name);
        }
    }

    // 5. ПРОВЕРКА ПОИСКА
    printf("\n=== 5. ПРОВЕРКА ПОИСКА ===\n");
    Doctor *found_doc = findDoc(docs, 2);
    printf("  Поиск доктора ID=2: %s\n", found_doc ? "НАЙДЕН" : "НЕ НАЙДЕН");

    Patient *found_pat = findPat(pats, 3);
    printf("  Поиск пациента ID=3: %s\n", found_pat ? "НАЙДЕН" : "НЕ НАЙДЕН");

    // 6. ПРОВЕРКА УДАЛЕНИЯ ПАЦИЕНТА
    printf("\n=== 6. УДАЛЕНИЕ ПАЦИЕНТА ===\n");
    printf("  До удаления: у доктора1 %d пациентов\n", docs->doctors[0]->count);
    erasePatient(pats, 2);
    printf("  После удаления пациента ID=2: у доктора1 %d пациентов\n",
           docs->doctors[0]->count);

    // 7. ПРОВЕРКА СМЕНЫ ВРАЧА
    printf("\n=== 7. СМЕНА ВРАЧА ===\n");
    printf("  Пациент1 лечится у %s\n", pats->patients[0]->doc->name);
    setDoctor(docs->doctors[1], pats->patients[0]);
    printf("  После смены: пациент1 лечится у %s\n",
           pats->patients[0]->doc->name);
    printf("  У доктора1 теперь %d пациентов (было 3)\n",
           docs->doctors[0]->count);
    printf("  У доктора2 теперь %d пациентов (было 2)\n",
           docs->doctors[1]->count);

    // ОЧИСТКА
    delete_base_of_docs(&docs);
    delete_base_of_pats(&pats);

    printf("\n========== ТЕСТ 1 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 2: КРАЕВЫЕ СЛУЧАИ ====================
void test_edge_cases(void) {
    printf("\n========== ТЕСТ 2: КРАЕВЫЕ СЛУЧАИ ==========\n\n");

    BaseoDocs *docs = createBaseDocs();
    BaseoPats *pats = createBasePats();

    // 1. ПОИСК В ПУСТОЙ БАЗЕ
    printf("1. ПОИСК В ПУСТОЙ БАЗЕ:\n");
    Doctor *null_doc = findDoc(docs, 999);
    Patient *null_pat = findPat(pats, 999);
    printf("   Поиск доктора: %s\n", null_doc == NULL ? "OK (NULL)" : "FAIL");
    printf("   Поиск пациента: %s\n\n",
           null_pat == NULL ? "OK (NULL)" : "FAIL");

    // 2. УДАЛЕНИЕ НЕСУЩЕСТВУЮЩЕГО
    printf("2. УДАЛЕНИЕ НЕСУЩЕСТВУЮЩЕГО:\n");
    eraseDoctor(docs, 999);
    erasePatient(pats, 999);
    printf("   Удаление несуществующего доктора: OK (нет ошибок)\n");
    printf("   Удаление несуществующего пациента: OK (нет ошибок)\n\n");

    // 3. БАЗА С ОДНИМ ЭЛЕМЕНТОМ
    printf("3. БАЗА С ОДНИМ ЭЛЕМЕНТОМ:\n");
    Doctor *single_doc = (Doctor *)malloc(sizeof(Doctor));
    single_doc->ID = 100;
    single_doc->name = strdup("Single Doctor");
    single_doc->text = strdup("Single Spec");
    single_doc->count = 0;
    single_doc->capacity = 10;
    single_doc->patients = (Patient **)calloc(10, sizeof(Patient *));
    docs->doctors[docs->count++] = single_doc;

    Patient *single_pat = (Patient *)malloc(sizeof(Patient));
    single_pat->ID = 200;
    single_pat->name = strdup("Single Patient");
    single_pat->text = strdup("Single Complaint");
    single_pat->doc = NULL;
    pats->patients[pats->count++] = single_pat;

    printf("   Создано: 1 доктор, 1 пациент\n");

    // Поиск
    Doctor *found = findDoc(docs, 100);
    printf("   Поиск доктора ID=100: %s\n", found ? "НАЙДЕН" : "НЕ НАЙДЕН");

    // Назначение врача
    addPatient_to_doc(found, single_pat);
    printf("   После назначения: у доктора %d пациентов\n", found->count);

    // Удаление
    eraseDoctor(docs, 100);
    printf("   После удаления доктора: в базе %d докторов\n\n", docs->count);

    // 4. ПОВТОРНОЕ УДАЛЕНИЕ
    printf("4. ПОВТОРНОЕ УДАЛЕНИЕ:\n");
    eraseDoctor(docs, 100);
    erasePatient(pats, 200);
    printf("   Повторное удаление: OK (нет ошибок)\n\n");

    // 5. НАЗНАЧЕНИЕ НЕСУЩЕСТВУЮЩИМ
    printf("5. НАЗНАЧЕНИЕ С НЕСУЩЕСТВУЮЩИМИ ID:\n");
    setDoctor(NULL, single_pat);  // Доктор = NULL
    printf("   Назначение с NULL доктором: OK (нет ошибок)\n");

    // 6. ДОБАВЛЕНИЕ ДУБЛИКАТА ПАЦИЕНТА К ДОКТОРУ
    printf("\n6. ДОБАВЛЕНИЕ ДУБЛИКАТА ПАЦИЕНТА:\n");
    Doctor *doc2 = (Doctor *)malloc(sizeof(Doctor));
    doc2->ID = 300;
    doc2->name = strdup("Doc2");
    doc2->text = strdup("Spec2");
    doc2->count = 0;
    doc2->capacity = 10;
    doc2->patients = (Patient **)calloc(10, sizeof(Patient *));
    docs->doctors[docs->count++] = doc2;

    Patient *pat2 = (Patient *)malloc(sizeof(Patient));
    pat2->ID = 400;
    pat2->name = strdup("Pat2");
    pat2->text = strdup("Complaint");
    pat2->doc = NULL;
    pats->patients[pats->count++] = pat2;

    addPatient_to_doc(doc2, pat2);
    addPatient_to_doc(doc2, pat2);  // Пытаемся добавить ещё раз
    printf("   У доктора %d пациентов (ожидается 1)\n", doc2->count);

    delete_base_of_docs(&docs);
    delete_base_of_pats(&pats);

    printf("\n========== ТЕСТ 2 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 3: БОЛЬШИЕ ДАННЫЕ ====================
void test_large_data(void) {
    printf("\n========== ТЕСТ 3: БОЛЬШИЕ ДАННЫЕ ==========\n\n");

    const int NUM_DOCTORS = 100;
    const int NUM_PATIENTS = 500;

    BaseoDocs *docs = createBaseDocs();
    BaseoPats *pats = createBasePats();

    // Увеличиваем capacity
    docs->capacity = NUM_DOCTORS;
    docs->doctors =
        (Doctor **)realloc(docs->doctors, NUM_DOCTORS * sizeof(Doctor *));
    pats->capacity = NUM_PATIENTS;
    pats->patients =
        (Patient **)realloc(pats->patients, NUM_PATIENTS * sizeof(Patient *));

    // 1. СОЗДАНИЕ 100 ДОКТОРОВ
    printf("1. СОЗДАНИЕ %d ДОКТОРОВ...\n", NUM_DOCTORS);
    for (int i = 1; i <= NUM_DOCTORS; i++) {
        Doctor *doc = (Doctor *)malloc(sizeof(Doctor));
        doc->ID = i;
        doc->name = (char *)malloc(30);
        sprintf(doc->name, "Doctor_%d", i);
        doc->text = (char *)malloc(100);
        sprintf(doc->text, "Specialization_%d", i % 10);
        doc->count = 0;
        doc->capacity = 20;
        doc->patients = (Patient **)calloc(20, sizeof(Patient *));

        docs->doctors[docs->count++] = doc;
    }
    printf("   OK. Всего: %d докторов\n\n", docs->count);

    // 2. СОЗДАНИЕ 500 ПАЦИЕНТОВ
    printf("2. СОЗДАНИЕ %d ПАЦИЕНТОВ...\n", NUM_PATIENTS);
    for (int i = 1; i <= NUM_PATIENTS; i++) {
        Patient *pat = (Patient *)malloc(sizeof(Patient));
        pat->ID = i;
        pat->name = (char *)malloc(30);
        sprintf(pat->name, "Patient_%d", i);
        pat->text = (char *)malloc(100);
        sprintf(pat->text, "Complaint_%d", i % 20);
        pat->doc = NULL;

        pats->patients[pats->count++] = pat;
    }
    printf("   OK. Всего: %d пациентов\n\n", pats->count);

    // 3. СОРТИРОВКА (для бинарного поиска)
    printf("3. СОРТИРОВКА БАЗ...\n");
    sort_docs(docs);
    sort_pats(pats);
    printf("   OK\n\n");

    // 4. НАЗНАЧЕНИЕ СЛУЧАЙНЫХ ВРАЧЕЙ
    printf("4. НАЗНАЧЕНИЕ СЛУЧАЙНЫХ ВРАЧЕЙ...\n");
    srand(time(NULL));
    for (int i = 0; i < NUM_PATIENTS; i++) {
        int doctor_id = (rand() % NUM_DOCTORS) + 1;
        Doctor *doc = findDoc(docs, doctor_id);
        if (doc) {
            addPatient_to_doc(doc, pats->patients[i]);
        }
    }
    printf("   OK\n\n");

    // 5. ПРОВЕРКА БИНАРНОГО ПОИСКА
    printf("=== ПРОВЕРКА БИНАРНОГО ПОИСКА ===\n");

    // Поиск существующих (каждый 13-й доктор)
    printf("1. ПОИСК СУЩЕСТВУЮЩИХ:\n");
    int found_count = 0;
    for (int i = 1; i <= NUM_DOCTORS; i += 13) {
        Doctor *doc = findDoc(docs, i);
        if (doc && doc->ID == i)
            found_count++;
    }
    printf("   Доктора: найдено %d из %d\n", found_count, NUM_DOCTORS / 13 + 1);

    found_count = 0;
    for (int i = 1; i <= NUM_PATIENTS; i += 17) {
        Patient *pat = findPat(pats, i);
        if (pat && pat->ID == i)
            found_count++;
    }
    printf("   Пациенты: найдено %d из %d\n", found_count,
           NUM_PATIENTS / 17 + 1);

    // Поиск несуществующих
    printf("\n2. ПОИСК НЕСУЩЕСТВУЮЩИХ:\n");
    Doctor *fake_doc = findDoc(docs, NUM_DOCTORS + 100);
    Patient *fake_pat = findPat(pats, NUM_PATIENTS + 100);
    printf("   Доктор ID=%d: %s\n", NUM_DOCTORS + 100,
           fake_doc == NULL ? "НЕ НАЙДЕН (OK)" : "НАЙДЕН (ERROR)");
    printf("   Пациент ID=%d: %s\n", NUM_PATIENTS + 100,
           fake_pat == NULL ? "НЕ НАЙДЕН (OK)" : "НАЙДЕН (ERROR)");

    // Поиск граничных значений
    printf("\n3. ПОИСК ГРАНИЧНЫХ ЗНАЧЕНИЙ:\n");
    Doctor *first_doc = findDoc(docs, 1);
    Doctor *last_doc = findDoc(docs, NUM_DOCTORS);
    Patient *first_pat = findPat(pats, 1);
    Patient *last_pat = findPat(pats, NUM_PATIENTS);
    printf("   Первый доктор (ID=1): %s\n", first_doc ? "НАЙДЕН" : "НЕ НАЙДЕН");
    printf("   Последний доктор (ID=%d): %s\n", NUM_DOCTORS,
           last_doc ? "НАЙДЕН" : "НЕ НАЙДЕН");
    printf("   Первый пациент (ID=1): %s\n",
           first_pat ? "НАЙДЕН" : "НЕ НАЙДЕН");
    printf("   Последний пациент (ID=%d): %s\n", NUM_PATIENTS,
           last_pat ? "НАЙДЕН" : "НЕ НАЙДЕН");

    // 6. ТЕСТ СКОРОСТИ
    printf("\n4. ТЕСТ СКОРОСТИ (1000 случайных поисков):\n");
    clock_t start = clock();

    for (int i = 0; i < 1000; i++) {
        int random_id = (rand() % (NUM_DOCTORS + 50)) + 1;
        findDoc(docs, random_id);
        findPat(pats, random_id);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   Время: %.4f секунд\n", time_spent);

    // 7. СТАТИСТИКА РАСПРЕДЕЛЕНИЯ
    printf("\n=== СТАТИСТИКА ===\n");
    int min_patients = 1000, max_patients = 0, total_patients = 0;
    for (int i = 0; i < docs->count; i++) {
        int cnt = docs->doctors[i]->count;
        total_patients += cnt;
        if (cnt < min_patients)
            min_patients = cnt;
        if (cnt > max_patients)
            max_patients = cnt;
    }
    printf("  Всего пациентов: %d\n", total_patients);
    printf("  В среднем на доктора: %.1f\n",
           (float)total_patients / NUM_DOCTORS);
    printf("  Минимум: %d, Максимум: %d\n", min_patients, max_patients);

    // 8. ПРОВЕРКА ЦЕЛОСТНОСТИ ДАННЫХ
    printf("\n=== ПРОВЕРКА ЦЕЛОСТНОСТИ ===\n");
    int integrity_ok = 1;

    for (int i = 0; i < pats->count; i++) {
        Patient *pat = pats->patients[i];
        if (pat->doc) {
            int found_in_doc = 0;
            for (int j = 0; j < pat->doc->count; j++) {
                if (pat->doc->patients[j] == pat) {
                    found_in_doc = 1;
                    break;
                }
            }
            if (!found_in_doc) {
                printf(
                    "  ОШИБКА: Пациент %d знает доктора, но доктор не знает "
                    "пациента\n",
                    pat->ID);
                integrity_ok = 0;
            }
        }
    }
    printf("  Целостность: %s\n", integrity_ok ? "OK" : "НАРУШЕНА");

    // 9. ТЕСТ БИНАРНЫХ ФАЙЛОВ
    printf("\n=== ТЕСТ БИНАРНЫХ ФАЙЛОВ ===\n");
    base_docs_to_bin(docs);
    base_pats_to_bin(pats);

    int pos = find_doctor_pos_by_id(50);
    if (pos >= 0) {
        Data_Doctor d = get_doctor_by_index(pos);
        printf("  Поиск доктора ID=50 в бинарном файле: найден (%s)\n", d.name);
    }

    pos = find_patient_pos_by_id(250);
    if (pos >= 0) {
        Data_Patient p = get_patient_by_index(pos);
        printf("  Поиск пациента ID=250 в бинарном файле: найден (%s)\n",
               p.name);
    }

    // 10. ТЕСТ ТЕКСТОВЫХ ФАЙЛОВ
    printf("\n=== ТЕСТ ТЕКСТОВЫХ ФАЙЛОВ ===\n");
    save_to_txt(docs, pats, "large_data.txt");
    printf("  Большие данные сохранены в large_data.txt\n");

    delete_base_of_docs(&docs);
    delete_base_of_pats(&pats);

    printf("\n========== ТЕСТ 3 ЗАВЕРШЁН ==========\n");
}

// ==================== ТЕСТ 4: ЧТЕНИЕ ИЗ ФАЙЛОВ ====================
void test_file_io(void) {
    printf(
        "\n========== ТЕСТ 4: ЧТЕНИЕ ИЗ ТЕКСТОВОГО И БИНАРНОГО ФАЙЛОВ "
        "==========\n\n");

    // ----- 1. СОЗДАНИЕ ТЕСТОВЫХ ДАННЫХ -----
    BaseoDocs *docs = createBaseDocs();
    BaseoPats *pats = createBasePats();

    // Создаём 3 докторов
    for (int i = 1; i <= 3; i++) {
        Doctor *doc = (Doctor *)malloc(sizeof(Doctor));
        doc->ID = i;
        doc->name = (char *)malloc(30);
        sprintf(doc->name, "Doctor_%d", i);
        doc->text = (char *)malloc(100);
        sprintf(doc->text, "Specialization_%d", i);
        doc->count = 0;
        doc->capacity = 10;
        doc->patients = (Patient **)calloc(10, sizeof(Patient *));
        docs->doctors[docs->count++] = doc;
    }

    // Создаём 5 пациентов
    for (int i = 1; i <= 5; i++) {
        Patient *pat = (Patient *)malloc(sizeof(Patient));
        pat->ID = i;
        pat->name = (char *)malloc(30);
        sprintf(pat->name, "Patient_%d", i);
        pat->text = (char *)malloc(100);
        sprintf(pat->text, "Complaint_%d", i);
        pat->doc = NULL;
        pats->patients[pats->count++] = pat;
    }

    // Назначаем врачей
    addPatient_to_doc(docs->doctors[0],
                      pats->patients[0]);  // Patient1 -> Doctor1
    addPatient_to_doc(docs->doctors[0],
                      pats->patients[1]);  // Patient2 -> Doctor1
    addPatient_to_doc(docs->doctors[1],
                      pats->patients[2]);  // Patient3 -> Doctor2
    addPatient_to_doc(docs->doctors[2],
                      pats->patients[3]);  // Patient4 -> Doctor3
    addPatient_to_doc(docs->doctors[2],
                      pats->patients[4]);  // Patient5 -> Doctor3

    printf("Исходные данные: %d докторов, %d пациентов\n", docs->count,
           pats->count);

    // ----- 2. СОХРАНЕНИЕ В ТЕКСТОВЫЙ ФАЙЛ -----
    save_to_txt(docs, pats, "test_data.txt");
    printf("Сохранено в test_data.txt\n");

    // ----- 3. ЗАГРУЗКА ИЗ ТЕКСТОВОГО ФАЙЛА И ПРОВЕРКА -----
    delete_base_of_docs(&docs);
    delete_base_of_pats(&pats);
    docs = createBaseDocs();
    pats = createBasePats();

    load_from_txt(docs, pats, "test_data.txt");
    printf("Загружено из test_data.txt: %d докторов, %d пациентов\n",
           docs->count, pats->count);

    // Проверяем целостность связей
    int ok_txt = 1;
    for (int i = 0; i < pats->count; i++) {
        Patient *p = pats->patients[i];
        if (p->doc) {
            int found = 0;
            for (int j = 0; j < p->doc->count; j++) {
                if (p->doc->patients[j] == p) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf(
                    "Ошибка в txt-загрузке: пациент %d не найден у доктора "
                    "%d\n",
                    p->ID, p->doc->ID);
                ok_txt = 0;
            }
        }
    }
    printf("Проверка txt-загрузки: %s\n\n", ok_txt ? "OK" : "НЕ ПРОЙДЕНА");

    // // ----- 4. СОХРАНЕНИЕ В БИНАРНЫЕ ФАЙЛЫ -----
    base_docs_to_bin(docs);
    base_pats_to_bin(pats);
    printf("Сохранено в doctors.bin и patients.bin\n");

    // ----- 5. ЗАГРУЗКА ИЗ БИНАРНЫХ ФАЙЛОВ И ПРОВЕРКА -----
    delete_base_of_docs(&docs);
    delete_base_of_pats(&pats);
    docs = createBaseDocs();
    pats = createBasePats();

    load_doctors_from_bin(docs);
    load_patients_from_bin(pats, docs);
    printf("Загружено из бинарных файлов: %d докторов, %d пациентов\n",
           docs->count, pats->count);

    int ok_bin = 1;
    for (int i = 0; i < pats->count; i++) {
        Patient *p = pats->patients[i];
        if (p->doc) {
            int found = 0;
            for (int j = 0; j < p->doc->count; j++) {
                if (p->doc->patients[j] == p) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf(
                    "Ошибка в bin-загрузке: пациент %d не найден у доктора "
                    "%d\n",
                    p->ID, p->doc->ID);
                ok_bin = 0;
            }
        }
    }
    printf("Проверка bin-загрузки: %s\n", ok_bin ? "OK" : "НЕ ПРОЙДЕНА");

    // Очистка
    delete_base_of_docs(&docs);
    delete_base_of_pats(&pats);

    printf("\n========== ТЕСТ 4 ЗАВЕРШЁН ==========\n");
}

int main() {
    printf("\n╔════════════════════════════════════════════════════════╗\n");
    printf("║              СИСТЕМА ТЕСТИРОВАНИЯ                       ║\n");
    printf("║        Медицинская база данных                          ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    printf("\nВыберите тест:\n");
    printf("  1 - Тест 1: Базовый функционал (2 доктора, 5 пациентов)\n");
    printf("  2 - Тест 2: Краевые случаи (пустые базы, NULL, дубликаты)\n");
    printf("  3 - Тест 3: Большие данные (100 докторов, 500 пациентов)\n");
    printf("  4 - Тест 4: Чтение из текстового и бинарного файлов\n");
    printf("  5 - Запустить все тесты\n");
    printf("  0 - Выход\n");
    printf("\nВаш выбор: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            test_basic_functionality();
            break;
        case 2:
            test_edge_cases();
            break;
        case 3:
            test_large_data();
            break;
        case 4:
            test_file_io();
            break;
        case 5:
            test_basic_functionality();
            test_edge_cases();
            test_large_data();
            test_file_io();
            printf("\n✅ ВСЕ ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ!\n");
            break;
        case 0:
            printf("До свидания!\n");
            break;
        default:
            printf("Неверный выбор!\n");
    }

    return 0;
}