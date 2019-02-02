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
			printf("显示帮助：\n");
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

bool checkSym(char *str){
	if(strspn(str,ACCEPTCHAR)==strlen(str))return true;
	else return false;
}

bool checkInput(char *str){
	bool flag=true;
	flag=flag&&checkSym(str);
	char *pos=str;
	if(*pos=='+'||*pos=='-')pos=pos+1;
	pos=pos+strcspn(pos,ACCEPTOPERATOR);
	flag=flag&&checkIt(pos+1);
	char ch=*pos;*pos=0;
	flag=flag&&checkIt(str);
	*pos=ch;
	return flag;
}

void showInfo(){
	printf("toCalc %s\n",VERSION);
	printf("输入h查看帮助，q退出程序\n");
	printf("请输入算式，按回车键结束输入。\n\n");
}

void showHelp(){
	printf("toCalc支持两个高精度实数算术运算，支持加减乘除运算。\n");
	printf("直接输入算式即可，支持的符号包括数字0-9，+-*/\n");
	printf("输入\"h\"查看帮助，\"q\"退出程序，输入小数点加数字可设置保留小数位数\n");
	printf("例如：输入\".7\"设置为保留到小数点后7位。\n");
	printf("\n作者：tootal\n邮箱：tootal@yeah.net\n");
}

int setPrecision(char *str){
	int temp=str2int(str);
	if(temp==-1)return -1;
	else return PRECISION=temp;
}

int str2int(char *str){
	int len=strlen(str),ans=0;
	// printf("len=%d\n",len);
	if(len>8||!checkNum(str)){
		return -1;
	}
	for(int i=0;i<len;i++){
		ans=ans*10+str[i]-'0';
	}
	return ans;
}

bool isNum(char x){
	if(x>='0'&&x<='9')return true;
	return false;
}

bool checkNum(char *str){
	int len=strlen(str);
	bool flag=true;
	for(int i=0;i<len;i++){
		if(!isNum(str[i])){
			flag=false;
			break;
		}
	}
	return flag;
}

bool checkIt(char *str){
	if(*str=='+'||*str=='-')str=str+1;
	char *pos=strchr(str,'.');
	bool flag=true;
	if(pos==0){
		flag=checkNum(str);
	}else{
		flag=flag&&checkNum(pos+1);
		char ch=*pos;*pos=0;
		flag=flag&&checkNum(str);
		*pos=ch;
	}
	return flag;
}