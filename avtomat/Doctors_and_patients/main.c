#include <stdio.h>
#include <stdlib.h>

#include "Base.h"
#include "Doctor.h"
#include "Patient.h"
#include "to_bin.h"

void interface() {
    printf("=========Операции=========\n");
    printf("Чтобы показать информацию о докторах введите 1\n");
    printf("Чтобы добавить доктора введите 2\n");
    printf("Чтобы показать информацию о нужном докторе введите 3\n");
    printf("Чтобы показать информацию о пациентах введите 4\n");
    printf("Чтобы добавить пациента введите 5\n");
    printf("Чтобы показать информацию о нужном пациенте введите 6\n");
    printf("Чтобы назначить врача пациенту введите 7\n");
    printf("Чтобы удалить доктора введите 8\n");
    printf("Чтобы удалить пациента введите 9\n");
    printf("Чтобы удалить базу докторов введите 10\n");
    printf("Чтобы удалить базу пациентов введите 11\n");
    printf("Чтобы записать базу докторов в бинарный файл введите 12\n");
    printf("Чтобы найти доктора в бинарном файле введите 14\n");
    printf("Чтобы найти пациента в бинарном файле введите 15\n");
}

int main() {
    BaseoDocs *base_docs = createBaseDocs();
    get_info_docs(base_docs);
    BaseoPats *base_pats = createBasePats();
    get_info_pats(base_pats);
    while (1 == 1) {
        interface();
        int x;
        printf("Введите операцию: ");
        scanf("%d", &x);
        if (x == 1) {
            get_info_docs(base_docs);
        } else if (x == 2) {
            addDoctor(base_docs);
        } else if (x == 3) {
            int ID;
            printf("Введите ID нужного доктора: ");
            scanf("%d", &ID);
            Doctor *a = findDoc(base_docs, ID);
            if (a == NULL)
                printf("Такого доктора нет в базе данных.\n");
            else {
                print_info_doc(a);
            }
        } else if (x == 4) {
            get_info_pats(base_pats);
        } else if (x == 5) {
            addPatient(base_pats);
        } else if (x == 6) {
            int ID;
            printf("Введите ID нужного пациента: ");
            scanf("%d", &ID);
            Patient *a = findPat(base_pats, ID);
            if (a == NULL)
                printf("Такого пациента нет в базе данных.\n");
            else {
                print_info_pat(a);
            }
        } else if (x == 7) {
            int ID;
            printf("Введите ID пациента, которому вы хотите назначить врача: ");
            scanf("%d", &ID);
            Patient *pat = findPat(base_pats, ID);
            if (pat == NULL) {
                printf("Такого пациента не существует\n");
                continue;
            }
            printf("Введите ID нужного врача: ");
            scanf("%d", &ID);
            Doctor *doc = findDoc(base_docs, ID);
            if (doc == NULL) {
                printf("Такого врача не существует\n");
                continue;
            }
            setDoctor(doc, pat);
        } else if (x == 8) {
            int ID;
            printf("Введите ID доктора, которого нужно удлаить: ");
            scanf("%d", &ID);
            eraseDoctor(base_docs, ID);
        } else if (x == 9) {
            int ID;
            printf("Введите ID пациента, которого нужно удлаить: ");
            scanf("%d", &ID);
            erasePatient(base_pats, ID);
        } else if (x == 10) {
            delete_base_of_docs(&base_docs);
            if (base_docs == NULL)
                printf("База докторов успешно удалена");
        } else if (x == 11) {
            delete_base_of_pats(&base_pats);
            if (base_pats == NULL)
                printf("База пациентов успешно удалена");
        } else if (x == 12) {
            base_docs_to_bin(base_docs);
        } else if (x == 13) {
            base_pats_to_bin(base_pats);
        } else if (x == 14) {
            int ID;
            printf("ID доктора, которого нужно найти: ");
            scanf("%d", &ID);
            int index = find_doctor_pos_by_id(ID);
            Data_Doctor doc = get_doctor_by_index(index);
            printf("%s\n", doc.name);
        } else if (x == 15) {
            int ID;
            printf("ID пациента, которого нужно найти: ");
            scanf("%d", &ID);
            int index = find_doctor_pos_by_id(ID);
            Data_Patient pat = get_patient_by_index(index);
            printf("%s\n", pat.name);
        }
    }
}