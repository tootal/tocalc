#ifndef _TOMATH_H
#define _TOMATH_H

const int MAXLEN=100000;
const int WIDTH=4;
const int BASE=10000;
//每个数保存的数据长度

void toCalcMain();
//界面交互部分

char* toCalc(char *input);
//计算部分

bool checkInput(char *input);
//检查输入是否为算式

void showHelp();
//显示帮助

int setPrecision(char *input);
//设置保留小数位数

#endif