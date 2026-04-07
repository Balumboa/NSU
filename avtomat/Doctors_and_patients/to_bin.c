#include "to_bin.h"

#include <stdio.h>
#include <stdlib.h>

#include "Base.h"
#include "Doctor.h"
#include "Patient.h"

void save_patient_to_file(Patient *pat, int index) {
    Data_Patient dest;
    memset(&dest, 0, sizeof(Data_Patient));

    dest.ID = pat->ID;
    dest.ID_doctor = pat->doc->ID;

    if (pat->name)
        strncpy(dest.name, pat->name, 29);
    if (pat->text)
        strncpy(dest.text, pat->text, 99);

    FILE *f = fopen("patients.bin", "rb+");
    if (!f)
        f = fopen("patients.bin", "wb");

    fseek(f, index * sizeof(Data_Patient), SEEK_SET);
    fwrite(&dest, sizeof(Data_Patient), 1, f);
    fclose(f);
}

Data_Patient get_patient_by_index(int index) {
    Data_Patient result = {0};
    FILE *f = fopen("patients.bin", "rb");
    if (!f)
        return result;

    fseek(f, index * sizeof(Data_Patient), SEEK_SET);
    fread(&result, sizeof(Data_Patient), 1, f);

    fclose(f);
    return result;
}

int find_patient_pos_by_id(int targetID) {
    FILE *f = fopen("patients.bin", "rb");
    if (!f)
        return -1;

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    int total_records = file_size / sizeof(Data_Patient);

    int l = 0;
    int r = total_records - 1;
    int result_idx = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        Data_Patient temp;

        fseek(f, mid * sizeof(Data_Patient), SEEK_SET);
        if (fread(&temp, sizeof(Data_Patient), 1, f) != 1)
            break;

        if (temp.ID == targetID) {
            result_idx = mid;
            break;
        }

        if (temp.ID < targetID) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    fclose(f);
    return result_idx;
}

void save_doctor_to_file(Doctor *src, int index) {
    Data_Doctor dest;
    memset(&dest, 0, sizeof(Data_Doctor));

    dest.ID = src->ID;
    dest.count = src->count;

    if (src->name)
        strncpy(dest.name, src->name, 29);
    if (src->text)
        strncpy(dest.text, src->text, 99);

    int limit = (src->count < 20) ? src->count : 20;
    for (int i = 0; i < limit; i++) {
        dest.ID_patients[i] = src->patients[i]->ID;
    }

    FILE *f = fopen("doctors.bin", "rb+");
    if (!f)
        f = fopen("doctors.bin", "wb");

    fseek(f, index * sizeof(Data_Doctor), SEEK_SET);
    fwrite(&dest, sizeof(Data_Doctor), 1, f);
    fclose(f);
}

Data_Doctor get_doctor_by_index(int index) {
    Data_Doctor result = {0};
    FILE *f = fopen("doctors.bin", "rb");
    if (!f)
        return result;

    fseek(f, index * sizeof(Data_Doctor), SEEK_SET);
    fread(&result, sizeof(Data_Doctor), 1, f);

    fclose(f);
    return result;
}

int find_doctor_pos_by_id(int targetID) {
    FILE *f = fopen("doctors.bin", "rb");
    if (!f)
        return -1;

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    int total_records = file_size / sizeof(Data_Doctor);

    int l = 0;
    int r = total_records - 1;
    int result_idx = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        Data_Doctor temp;

        fseek(f, mid * sizeof(Data_Doctor), SEEK_SET);
        if (fread(&temp, sizeof(Data_Doctor), 1, f) != 1)
            break;

        if (temp.ID == targetID) {
            result_idx = mid;
            break;
        }

        if (temp.ID < targetID) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    fclose(f);
    return result_idx;
}

void base_docs_to_bin(BaseoDocs *base) {
    for (int i = 0; i < base->count; i++) {
        save_doctor_to_file(base->doctors[i], i);
    }
}

void base_pats_to_bin(BaseoPats *base) {
    for (int i = 0; i < base->count; i++) {
        save_patient_to_file(base->patients[i], i);
    }
}