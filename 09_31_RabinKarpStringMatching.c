#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *rabin_karp(const char *text, const char *pattern, int *count_out) {
    int n = strlen(text), m = strlen(pattern);
    *count_out = 0;
    if (m == 0 || m > n) return NULL;

    const unsigned long long base = 256ULL;
    const unsigned long long mod = 1000000007ULL;

    unsigned long long ph = 0, th = 0, power = 1;
    for (int i = 0; i < m; ++i) {
        ph = (ph * base + (unsigned char)pattern[i]) % mod;
        th = (th * base + (unsigned char)text[i]) % mod;
        if (i) power = (power * base) % mod;
    }

    int *matches = malloc(sizeof(int) * (n - m + 1));
    for (int i = 0; i <= n - m; ++i) {
        if (ph == th) {
            if (strncmp(text + i, pattern, m) == 0) {
                matches[*count_out] = i;
                (*count_out)++;
            }
        }
        if (i < n - m) {
            unsigned long long left = ((unsigned long long)(unsigned char)text[i] * power) % mod;
            if (th < left) th += mod;
            th = (th - left) % mod;
            th = (th * base + (unsigned char)text[i + m]) % mod;
        }
    }
    return matches;
}

void print_matches(const char *name, int *matches, int c) {
    printf("%s found %d occurrence(s) :\n", name, c);
    if (c == 0) { printf("  (none)\n"); return; }
    for (int i = 0; i < c; ++i) printf("    At index %d\n", matches[i]);
}

int main(void) {
    const char *text = "ABABDAABABCABABBACDABABCABAB";
    const char *pattern = "ABABCABAB";
    printf("Rabin-Karp Test\nText: \"%s\"\nPattern: \"%s\"\n\n", text, pattern);
    int count = 0;
    int *matches = rabin_karp(text, pattern, &count);
    print_matches("Rabin-Karp", matches, count);
    free(matches);
    return 0;
}

// Rabin-Karp Test
// Text: "ABABDAABABCABABBACDABABCABAB"
// Pattern: "ABABCABAB"

// Rabin-Karp found 2 occurrence(s) :
//     At index 6
//     At index 19