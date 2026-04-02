#include <stdio.h>

void solve(int x) {
    int ans = 0;
    int now = 0;
    unsigned int t = 0;
    if (x < 0) {
        t = -x;
        t = ~t;
        t++;
    } else {
        t = x;
    }
    while (t > 0) {
        int a = t % 2;
        if (a == 1) {
            now++;
        } else {
            ans = (ans < now) ? now : ans;
            now = 0;
        }
        t /= 2;
    }
    ans = (ans < now) ? now : ans;
    printf("%d", ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    solve(n);
}