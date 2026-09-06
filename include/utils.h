#ifndef NUMERICAL_LAB_UTILS_H
#define NUMERICAL_LAB_UTILS_H

/* 清空当前输入行，主要用于简单命令行交互。 */
void clear_input_line(void);

/* 读取整数，失败时返回 0，成功返回 1。 */
int read_int(const char *prompt, int *value);

/* 读取 double，失败时返回 0，成功返回 1。 */
int read_double(const char *prompt, double *value);

#endif
