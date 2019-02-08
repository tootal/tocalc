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
			printf("已设置结果保留%d位小数！\n",PRECISION=s2i(input+1));
		}else{
			char *pos=findOp(input);
			toNum *b=s2n(pos+1);//后操作数
			char op=*pos;//操作符
			*pos=0;
			toNum *a=s2n(input);//前操作数
			shift(a,b);//把a，b的小数点对齐
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
	printf("直接输入算式，例如\"99.899/-99666.99666\"，按回车键结束输入。");
	printf("请确保输入合法，程序未做异常处理。\n\n");
}

int s2i(char *s){
	int ans=0,len=strlen(s);
	for(int i=0;i<len;i++){
		ans=ans*10+s[i]-'0';
	}
	return ans;
}

char* findOp(char *s){
	if(*s=='+'||*s=='-')str=str+1;
	return str+strcspn(str,ACCEPTOPERATOR);
}

toNum* s2n(char *s){
	toNum *a=new toNum;
	if(s[0]=='-')a->sign=true;
	if(s[0]=='+'||s[0]=='-')s=s+1;
	//处理数前面的正负号
	char *pos=strchr(s,'.');
	//查找小数点的位置
	if(pos==NULL){//没有小数点
		toNode x=s2l(s);
		a=toNum(a->sign,a->exp,x.pre,x.next);
	}else{
		int len=strlen(pos+1);
		//计算exp
		toNode y=s2l(pos+1);
		*pos=0;
		toNode x=s2l(s);
		//转化为类似于x.y的结构
		x.next->next=y.pre;
		y.pre->pre=x.next;
		//合并两部分链表
		a=toNum(a->sign,len,x.pre,y.next);
	}
	return a;
}

toNode s2l(char *s){
	toNode *head=new toNode(s[0]-'0'),*pre=head;
	int len=strlen(s);
	for(int i=1;i<len;i++){
		toNode *curr=new toNode(s[i]-'0',pre);
		pre=pre->next=curr;
	}
	return toNode(0,head,pre);
}

void shift(toNum *x,toNum *y){
	toNum *z=(y->exp>x->exp)?y:x;
	//z表示阶码较大的数
	int t=(z->exp-x->exp)+(z->exp-y->exp);
	//t表示z需要移动的位数
	while(t--){
		toNode *tp=new toNode(0,z->tail);
		z->tail=z->tail->next=tp;
	}
}

toNum* abs(toNum *x){
	return toNum(false,x->exp,x->head,x->tail);
}

toNum* add(toNum *x,toNum *y){
	if(x->sign)return sub(y,abs(x));
	if(y->sign)return sub(x,abs(y));
	//处理负数情况
	//以下模拟手工加法计算两个正整数相加
	toNum *ans=new toNum(false,x->exp);
	toNode *nowx=x->tail,*nowy=y->tail;
	short buf=0;
	//保存进位
	while(true){
		short sum=buf;
		if(nowx)sum+=nowx->data;
		if(nowy)sum+=nowy->data;
		//加和
		toNode *tp=new toNode(sum%10,ans->tail);
		if(ans->head)ans->tail=ans->tail->next=tp;
		else ans->head=ans->tail=tp;
		//插入结果
		buf=sum/10;
		//计算进位
		if(nowx)nowx=nowx->pre;
		if(nowy)nowy=nowy->pre;
		//移动指针
		if(!nowx&&!nowy&&!buf)break;
	}
	return ans;
}