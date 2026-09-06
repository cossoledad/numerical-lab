#ifndef NUMERICAL_LAB_MATRIX_H
#define NUMERICAL_LAB_MATRIX_H

/*
 * 一个最小但实用的动态矩阵结构。
 *
 * data 按行优先存储：
 *
 *     data[row * cols + col]
 *
 * 这样可以借助 malloc 动态创建任意大小的矩阵。
 */

typedef struct
{
    int rows;
    int cols;
    double *data;
} Matrix;

Matrix matrix_create(int rows, int cols);
void matrix_free(Matrix *matrix);

double matrix_get(const Matrix *matrix, int row, int col);
void matrix_set(Matrix *matrix, int row, int col, double value);
void matrix_print(const Matrix *matrix);

/*
 * 使用带部分主元选取的 Gaussian elimination 求解：
 *
 *     A x = b
 *
 * 为了教学方便，本函数会修改 A 和 b。
 *
 * 返回：
 *     1  成功
 *     0  矩阵奇异或输入非法
 */
int solve_linear_system(Matrix *A, double *b, double *x);

#endif
