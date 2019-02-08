//此文件包含tomath库函数的实现部分

#include <cstdio>
#include <cstring>
#include "tomath.h"

void toCalcMain(){
	showInfo();//显示初始信息
	while(true){
		printf("%s",SHOWINPUT);
		char *input=new char[MAXINPUTLEN];
		scanf(" %s",input);
		printf("%s",SHOWOUTPUT);
		//假定输入合法，不做异常处理
		if(input[0]=='q'){//退出程序
			printf("Bye!\n");
			break;
		}else if(input[0]=='.'){//设置保留小数位数
			printf("已设置结果保留%d位小数！\n",setPrecision(s2i(input+1)));
		}else{
			char *pos=findOp(input);
			toNum *b=s2n(pos+1);//后操作数
			char op=*pos;//操作符
			*pos=0;
			toNum *a=s2n(input);//前操作数
			toNum *c;
			if(op=='+'){
				c=add(b,a);
			}else if(op=='-'){
				c=sub(b,a);
			}else if(op=='*'){
				c=mul(b,a);
			}else if(op=='/'){//假定除数不为0，不处理为0情况
				c=div(b,a);
			}
			char *s=n2s(c);//c转换为字符串输出
			printf("%s\n",s);
			delete[] s;
		}
		delete[] input;
	}
}

void showInfo(){
	printf("toCalc %s\n",VERSION);
	printf("toCalc支持两个高精度实数四则运算，可保留到小数点后任意一位。\n");
	printf("输入q退出程序，输入小数点加数字可设置保留小数位数（默认10位）\n");
	printf("例如：输入\".7\"设置为保留到小数点后7位。\n");
	printf("直接输入算式，按回车键结束输入。");
	printf("请确保输入合法，程序未做异常处理。\n\n");
}