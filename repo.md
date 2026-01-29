# b599_pre

## Repo简介

RPN Calculator是一个C++实现的逆波兰表示法（Reverse Polish Notation）计算器。RPN是一种数学表达式的表示方法，其中运算符位于操作数之后，不需要括号来指定运算顺序。

**主要功能：**
- 解析和计算RPN表达式
- 支持基本四则运算（+、-、*、/）
- 支持负数和小数
- 完善的错误处理机制
- 自定义异常类型用于错误报告

**技术栈：**
- C++ (C++11或更高版本)
- STL容器（stack、string、sstream）
- 自定义异常类

**项目结构：**
- `RPN.h`: 头文件，包含函数声明和自定义异常类
- `RPN.cpp`: 实现文件，包含RPN计算逻辑
- `TestRPN.cpp`: 测试文件，包含全面的测试用例

**核心算法：**
- `calculateRPN()`: 主计算函数，使用栈数据结构实现RPN表达式求值
- `InvalidRPNString`: 自定义异常类，用于报告各种错误情况

**RPN工作原理：**
1. 从左到右扫描表达式
2. 遇到数字则压入栈
3. 遇到运算符则弹出栈顶两个元素，执行运算，将结果压回栈
4. 最后栈中应只剩一个元素，即为结果

## 题目Prompt

I need to make sure the code I have for an RPN(reverse polish notation) calculator is completely right.  I have provided you with the implementation of the calculator all I need help with is having comprehensive and robust testing.  Create as many test functions as necessary to be sure the implementation of the calculator is good.  If any of the test's fail be sure to tell me which ones fail.  The code should run in a way so that you can tell exactly which tests failed and which ones didn't.

## PR链接

https://github.com/ncepudlgc/b599_pre/pull/1
