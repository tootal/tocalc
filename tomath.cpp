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
			int len=strlen(input+1);
			if(len>6||!checkNum(input+1))flag=false;
			else{
				int num=setPrecision(input+1);
				printf("已设置结果保留%d位小数！\n",num);
			}
		}else if(checkInput(input)){
			// printf("输入合法！\n");
			char *pos=findOperator(input);
			toNum *a=str2toNum(pos+1);
			char op=*pos;*pos=0;
			toNum *b=str2toNum(input);
			toNum *c;
			if(op=='+'){
				c=add(b,a);
			}else if(op=='-'){
				c=sub(b,a);
			}else if(op=='*'){
				c=mul(b,a);
			}else if(op=='/'){
				if(b->len==1&&b->a[0]==0)flag=false;
				else{
					c=div(b,a);
				}
			}
			if(flag){
				printf("%s\n",toNum2str(c));
			}
		}else{
			flag=false;
		}

		if(!flag){
			printf("无效输入，请重新输入！\n");
		}
	}
}

bool checkSym(char *str){
	if(strspn(str,ACCEPTCHAR)==strlen(str))return true;
	else return false;
}

char* findOperator(char *str){
	if(*str=='+'||*str=='-')str=str+1;
	return str+strcspn(str,ACCEPTOPERATOR);
}

bool checkInput(char *str){
	bool flag=true;
	flag=flag&&checkSym(str);

	char *pos=findOperator(str);
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
	return PRECISION=str2int(str);
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

toNum* str2toNum(char *str){
	toNum *a=new toNum;
	a->sign=false;
	if(str[0]=='-')a->sign=true;
	if(str[0]=='+'||str[0]=='-')str=str+1;
	int len=strlen(str);
	char *tempstr=new char[len];
	int i,j=0,pos=len;
	for(i=0;i<len;i++){
		if(isNum(str[i]))tempstr[j++]=str[i];
		else pos=i;
	}
	a->exp=pos-len;
	// printf("exp=%d\n",a->exp);
	len=j;j=0;
	a->a=new int[(len-1)/WIDTH+1];
	for(i=len-WIDTH;i>=0;i-=WIDTH){
		a->a[j++]=str2int(tempstr+i);
		tempstr[i]=0;
	}
	if(i!=-WIDTH)a->a[j++]=str2int(tempstr);
	a->len=j;
}

toNum* add(toNum *x,toNum *y){

}

toNum* sub(toNum *x,toNum *y){

}

toNum* mul(toNum *x,toNum *y){

}

toNum* div(toNum *x,toNum *y){

}

char* toNum2str(toNum *x){
	
}