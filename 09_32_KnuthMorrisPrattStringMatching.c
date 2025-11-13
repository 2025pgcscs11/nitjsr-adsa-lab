#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute_lps(const char *pat, int m, int *lps) {
    lps[0] = 0;
    int len = 0, i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++; lps[i] = len; i++;
        } else {
            if (len != 0) len = lps[len - 1];
            else { lps[i] = 0; i++; }
        }
    }
}

int *kmp_search(const char *text, const char *pat, int *count_out) {
    int n = strlen(text), m = strlen(pat);
    *count_out = 0;
    if (m == 0 || m > n) return NULL;
    int *lps = malloc(sizeof(int) * m);
    compute_lps(pat, m, lps);

    int *matches = malloc(sizeof(int) * (n - m + 1));
    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pat[j]) { i++; j++; }
        if (j == m) {
            matches[*count_out] = i - j;
            (*count_out)++;
            j = lps[j - 1];
        } else if (i < n && text[i] != pat[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    free(lps);
    return matches;
}

void print_matches(const char *name, int *matches, int c) {
    printf("%s found %d occurrence(s):\n", name, c);
    if (c == 0) { printf("  (none)\n"); return; }
    for (int i = 0; i < c; ++i) printf("  at index %d\n", matches[i]);
}

int main(void) {
    const char *text = "AABAACAADAABAABA";
    const char *pattern = "AABA";
    printf("Knuth-Morris-Pratt Test\nText: \"%s\"\nPattern: \"%s\"\n\n", text, pattern);
    int count = 0;
    int *matches = kmp_search(text, pattern, &count);
    print_matches("KMP", matches, count);
    free(matches);
    return 0;
}

// Knuth-Morris-Pratt Test
// Text: "AABAACAADAABAABA"
// Pattern: "AABA"

// KMP found 3 occurrence(s):
//   at index 0
//   at index 9
//   at index 12