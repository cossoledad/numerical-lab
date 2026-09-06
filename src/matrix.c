#include "matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Matrix matrix_create(int rows, int cols)
{
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = 0;

    if (rows <= 0 || cols <= 0)
    {
        matrix.rows = 0;
        matrix.cols = 0;
        return matrix;
    }

    /*
     * calloc 会把分配出来的内存初始化为 0。
     */
    matrix.data = (double *)calloc(
        (size_t)rows * (size_t)cols,
        sizeof(double)
    );

    if (matrix.data == 0)
    {
        matrix.rows = 0;
        matrix.cols = 0;
    }

    return matrix;
}

void matrix_free(Matrix *matrix)
{
    if (matrix == 0)
    {
        return;
    }

    free(matrix->data);

    matrix->data = 0;
    matrix->rows = 0;
    matrix->cols = 0;
}

double matrix_get(const Matrix *matrix, int row, int col)
{
    return matrix->data[row * matrix->cols + col];
}

void matrix_set(Matrix *matrix, int row, int col, double value)
{
    matrix->data[row * matrix->cols + col] = value;
}

void matrix_print(const Matrix *matrix)
{
    for (int r = 0; r < matrix->rows; ++r)
    {
        for (int c = 0; c < matrix->cols; ++c)
        {
            printf("%12.6f ", matrix_get(matrix, r, c));
        }
        printf("\n");
    }
}

static void swap_rows(Matrix *A, double *b, int row1, int row2)
{
    if (row1 == row2)
    {
        return;
    }

    for (int col = 0; col < A->cols; ++col)
    {
        double tmp = matrix_get(A, row1, col);
        matrix_set(A, row1, col, matrix_get(A, row2, col));
        matrix_set(A, row2, col, tmp);
    }

    double tmp_b = b[row1];
    b[row1] = b[row2];
    b[row2] = tmp_b;
}

int solve_linear_system(Matrix *A, double *b, double *x)
{
    if (A == 0 || b == 0 || x == 0 ||
        A->data == 0 || A->rows <= 0 || A->rows != A->cols)
    {
        return 0;
    }

    int n = A->rows;

    /*
     * 前向消元。
     */
    for (int k = 0; k < n; ++k)
    {
        /*
         * 部分主元选取：
         * 在当前列中寻找绝对值最大的元素作为主元。
         */
        int pivot_row = k;
        double pivot_value = fabs(matrix_get(A, k, k));

        for (int r = k + 1; r < n; ++r)
        {
            double candidate = fabs(matrix_get(A, r, k));

            if (candidate > pivot_value)
            {
                pivot_value = candidate;
                pivot_row = r;
            }
        }

        if (pivot_value < 1.0e-14)
        {
            return 0;
        }

        swap_rows(A, b, k, pivot_row);

        for (int i = k + 1; i < n; ++i)
        {
            double factor =
                matrix_get(A, i, k) / matrix_get(A, k, k);

            matrix_set(A, i, k, 0.0);

            for (int j = k + 1; j < n; ++j)
            {
                double value =
                    matrix_get(A, i, j)
                    - factor * matrix_get(A, k, j);

                matrix_set(A, i, j, value);
            }

            b[i] -= factor * b[k];
        }
    }

    /*
     * 回代。
     */
    for (int i = n - 1; i >= 0; --i)
    {
        double sum = b[i];

        for (int j = i + 1; j < n; ++j)
        {
            sum -= matrix_get(A, i, j) * x[j];
        }

        double diagonal = matrix_get(A, i, i);

        if (fabs(diagonal) < 1.0e-14)
        {
            return 0;
        }

        x[i] = sum / diagonal;
    }

    return 1;
}
