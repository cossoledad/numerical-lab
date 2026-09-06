# Numerical Lab

这个项目不把 C 语言拆成互相孤立的语法题，而是通过真实数学问题说明：

> 如何把无法方便手算的数学问题，转化为计算机可以执行的有限步骤。

---

## 1. 项目目标

1. **C 语言基础**
   - 变量与基本类型
   - 表达式与运算符
   - `if / switch`
   - `for / while`
   - 函数
   - 数组
   - 指针
   - 函数指针
   - `struct`
   - `enum`
   - 动态内存
   - 文件组织
   - 头文件
   - 多编译单元
   - `const / static`
   - 标准库
   - 错误处理

2. **大学数学入门**
   - 极限
   - 微分
   - 积分
   - 常微分方程
   - 线性代数
   - 最小二乘
   - 数值优化
   - 概率与 Monte Carlo
   - 统计
   - 数值误差

3. **计算思维**
   - 解析解与数值解
   - 迭代
   - 收敛
   - 误差
   - 稳定性
   - 模型与算法分离
   - 数据结构与算法接口

---

## 2. 编译

### Linux / macOS

```bash
cmake -S . -B build
cmake --build build
./build/numerical_lab
```

### Windows + Visual Studio

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\numerical_lab.exe
```

如果使用 MinGW：

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
build\numerical_lab.exe
```

---

## 3. 模块

### 非线性方程求根

文件：

- `include/root.h`
- `src/root.c`

算法：

- 二分法
- Newton 法

示例：

```text
x^3 + x - 1 = 0
```

核心数学思想：

- 连续函数
- 介值定理
- 导数
- 迭代
- 收敛

核心 C 知识：

- 函数
- 函数指针
- `struct`
- `enum`
- `for`
- `if`
- 返回状态

---

### 数值积分

文件：

- `include/integration.h`
- `src/integration.c`

计算：

```text
∫[0,1] exp(-x²) dx
```

该函数没有初等函数形式的原函数，因此非常适合展示：

> 定积分不等于“必须先求原函数”。

算法：

- 中点法
- 梯形法
- Simpson 法

---

### 数值微分

文件：

- `include/derivative.h`
- `src/derivative.c`

算法：

```text
前向差分
中心差分
```

用于观察：

```text
h 太大 -> 截断误差大
h 过小 -> 浮点舍入误差开始显著
```

---

### 常微分方程

文件：

- `include/ode.h`
- `src/ode.c`

示例：

```text
Newton 冷却定律
```

方程：

```text
dT/dt = -k(T-T_env)
```

算法：

- Euler
- RK4

这一模块体现：

> 计算机并不一定需要先得到解析解，才能研究动态系统。

---

### 线性方程组

文件：

- `include/matrix.h`
- `src/matrix.c`

实现：

- 动态矩阵
- `malloc/calloc/free`
- Gaussian elimination
- 部分主元选取
- 回代

用于学习：

```text
Ax = b
```

并理解二维数组/矩阵与连续内存之间的关系。

---

### 最小二乘拟合

文件：

- `include/regression.h`
- `src/regression.c`

模型：

```text
y ≈ ax + b
```

通过最小化：

```text
Σ(yi - axi - b)²
```

寻找最符合实验数据的直线。

---

### 一维函数最小化

文件：

- `include/optimize.h`
- `src/optimize.c`

算法：

```text
黄金分割搜索
```

用途：

> 当函数的导数难以使用或没有必要显式求出时，也可以进行数值优化。

---

### Monte Carlo

文件：

- `include/monte_carlo.h`
- `src/monte_carlo.c`

实验：

- 随机估计 π
- 随机估计积分

用于直观理解：

- 随机变量
- 概率
- 大数定律
- 抽样
- 统计误差

---

### 基础统计

文件：

- `include/statistics.h`
- `src/statistics.c`

计算：

- 最小值
- 最大值
- 均值
- 方差
- 标准差

---

### 数值误差

文件：

- `include/numeric_error.h`
- `src/numeric_error.c`

包含三个重要实验：

1. `0.1 + 0.2 != 0.3`
2. 消去误差
3. 浮点求和顺序

这一部分尤其重要，因为：

> 数学上等价的表达式，在计算机中不一定具有相同的数值稳定性。

---

## 4. 工程结构

```text
numerical-lab/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── common.h
│   ├── root.h
│   ├── integration.h
│   ├── derivative.h
│   ├── ode.h
│   ├── matrix.h
│   ├── regression.h
│   ├── optimize.h
│   ├── monte_carlo.h
│   ├── statistics.h
│   ├── numeric_error.h
│   └── utils.h
├── src/
│   ├── main.c
│   ├── root.c
│   ├── integration.c
│   ├── derivative.c
│   ├── ode.c
│   ├── matrix.c
│   ├── regression.c
│   ├── optimize.c
│   ├── monte_carlo.c
│   ├── statistics.c
│   ├── numeric_error.c
│   └── utils.c
├── data/
│   ├── motion.csv
│   └── temperature.csv
└── docs/
    ├── learning-guide.md
    └── exercises.md
```

---

## 5. 推荐阅读顺序

不要直接从 `main.c` 从头读到尾。

推荐：

```text
1. src/integration.c
2. src/root.c
3. src/derivative.c
4. src/statistics.c
5. src/ode.c
6. src/regression.c
7. src/matrix.c
8. src/optimize.c
9. src/monte_carlo.c
10. src/numeric_error.c
11. src/main.c
```

这样复杂度逐步提高。

---

## 6. 最重要的学习方法

每个模块都按四层思考：

```text
数学问题
    ↓
数值方法
    ↓
算法步骤
    ↓
C 代码
```

例如积分：

```text
数学问题：
∫ f(x) dx

↓ 数值化

将区间切成很多小块

↓ 算法

循环计算小块面积并累加

↓ C

for (...) {
    sum += ...;
}
```

这就是本项目真正想训练的能力。
