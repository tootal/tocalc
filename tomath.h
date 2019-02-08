//此文件包含tomath库函数的声明
//于20190208重写

#ifndef _TOMATH_H
#define _TOMATH_H
//避免头文件重复包含

static const char *VERSION="2.0.10";
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
//保留小数为截断而不是四舍五入

struct toNode{
	short data;//每个节点存储一位数（0~9）便于小数点的处理
	toNode *pre,*next;
	toNode(	short x=0,
			toNode *p=NULL,
			toNode *n=NULL)//不用nullptr便于和0转换
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
			toNode *h=NULL,
			toNode *t=NULL)
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

toNum* s2n(char *s);
//把高精度实数字符串转换为toNum结构体
//参数s为字符串指针，指向一个形如
//"-9999.987654"的字符串
//此字符串将被转换为一个
//toNum(true,-6,head,tail)的结构体
//其中head、tail描述的链表有10个节点，结构为：
// head						  tail
//	|						   |
//	V 						   V
//	9->9->9->9->9->8->7->6->5->4

toNode s2l(char *s);
//s2n函数的一部分
//把高精度正整数转换为链表
//返回值为结构体toNode(0,head,tail)
//head、tail分别表示该链表的首尾节点

void shift(toNum *x,toNum *y);
//把x，y的小数点对齐
//具体操作是在阶码较大的数后补0

toNum* neg(toNum *x);
//返回x的相反数
//不会修改x

toNum* add(toNum *x,toNum *y);
//高精度实数加法

toNum* sub(toNum *x,toNum *y);
//高精度实数减法

toNum* mul(toNum *x,toNum *y);
//高精度实数乘法

toNum* div(toNum *x,toNum *y);
//高精度实数除法
//假定y不为0

void push_front(toNum *x,short y=0);
//在链表头插入数据y，默认为0

void push_back(toNum *x,short y=0);
//在链表尾插入数据y，默认为0


#endif //_TOMATH_H

