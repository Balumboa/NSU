#include <stdio.h>

int norm[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int vesok[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int is_vesok(int x) {
    if ((x % 4 == 0 & x % 100 != 0) || x % 400 == 0)
        return 1;
    return 0;
}

int count(int day, int month, int year) {
    for (int i)
}

int main() {
    int day1, month1, year1;
    int day2, month2, year2;
    scanf("%d %d %d", &day1, &month1, year1);
    scanf("%d %d %d", &day2, &month2, year2);
    int countdays1 = 0;
    int countdays2 = 0;
    countdays1 = count(day1, month1, year1);
    countdays2 = count(day2, month2, year2);
}