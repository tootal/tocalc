#include <cstdio>
#include <cstring>
#include "tomath.h"

void toCalcMain(){
	printf("toCalc \n\n");
	printf("输入h查看帮助，q退出程序\n");
	printf("请输入算式，按回车键结束输入。\n");

	while(true){
		printf("toCalc>>> ");
		char *input=new char[MAXLEN];
		scanf(" %s",input);
		if(input[0]=='h'){
			showHelp();
		}else if(input[0]=='q'){
			printf("Bye\n");
			break;
		}else if(input[0]=='.'){
			int num=setPrecision(input);
			printf("已设置结果保留%d位小数！\n",num);
		}else if(checkInput(input)){
			printf("输入合法！\n");
		}else{
			printf("无效输入，请重新输入！\n");
		}
	}
}

char* toCalc(char *input){
	char *output;

	return output;
}

bool checkInput(char *input){
	return true;
}

void showHelp(){
	printf("toCalc支持高精度实数算术运算，支持加减乘除幂运算。\n");
	printf("直接输入算式即可，支持的符号包括数字0-9，+-*/^，()\n");
	printf("输入\"h\"查看帮助，\"q\"退出程序，输入小数点加数字可设置保留小数位数\n");
	printf("例如：输入\".7\"设置为保留到小数点后7位。\n");
}

int setPrecision(){
	
}