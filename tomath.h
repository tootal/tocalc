//此文件包含tomath库函数的声明
//于20190208重写

#ifndef _TOMATH_H
#define _TOMATH_H
//避免头文件重复包含

static const char *VERSION="2.0.2";
//版本号

static const char *SHOWINPUT="toCalc>>> ";
static const char *SHOWOUTPUT="toCalc<<< ";
//界面交互提示符

const int MAXINPUTLEN=100005;
//单次输入最大字符数

void toCalcMain();
//计算器主界面

void showInfo();
//显示初始信息

int s2i(char *s);
//字符串转换为整数(String to Integer)



#endif //_TOMATH_H

