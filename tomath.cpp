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
			// printf("pos=%c\n",*pos);
			toNum *a=str2toNum(pos+1);
			// printf("a->len=%d\n",a->len);
			// printf("a->exp=%d\n",a->exp);
			// printf("a->a[0]=%d\n",a->a[0]);
			char op=*pos;*pos=0;
			toNum *b=str2toNum(input);
			// printf("b->len=%d\n",b->len);
			// printf("b->exp=%d\n",b->exp);
			// printf("b->a[0]=%d\n",b->a[0]);
			// printf("%s%c%s\n",toNum2str(b),op,toNum2str(a));
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
				char *s=toNum2str(c);
				printf("%s\n",s);
				delete[] s;
			}
		}else{
			flag=false;
		}

		if(!flag){
			printf("无效输入，请重新输入！\n");
		}
		delete[] input;
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
	printf("直接输入算式即可，支持的符号包括数字0-9，+-*/.\n");
	printf("输入\"h\"查看帮助，\"q\"退出程序，输入小数点加数字可设置保留小数位数(默认10位)\n");
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

char* int2str(int x,int y){
	char *s=new char[y];
	for(int i=y-1;i>=0;i--){
		s[i]=x%10+'0';
		x/=10;
	}
	s[y]=0;
	return s;
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
	// printf("sign=%d\n",a->sign);
	int len=strlen(str);
	char *tempstr=new char[len];
	int i,j=0,pos=len;
	for(i=0;i<len;i++){
		if(isNum(str[i]))tempstr[j++]=str[i];
		else pos=i;
	}
	len=j;j=0;
	tempstr[len]=0;
	// printf("pos=%d\n",pos);
	a->exp=pos-len;
	// printf("len=%d\n",len);
	// printf("exp=%d\n",a->exp);
	// printf("tempstr=%s\n",tempstr);
	a->a=new int[(len-1)/WIDTH+1];
	for(i=len-WIDTH;i>=0;i-=WIDTH){
		a->a[j++]=str2int(tempstr+i);
		// printf("a[%d]=%d\n",j-1,a->a[j-1]);
		tempstr[i]=0;
	}
	if(i!=-WIDTH)a->a[j++]=str2int(tempstr);
	a->len=j;
	// printf("len=%d\n",a->len);
	return a;
}

toNum* add(toNum *x,toNum *y){
	toNum *z;
	return z;
}

toNum* sub(toNum *x,toNum *y){
	toNum *z;
	return z;
}

toNum* mul(toNum *x,toNum *y){
	toNum *z;
	return z;
}

toNum* div(toNum *x,toNum *y){
	toNum *z;
	return z;
}

char* toNum2str(toNum *x){
	char *s=new char[x->len*WIDTH+4];
	int i=0,j=(x->len)-1,ppos;
	if(x->sign)s[i++]='-';
	bool left=false;
	if(WIDTH*j+1>-(x->exp)){
		sprintf(s+i,"%d",x->a[j]);
		while(isNum(s[i]))i++;
		j--;
		left=true;
	}
	while(WIDTH*j+1>-(x->exp)){
		char *ts=int2str(x->a[j]);
		sprintf(s+i,"%s",ts);
		delete[] ts;
		i+=WIDTH;
		j--;
		left=true;
	}
	// printf("i=%d,j=%d,s[i-1]=%c\n",i,j,s[i-1]);
	if(-(x->exp)>j*WIDTH&&-(x->exp)<(j+1)*WIDTH){
		char *ts=int2str(x->a[j]);
		int pos=WIDTH*(j+1)+(x->exp);
		// printf("pos=%d\n",pos);
		ppos=i+pos;
		// printf("ts+pos=%s\n",ts+pos);
		sprintf(s+i+pos,".%s",ts+pos);
		ts[pos]=0;
		char tempc=s[i+pos];
		sprintf(s+i,"%s",ts);
		s[i+pos]=tempc;
		// printf("s[0]=%c,s[1]=%c,s[2]=%c,s[3]=%c\n",s[0],s[1],s[2],s[3]);
		delete[] ts;
		i+=WIDTH+1;
		j--;
	}else{
		if(!left)s[i++]='0';
		ppos=i;
		s[i++]='.';
		int temp=-(x->exp)-(j+1)*WIDTH;
		while(temp--)s[i++]='0';
	}
	while(j>=0){
		char *ts=int2str(x->a[j]);
		// printf("j=%d,ts=%s\n",j,ts);
		sprintf(s+i,"%s",ts);
		delete[] ts;
		i+=WIDTH;
		j--;
	}
	while(i<ppos+PRECISION+2)s[i++]='0';
	if(PRECISION==0)s[ppos]=0;
	else s[ppos+PRECISION+1]=0;
	return s;
}

void shift(toNum *x,toNum *y){
	
}