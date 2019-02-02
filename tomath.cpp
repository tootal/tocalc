#include <cstdio>
#include <cstring>
#include "tomath.h"

void toCalcMain(){
	showInfo();
	while(true){
		printf("%s",SHOWINPUT);
		char *input=new char[MAXLEN];
		scanf(" %s",input);
		printf("%s",SHOWOUTPUT);
		bool flag=true;
		if(input[0]=='h'){
			showHelp();
		}else if(input[0]=='q'){
			printf("Bye\n");
			break;
		}else if(input[0]=='.'){
			int num=setPrecision(input+1);
			if(num==-1)flag=false;
			else{
				printf("已设置结果保留%d位小数！\n",num);
			}
		}else if(checkInput(input)){
			printf("输入合法！\n");
		}else{
			flag=false;
		}

		if(!flag){
			printf("无效输入，请重新输入！\n");
		}
	}
}

char* toCalc(char *input){
	char *output;

	return output;
}

bool isSym(char x){
	if(isNum(x)||\
		 x=='+'||\
		 x=='-'||\
		 x=='*'||\
		 x=='/'||\
		 x=='.'||\
		 x==' '\
	)return true;
	return false;
}

bool checkSym(char *input){
	int len=strlen(input);
	bool flag=true;
	for(int i=0;i<len;i++){
		if(!isSym(input[i])){
			flag=false;
			break;
		}
	}
	return flag;
}

bool checkInput(char *input){
	bool flag=true;
	flag=flag&&checkSym(input);
	return flag;
}

void showInfo(){
	printf("toCalc %s\n",VERSION);
	printf("输入h查看帮助，q退出程序\n");
	printf("请输入算式，按回车键结束输入。\n\n");
}

void showHelp(){
	printf("toCalc支持高精度实数算术运算，支持加减乘除运算。\n");
	printf("直接输入算式即可，支持的符号包括数字0-9，+-*/\n");
	printf("输入\"h\"查看帮助，\"q\"退出程序，输入小数点加数字可设置保留小数位数\n");
	printf("例如：输入\".7\"设置为保留到小数点后7位。\n");
	printf("\n作者：tootal\n邮箱：tootal@yeah.net\n");
}

int setPrecision(char *input){
	int temp=str2int(input);
	if(temp==-1)return -1;
	else return PRECISION=temp;
}

int str2int(char *left,char *right){
	int len,ans=0;
	if(right==nullptr)len=strlen(left);
	else len=right-left;
	// printf("len=%d\n",len);
	if(len>8||!checkNum(left,right))return -1;
	for(int i=0;i<len;i++){
		ans=ans*10+left[i]-'0';
	}
	return ans;
}

bool isNum(char x){
	if(x>='0'&&x<='9')return true;
	return false;
}

bool checkNum(char *left,char *right){
	int len;
	if(right==nullptr)len=strlen(left);
	else len=right-left;
	bool flag=true;
	for(int i=0;i<len;i++){
		if(!isNum(left[i])){
			flag=false;
			break;
		}
	}
	return flag;
}