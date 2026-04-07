#include "Base.h"

#include <stdio.h>
#include <stdlib.h>

#include "Doctor.h"
#include "Patient.h"

typedef struct BaseoDocs BaseoDocs;

typedef struct BaseoPats BaseoPats;

void get_info_docs(BaseoDocs *base) {
    if (base != NULL) {
        if (base->count > 0)
            printf("\n");
        printf("Количество доктров: ");
        printf("%d\n", base->count);
        for (int i = 0; i < base->count; i++) {
            print_info_doc(base->doctors[i]);
            printf("\n");
        }
        if (base->count > 0)
            printf("\n");
    } else {
        printf("БАЗА ДОКТОРОВ УДАЛЕНА");
    }
}

void get_info_pats(BaseoPats *base) {
    if (base != NULL) {
        if (base->count > 0)
            printf("\n");
        printf("Количество пациентов: ");
        printf("%d\n", base->count);
        for (int i = 0; i < base->count; i++) {
            print_info_pat(base->patients[i]);
            printf("\n");
        }
        if (base->count > 0)
            printf("\n");
    } else {
        printf("БАЗА ПАЦИЕНТОВ УДАЛЕНА");
    }
}

BaseoDocs *createBaseDocs() {
    BaseoDocs *base = (BaseoDocs *)malloc(sizeof(BaseoDocs));
    base->doctors = (Doctor **)calloc(10, sizeof(Doctor *));
    base->capacity = 10;
    base->count = 0;
    return base;
}

BaseoPats *createBasePats() {
    BaseoPats *base = (BaseoPats *)malloc(sizeof(BaseoPats));
    base->patients = (Patient **)calloc(10, sizeof(Patient *));
    base->capacity = 10;
    base->count = 0;
    return base;
}

void delete_base_of_docs(BaseoDocs **base) {
    if (*base != NULL) {
        printf("УДАЛЕНИЕ БАЗЫ ДОКТОРОВ");
        for (int i = 0; i < (*base)->count; i++) {
            delete_doc(&(*base)->doctors[i]);
        }
        free(*base);
        *base = NULL;
    }
}

void delete_base_of_pats(BaseoPats **base) {
    if (*base != NULL) {
        printf("УДАЛЕНИЕ БАЗЫ ПАЦИЕНТОВ");
        for (int i = 0; i < (*base)->count; i++) {
            delete_pat(&(*base)->patients[i]);
        }
        free(*base);
        *base = NULL;
    }
}

void sort_docs(BaseoDocs *base) {
    int now = base->count - 1;
    while (now > 0) {
        Doctor *a = base->doctors[now];
        Doctor *b = base->doctors[now - 1];
        if (b->ID > a->ID) {
            base->doctors[now] = b;
            base->doctors[now - 1] = a;
        }
        now--;
    }
}

void sort_pats(BaseoPats *base) {
    int now = base->count - 1;
    while (now > 0) {
        Patient *a = base->patients[now];
        Patient *b = base->patients[now - 1];
        if (b->ID > a->ID) {
            base->patients[now] = b;
            base->patients[now - 1] = a;
        }
        now--;
    }
}

void addDoctor(BaseoDocs *base) {
    Doctor *a = create_doc();
    if (base->capacity == base->count) {
        base->capacity *= 2;
        base->doctors = (Doctor **)realloc(base->doctors,
                                           sizeof(Doctor *) * base->capacity);
    }
    base->doctors[base->count] = a;
    base->count++;
    sort_docs(base);
}

void addPatient(BaseoPats *base) {
    Patient *a = create_pat();
    if (base->capacity == base->count) {
        base->capacity *= 2;
        base->patients = (Patient **)realloc(
            base->patients, sizeof(Patient *) * base->capacity);
    }
    base->patients[base->count] = a;
    base->count++;
    sort_pats(base);
}

Doctor *findDoc(BaseoDocs *base, int ID) {
    if (base->count == 0)
        return NULL;
    int l = 0, r = base->count;
    while (r - l > 1) {
        int k = (r + l) / 2;
        if (base->doctors[k]->ID <= ID) {
            l = k;
        } else {
            r = k;
        }
    }
    Doctor *x = base->doctors[l];
    if (x->ID != ID) {
        x = NULL;
    }
    return x;
}

Patient *findPat(BaseoPats *base, int ID) {
    if (base->count == 0)
        return NULL;
    int l = 0, r = base->count;
    while (r - l > 1) {
        int k = (r + l) / 2;
        if (base->patients[k]->ID <= ID) {
            l = k;
        } else {
            r = k;
        }
    }
    Patient *x = base->patients[l];
    if (x->ID != ID) {
        x = NULL;
    }
    return x;
}

void eraseDoctor(BaseoDocs *base, int ID) {
    Doctor *a = findDoc(base, ID);
    int l = 0, r = base->count;
    if (a != NULL) {
        while (r - l > 1) {
            int k = (r + l) / 2;
            if (base->doctors[k]->ID <= ID) {
                l = k;
            } else {
                r = k;
            }
        }
        while (l < base->count - 1) {
            Doctor *a = base->doctors[l];
            Doctor *b = base->doctors[l + 1];
            if (b->ID > a->ID) {
                base->doctors[l] = b;
                base->doctors[l + 1] = a;
            }
            l++;
        }
        delete_doc(&base->doctors[base->count - 1]);
        base->count--;
    }
}

void erasePatient(BaseoPats *base, int ID) {
    Patient *a = findPat(base, ID);
    if (a != NULL) {
        erasePatient_from_doc(a->doc, a);
        int l = 0, r = base->count;
        while (r - l > 1) {
            int k = (r + l) / 2;
            if (base->patients[k]->ID <= ID) {
                l = k;
            } else {
                r = k;
            }
        }
        while (l < base->count - 1) {
            Patient *a = base->patients[l];
            Patient *b = base->patients[l + 1];
            if (b->ID > a->ID) {
                base->patients[l] = b;
                base->patients[l + 1] = a;
            }
            l++;
        }
        delete_pat(&base->patients[base->count - 1]);
        base->count--;
    }
}