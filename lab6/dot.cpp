#include "dot.h"

int dot(const char *filename, int **matrix, int n)
{
    char filename_p[100];
    snprintf(filename_p, 100, "%s.gv", filename);
    FILE *f = fopen(filename_p, "w");
    fprintf(f, "%s\n", "graph test_tree {");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != 0 && j > i)
                fprintf(f, "%d--%d[label=%d]\n", i + 1, j + 1, matrix[i][j]);
    }
    fprintf(f, "}\n");
    fclose(f);

    char str[1000];
    snprintf(str, 1000, "dot -Tpng %s.gv -o %s.png\n", filename, filename);

    system(str);

    return 0;
}
