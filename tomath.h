//此文件包含tomath库函数的声明
//于20190208重写

#ifndef _TOMATH_H
#define _TOMATH_H
//避免头文件重复包含

static const char *VERSION="2.0.4";
//版本号

static const char *SHOWINPUT="toCalc>>> ";
static const char *SHOWOUTPUT="toCalc<<< ";
//界面交互提示符

static const char *ACCEPTOPERATOR="+-*/";
//允许输入的运算符

const int MAXINPUTLEN=100005;
//单次输入最大字符数

int PRECISION=10;
//保留小数点后位数，默认为10

struct toNode{
	short data;//每个节点存储一位数（0~9）便于小数点的处理
	toNode *pre,*next;
	toNode(	short x=0,
			toNode *p=nullptr,
			toNode *n=nullptr)
	:data(x),pre(p),next(n){}
};
//链表节点结构体
//包含简单的构造函数

struct toNum{
	bool sign;//true表示负数，false表示正数
	int exp;//表示阶码，数值为小数点后数字个数的相反数
	toNode *head,*tail;//存储高精度数的链表首尾节点
	toNum(	bool s=false,
			int e=0,
			toNode *h=nullptr,
			toNode *t=nullptr)
	:sign(s),exp(e),head(h),tail(t){}
};
//高精度实数结构体
//包含简单的构造函数

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

