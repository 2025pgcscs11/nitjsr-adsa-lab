#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preprocess_badchar(const unsigned char *pat, int m, int badchar[256]) {
    for (int i = 0; i < 256; ++i) badchar[i] = -1;
    for (int i = 0; i < m; ++i) badchar[pat[i]] = i;
}

void preprocess_suffixes(const unsigned char *pat, int m, int *suf) {
    suf[m-1] = m;
    int g = m-1, f = 0;
    for (int i = m-2; i >= 0; --i) {
        if (i > g && suf[i + m - 1 - f] < i - g) suf[i] = suf[i + m - 1 - f];
        else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && pat[g] == pat[g + m - 1 - f]) g--;
            suf[i] = f - g;
        }
    }
}

void preprocess_good_suffix(const unsigned char *pat, int m, int *shift) {
    int *suf = malloc(sizeof(int) * m);
    preprocess_suffixes(pat, m, suf);
    for (int i = 0; i < m; ++i) shift[i] = m;
    int j = 0;
    for (int i = m - 1; i >= 0; --i)
        if (suf[i] == i + 1)
            for (; j < m - 1 - i; ++j)
                if (shift[j] == m) shift[j] = m - 1 - i;
    for (int i = 0; i <= m - 2; ++i)
        shift[m - 1 - suf[i]] = m - 1 - i;
    free(suf);
}

int *boyer_moore_search(const char *text, const char *pattern, int *count_out) {
    int n = strlen(text), m = strlen(pattern);
    *count_out = 0;
    if (m == 0 || m > n) return NULL;

    unsigned char *pat = (unsigned char *)pattern;
    unsigned char *txt = (unsigned char *)text;
    int badchar[256]; preprocess_badchar(pat, m, badchar);
    int *shift = malloc(sizeof(int) * m); preprocess_good_suffix(pat, m, shift);

    int *matches = malloc(sizeof(int) * (n - m + 1));
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j]) j--;
        if (j < 0) {
            matches[*count_out] = s; (*count_out)++;
            s += shift[0];
        } else {
            int bc_index = badchar[txt[s + j]];
            int bc_shift = j - (bc_index >= 0 ? bc_index : -1);
            int gs_shift = shift[j];
            s += (bc_shift > gs_shift) ? bc_shift : gs_shift;
        }
    }
    free(shift);
    return matches;
}

void print_matches(const char *name, int *matches, int c) {
    printf("%s found %d occurrence(s):\n", name, c);
    if (c == 0) { printf("  (none)\n"); return; }
    for (int i = 0; i < c; ++i) printf("  at index %d\n", matches[i]);
}

int main(void) {
    const char *text = "HERE IS A SIMPLE EXAMPLE";
    const char *pattern = "EXAMPLE";
    printf("Boyer-Moore Test\nText: \"%s\"\nPattern: \"%s\"\n\n", text, pattern);
    int count = 0;
    int *matches = boyer_moore_search(text, pattern, &count);
    print_matches("Boyer-Moore", matches, count);
    free(matches);
    return 0;
}

// Boyer-Moore Test
// Text: "HERE IS A SIMPLE EXAMPLE"
// Pattern: "EXAMPLE"

// Boyer-Moore found 1 occurrence(s):
//   at index 17