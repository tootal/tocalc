#ifndef _TOMATH_H
#define _TOMATH_H

static const char *VERSION="1.2.4";
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

static const int WIDTH=2;
static const int BASE=100;
//每个位保存的数据长度

static int PRECISION=10;
//保留小数位数，默认为10

struct toNum{
	bool sign;
	int *a,len,exp;
};
/*
高精度实数采用转换成整数的方式存储
包含符号位，指数部分exp，以及整数部分
sign表示符号位，true为负数，false为正数
整数部分采用动态数组存储，a为数组首地址
len表示a数组长度。
*/

void toCalcMain();
//界面交互部分

bool checkSym(char *str);
//检查输入符号

char* findOperator(char *str);
//找到算式中间的运算符

bool checkInput(char *str);
//检查输入是否为算式

void showInfo();
//显示初始信息

void showHelp();
//显示帮助

int setPrecision(char *str);
//设置保留小数位数

int str2int(char *str);
//把区间[left,right)范围内的字符串转换成正整数
//忽略其他字符

char* int2str(int x,int y=WIDTH);
//把整数x转换为字符串，前面补零凑足y位

bool isNum(char x);
//判断字符是否为数字

bool checkNum(char *str);
//判断字符串是否全为数字

bool checkIt(char *str);
//判断字符串是否为实数

toNum* str2toNum(char *str);
//转换字符串为toNum类型
//不考虑前后可能有多余的零

toNum* add(toNum *x,toNum *y);
//加法

toNum* sub(toNum *x,toNum *y);
//减法

toNum* mul(toNum	*x,toNum *y);
//乘法

toNum* div(toNum *x,toNum *y);
//除法

char* toNum2str(toNum *x);
//toNum类型转换成字符串

#endif