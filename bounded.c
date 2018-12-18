#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    char *name;
    int harga;
    int profit;
    int jumlah;
} item_t;
 
item_t items[] = {
    {"ayam",                5000,    25000,     5},
    {"bebek",               7000,    40000,     5},
    {"kambing",             30000,   200000,    2},
    {"kelinci",             25000,   150000,    2},
};
 
int n = sizeof (items) / sizeof (item_t);
 
int *knapsack (int w) {
    int i, j, k, v, *mm, **m, *s;
    mm = calloc((n + 1) * (w + 1), sizeof (int));
    m = malloc((n + 1) * sizeof (int *));
    m[0] = mm;
    for (i = 1; i <= n; i++) {
        m[i] = &mm[i * (w + 1)];
        for (j = 0; j <= w; j++) {
            m[i][j] = m[i - 1][j];
            for (k = 1; k <= items[i - 1].jumlah; k++) {
                if (k * items[i - 1].harga > j) {
                    break;
                }
                v = m[i - 1][j - k * items[i - 1].harga] + k * items[i - 1].profit;
                if (v > m[i][j]) {
                    m[i][j] = v;
                }
            }
        }
    }
    s = calloc(n, sizeof (int));
    for (i = n, j = w; i > 0; i--) {
        int v = m[i][j];
        for (k = 0; v != m[i - 1][j] + k * items[i - 1].profit; k++) {
            s[i - 1]++;
            j -= items[i - 1].harga;
        }
    }
    free(mm);
    free(m);
    return s;
}
 
int main () {
    int i, tj = 0, th = 0, tp = 0, *s;
    s = knapsack(50000);
    for (i = 0; i < n; i++) {
        if (s[i]) {
            printf("%-22s %5d %5d %5d\n", items[i].name, s[i], s[i] * items[i].harga, s[i] * items[i].profit);
            tj += s[i];
            th += s[i] * items[i].harga;
            tp += s[i] * items[i].profit;
        }
    }
    printf("%-22s %5d %5d %5d\n", "jumlah, harga, profit:", tj, th, tp);
    return 0;
}
