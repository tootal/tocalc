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
			// shift(a,b);//把a，b的小数点对齐
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
	printf("toCalc %s by tootal\n",VERSION);
	printf("toCalc支持两个高精度实数四则运算，可保留到小数点后任意一位。\n");
	printf("输入q退出程序，输入小数点加数字可设置保留小数位数（默认10位）\n");
	printf("例如：输入\".7\"设置为保留到小数点后7位。\n");
	printf("直接输入算式，例如\"99.899/-99666.99666\"，按回车键结束输入。\n");
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
	if(*s=='+'||*s=='-')s=s+1;
	return s+strcspn(s,ACCEPTOPERATOR);
}

toNum* s2n(char *s){
	toNum *a=new toNum;
	if(s[0]=='-')a->sign=true;
	if(s[0]=='+'||s[0]=='-')s=s+1;
	//处理数前面的正负号
	char *pos=strchr(s,'.');
	//查找小数点的位置
	if(pos==NULL){//没有小数点
		int len=strlen(s);
		//计算len
		toNode x=s2l(s);
		a=new toNum(a->sign,0,len,x.pre,x.next);
	}else{
		int exp=strlen(pos+1);
		//计算exp
		int len=strlen(s)-1;
		//计算len
		toNode y=s2l(pos+1);
		*pos=0;
		toNode x=s2l(s);
		//转化为类似于x.y的结构
		x.next->next=y.pre;
		y.pre->pre=x.next;
		//合并两部分链表
		a=new toNum(a->sign,exp,len,x.pre,y.next);
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
	while(t--)push_back(z);
	//在z后补t个0
}

toNum* neg(toNum *x){
	return new toNum(!x->sign,x->exp,x->len,x->head,x->tail);
}

toNum* add(toNum *x,toNum *y){
	shift(x,y);
	if(x->sign)return sub(y,neg(x));
	if(y->sign)return sub(x,neg(y));
	//处理负数情况
	//以下模拟手算加法
	//计算两个正整数相加
	toNum *ans=new toNum(false,x->exp);
	toNode *nowx=x->tail,*nowy=y->tail;
	int buf=0;
	//保存进位
	while(true){
		int sum=buf;
		if(nowx)sum+=nowx->data;
		if(nowy)sum+=nowy->data;
		//计算加法
		push_front(ans,sum%10);
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

toNum* sub(toNum *x,toNum *y){
	shift(x,y);
	if(x->sign)return neg(add(neg(x),y));
	if(y->sign)return add(x,neg(y));
	if(cmp(x,y)<0)return neg(sub(y,x));
	//以下模拟手算减法
	//计算一个大正整数减一个小正整数
	toNum *ans=new toNum(false,x->exp);
	toNode *nowx=x->tail,*nowy=y->tail;
	int buf=0;
	//储存借位
	while(true){
		int res=buf+nowx->data;
		buf=0;
		if(nowy)res-=nowy->data;
		//计算减法
		if(res<0)buf--,res+=10;
		//计算借位
		push_front(ans,res);
		//插入结果
		nowx=nowx->pre;
		if(nowy)nowy=nowy->pre;
		//移动指针
		if(!nowx)break;
	}
	//未去除前端多余的0
	return ans;
}

toNum* mul(toNum *x,toNum *y){
	shift(x,y);
	if(x->sign)return neg(mul(neg(x),y));
	if(y->sign)return neg(mul(x,neg(y)));
	//以下模拟手算乘法
	//计算两个正整数相乘
	toNum *ans=new toNum(false,x->exp+y->exp);
	toNode *nowy=y->head;
	toNode *nowans=ans->head;//标记答案偏移
	while(true){
		int buf=0;
		toNode *nowx=x->head,*pos=nowans;
		while(true){
			int sum=buf;
			if(nowx&&nowy)sum+=(nowx->data)*(nowy->data);
			//计算乘法
			if(!pos)push_front(ans,sum%10);
			else{
				buf=(pos->data+sum)/10;
				pos->data=(pos->data+sum)%10;
			}
			//插入结果
			if(nowx)nowx=nowx->pre;
			pos=pos->pre;
			if(!nowx&&!buf)break;
		}
		nowy=nowy->pre;
		if(!nowans)nowans=ans->tail;
		nowans=nowans->pre;
		if(!nowy)break;
	}
	return ans;
}

toNum* div(toNum *x,toNum *y){
	shift(x,y);
	if(x->sign)return neg(div(neg(x),y));
	if(y->sign)return neg(div(x,neg(y)));
	for(int i=0;i<PRECISION;i++)push_back(x);
	//在x后加PRECISION个0
	//以下模拟手算除法
	//计算两个正整数相除(算出商和余数)
	//试商部分采用二分法
	toNum *q=new toNum(false,-PRECISION);
	toNum *r=new toNum(false,-PRECISION);
	//分别表示商quotient、余数remainder
	toNode *nowx=x->head;
	while(nowx){
		int lt=0,rt=9,m;
		while(lt<rt){
			m=(lt+rt+1)>>1;
			if(cmp(mul(y,i2n(m)),r)<=0)lt=m;
			else rt=m-1;
		}
		//二分试商，商为
		push_back(q,lt);
		r=sub(r,mul(y,i2n(lt)));
		nowx=nowx->next;
	}
	return q;
	//此处返回r即为浮点余数
}

void push_front(toNum *x,int y){
	x->len++;
	toNode *tp=new toNode(y,NULL,x->head);
	if(x->head)x->head=x->head->pre=tp;
	else x->head=x->tail=tp;
}

void push_back(toNum *x,int y){
	x->len++;
	toNode *tp=new toNode(y,x->tail);
	if(x->tail)x->tail=x->tail->next=tp;
	else x->tail=x->head=tp;
}

int pop_front(toNum *x){
	int t=x->head->data;
	if(x->head==x->tail)x->head=x->tail=NULL;
	else{
		x->head=x->head->next;
		x->head->pre=NULL;
	}
	return t;
}

toNum* i2n(int x){
	toNode *tp=new toNode(x);
	return new toNum(false,0,1,tp,tp);
}

int cmp(toNum *x,toNum *y){
	shift(x,y);
	if(x->sign&&!y->sign)return -1;
	if(!x->sign&&y->sign)return 1;
	if(x->len!=y->len)return 
		(x->sign^(x->len>y->len))?1:-1;
	//此时xy同号,利用位运算简化判断
	else{
		toNode *nowx=x->head,*nowy=y->head;
		while(nowx&&nowy){
			if(nowx->data!=nowy->data)return
				(x->sign^(nowx->data>nowy->data))?1:-1;
			nowx=nowx->next;
			nowy=nowy->next;
		}
		return 0;//x==y
	}
}

char* n2s(toNum *x){
	while(x->exp>0&&x->exp--)push_back(x);
	while(-x->exp<PRECISION&&x->exp--)push_back(x);
	while(-x->exp>=x->len)push_front(x);
	while(x->len+1>-x->exp&&!x->head->data)pop_front(x);
	//处理首尾0
	char *s=new char[x->len+4];
	int i=0,j=x->len+x->exp;
	toNode *n=x->head;
	//i指向s当前处理位置
	//j表示小数点前的数字个数
	//n指向链表当前处理位置
	if(x->sign)s[i++]='-';
	while(j--){
		s[i++]=n->data+'0';
		n=n->next;
	}
	if(x->exp<0)s[i++]='.';
	while(n){
		s[i++]=n->data+'0';
		n=n->next;
	}
	return s;
}