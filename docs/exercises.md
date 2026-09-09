# Numerical Lab 练习

下面练习不是简单改数字，而是用于继续扩展项目。

---

## Level 0：基础语法

### 练习 1

当前项目中存在一个big_number的模块，用于简单使用C字符串实现大数相加（因为我们知道int、long都是有范围的，超过了范围就会溢出）。

需要：1、理解现有实现；2、分析现有实现不足；3、不借助任何辅助工具的前提下重写现有实现；

对于要求3重写现有实现，需要设计新增一个模块文件，并且按照如下的函数签名进行实现：

```C
typedef struct {
    size_t size;
    char *buffer; // 低位在前的十进制数字字符
} aString;

aString aStringCreate(size_t size);
void aStringRelease(aString *b);
aString aStringFromCString(const char *c);
void aStringPrint(const aString *a);

/**
 * 十进制半加器 (Half Adder)
 * 输入: 加数 a, b (字符 '0'-'9')
 * 输出: *sum (本位和字符 '0'-'9')
 * 返回: 进位字符 ('0' 或 '1')
 */
char halfAdder(char a, char b, char *sum);

/**
 * 十进制全加器 (Full Adder)
 * 由两个半加器和一个或门级联组成：
 * 1. HA1(a, b) -> sum1, carry1
 * 2. HA2(sum1, cin) -> sum, carry2
 * 3. cout = carry1 OR carry2 (十进制两数相加+进位最多为 9+9+1=19，两者进位互斥)
 */
char fullAdder(char a, char b, char cin, char *sum);

/**
 * 基于全加器的大数加法
 */
aString aStringAdd(const aString *a, const aString *b);

// 需要能完成测试
bString num1 = bStringFromCString("99999999999999999999");
bString num2 = bStringFromCString("1");
bString res = bStringAdd(&num1, &num2);
bStringPrint(&res);
```

### 练习 2

分析bList的实现，独立完成一个aList（使用单向List，即只记录一个Node的nxt指针）。

---

## Level 1：基础 C

### 练习 1

修改积分模块，新增左矩形法：

```text
integrate_left_rectangle(...)
```

比较：

- 左矩形
- 中点
- 梯形
- Simpson

---

### 练习 2

让用户输入积分区间 `[a,b]` 和子区间数量 `n`。

要求处理：

- `n <= 0`
- `a == b`
- 输入非数字

---

### 练习 3

增加函数：

```text
f(x) = sin(x)
```

验证：

```text
∫[0,π] sin(x) dx = 2
```

---

## Level 2：算法思维

### 练习 4

实现割线法求根。

特点：

```text
不需要显式导数
```

比较：

- 二分法
- Newton
- 割线法

的迭代次数。

---

### 练习 5

给 Newton 法增加：

```text
最大步长限制
```

思考：

> 为什么 Newton 法有时会发散？

---

## Level 3：微积分

### 练习 6

研究：

```text
f(x)=sin(x)
```

在：

```text
x=1
```

处的数值导数。

让：

```text
h = 10^-1, 10^-2, ..., 10^-16
```

输出误差。

观察：

> 误差为什么先下降，然后又上升？

---

### 练习 7

给积分算法增加自适应 Simpson 方法。

目标：

```text
用户提供误差 tolerance
算法自动决定需要分多少段
```

---

## Level 4：ODE

### 练习 8

模拟自由落体：

```text
dv/dt = g
```

比较：

```text
数值结果
与
v = gt
```

---

### 练习 9

加入线性空气阻力：

```text
m dv/dt = mg - cv
```

分析终端速度。

---

### 练习 10

综合模型：

```text
降落伞运动
```

高度达到指定位置后改变阻力系数。

这会用到：

- `if`
- 状态变量
- ODE
- 参数切换

---

## Level 5：线性代数

### 练习 11

实现：

```text
matrix_add
matrix_multiply
matrix_transpose
```

---

### 练习 12

Gaussian elimination 中删除主元选取。

寻找一个例子，使算法：

```text
失败
或出现严重数值误差
```

然后重新启用部分主元。

理解：

> 数值算法中的“看起来多余的一步”可能是稳定性的关键。

---

## Level 6：数据与文件

### 练习 13

从：

```text
data/motion.csv
```

读取数据，并完成线性拟合。

不要再把数据写死在 `main.c`。

---

### 练习 14

把 ODE 结果保存为：

```text
cooling.csv
```

格式：

```text
time,temperature
0.0,90.0
...
```

然后使用 Excel、Python、gnuplot 等绘制曲线。

---

## Level 7：统计与概率

### 练习 15

重复运行 Monte Carlo π 估计 100 次。

统计：

- 平均值
- 最大值
- 最小值
- 标准差

观察样本数：

```text
100
1000
10000
100000
```

对波动的影响。

---

## Level 8：综合项目

实现：

# Projectile Lab

模拟带空气阻力的二维抛体运动。

状态：

```text
x
y
vx
vy
```

方程：

```text
dx/dt = vx
dy/dt = vy

dvx/dt = -k v vx
dvy/dt = -g - k v vy
```

其中：

```text
v = sqrt(vx² + vy²)
```

输入：

- 初速度
- 发射角度
- 阻力系数
- 时间步长

输出：

- 最大高度
- 飞行时间
- 水平距离
- CSV 轨迹

这个练习会把整个项目中的大部分知识真正连接起来。
