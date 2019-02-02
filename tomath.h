#ifndef _TOMATH_H
#define _TOMATH_H

static const char *VERSION="1.0.0";
//版本号

static const char *SHOWINPUT="toCalc>>> ";
static const char *SHOWOUTPUT="toCalc<<< ";
//界面交互提示符

static const char *ACCEPTNUMBER="0123456789";
static const char *ACCEPTOPERATOR="+-*/";
static const char *ACCEPTCHAR="0123456789+-*/. ";
//允许输入的字符

static const int MAXLEN=100000;
//输入输出最大长度

static const int WIDTH=4;
static const int BASE=10000;
//每个数保存的数据长度

static int PRECISION=10;
//保留小数位数，默认为10

void toCalcMain();
//界面交互部分

char* toCalc(char *input);
//计算部分

bool checkSym(char *str);
//检查输入符号

bool checkInput(char *str);
//检查输入是否为算式

void showInfo();
//显示初始信息

void showHelp();
//显示帮助

int setPrecision(char *str);
//设置保留小数位数,返回-1表示设置失败

int str2int(char *str);
//把区间[left,right)范围内的字符串转换成正整数
//返回-1表示转换失败,含有其他字符

bool isNum(char x);
//判断字符是否为数字

bool checkNum(char *str);
//判断字符串是否全为数字

bool checkIt(char *str);
//判断字符串是否为实数

#endif