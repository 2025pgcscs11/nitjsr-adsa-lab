#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct { double x, y; } Point;
Point pivot;

double cross(const Point *o, const Point *a, const Point *b) {
    return (a->x - o->x) * (b->y - o->y) - (a->y - o->y) * (b->x - o->x);
}
double dist2(const Point *a, const Point *b) {
    double dx = a->x - b->x, dy = a->y - b->y; return dx*dx + dy*dy;
}

int cmp_point(const void *pa, const void *pb) {
    const Point *a = pa, *b = pb;
    if (a->y < b->y) return -1;
    if (a->y > b->y) return 1;
    if (a->x < b->x) return -1;
    if (a->x > b->x) return 1;
    return 0;
}

int polar_cmp(const void *pa, const void *pb) {
    const Point *a = pa, *b = pb;
    double c = cross(&pivot, a, b);
    if (c > 0) return -1;
    if (c < 0) return 1;
    double da = dist2(&pivot, a), db = dist2(&pivot, b);
    if (da > db) return -1;
    if (da < db) return 1;
    return 0;
}

Point *graham_scan(Point *pts, int n, int *hcount_out) {
    *hcount_out = 0;
    if (n == 0) return NULL;
    if (n == 1) { Point *h = malloc(sizeof(Point)); *h = pts[0]; *hcount_out = 1; return h; }

    // pivot: lowest y (then lowest x)
    int minidx = 0;
    for (int i = 1; i < n; ++i)
        if (pts[i].y < pts[minidx].y || (pts[i].y == pts[minidx].y && pts[i].x < pts[minidx].x))
            minidx = i;
    Point tmp = pts[0]; pts[0] = pts[minidx]; pts[minidx] = tmp;
    pivot = pts[0];

    qsort(pts + 1, n - 1, sizeof(Point), polar_cmp);

    // remove collinear duplicates keeping farthest
    int m = 1;
    for (int i = 1; i < n; ++i) {
        while (i < n - 1 && fabs(cross(&pivot, &pts[i], &pts[i + 1])) < 1e-12) i++;
        pts[m++] = pts[i];
    }
    if (m < 3) { Point *h = malloc(sizeof(Point) * m); for (int i = 0; i < m; ++i) h[i] = pts[i]; *hcount_out = m; return h; }

    Point *stack = malloc(sizeof(Point) * m);
    int top = 0;
    stack[top++] = pts[0]; stack[top++] = pts[1]; stack[top++] = pts[2];
    for (int i = 3; i < m; ++i) {
        while (top >= 2 && cross(&stack[top-2], &stack[top-1], &pts[i]) <= 0) top--;
        stack[top++] = pts[i];
    }
    Point *hull = malloc(sizeof(Point) * top);
    for (int i = 0; i < top; ++i) hull[i] = stack[i];
    *hcount_out = top;
    free(stack);
    return hull;
}

int main(void) {
    Point pts[] = {
        {0,3},{1,1},{2,2},{4,4},{0,0},{1,2},{3,1},{3,3},{2,4},{4,0},{5,2},{5,5}
    };
    int n = sizeof(pts)/sizeof(pts[0]);
    printf("Graham Scan Test: %d input points\n", n);
    for (int i = 0; i < n; ++i) printf("  (%.2f, %.2f)\n", pts[i].x, pts[i].y);

    Point *copy = malloc(sizeof(Point) * n);
    memcpy(copy, pts, sizeof(Point) * n);
    int hull_count = 0;
    Point *hull = graham_scan(copy, n, &hull_count);
    free(copy);

    printf("\nConvex hull (%d points) in Counter-clock Wise order:\n", hull_count);
    for (int i = 0; i < hull_count; ++i) printf("  (%.2f, %.2f)\n", hull[i].x, hull[i].y);
    free(hull);
    return 0;
}

// Graham Scan Test: 12 input points
//   (0.00, 3.00)
//   (1.00, 1.00)
//   (2.00, 2.00)
//   (4.00, 4.00)
//   (0.00, 0.00)
//   (1.00, 2.00)
//   (3.00, 1.00)
//   (3.00, 3.00)
//   (2.00, 4.00)
//   (4.00, 0.00)
//   (5.00, 2.00)
//   (5.00, 5.00)

// Convex hull (4 points) in Counter-clock Wise order:
//   (0.00, 0.00)
//   (4.00, 0.00)
//   (5.00, 2.00)
//   (0.00, 3.00)