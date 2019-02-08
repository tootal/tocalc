//此文件包含tomath库函数的声明
//于20190208重写

#ifndef _TOMATH_H
#define _TOMATH_H
//避免头文件重复包含

static const char *VERSION="2.0.3";
//版本号

static const char *SHOWINPUT="toCalc>>> ";
static const char *SHOWOUTPUT="toCalc<<< ";
//界面交互提示符

static const char *ACCEPTOPERATOR="+-*/";
//允许输入的运算符

const int MAXINPUTLEN=100005;
//单次输入最大字符数

int PRECISION

void toCalcMain();
//计算器主界面

void showInfo();
//显示初始信息

int s2i(char *s);
//字符串转换为整数(String to Integer)

char* findOp(char *s);
//找到算式中间的运算符
//参数s为字符串指针，指向一个形如
//"-13.99/-98.35"的字符串
//返回值为字符'/'位置的指针

#endif //_TOMATH_H

