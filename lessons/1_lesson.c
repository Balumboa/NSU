#include <math.h>
#include <stdio.h>

/*
угол q(t)
мы знаем, что за 12 часов 720 минут делает полный оборот
значит скорость v_hours = 2pi/720
скорость минутной v_minets = 2pi/60

по сути тут количество делений, проходимых за минуту

угол r_hours = 1/12
угол r_minets = 1

*/

int main() {
    int nowh, nowm;
    scanf("%d %d", &nowh, &nowm);
    int timenow = nowh * 60 + nowm;
    int answer = 0;
    for (int t = 0; t < 12 * 60; t++) {
        int hours = t / 12;
        printf("%d %d");
        if (t % 60 == hours) {
            if (t - timenow >= 0) {
                answer = t - timenow;
                break;
            }
        }
    }
    printf("%d", answer);
}