/*

Create by tootal at 2019.2.2
Compiler version: MinGW-W64 gcc 8.1.0
Compile command: 

64位程序：
g++ -fexec-charset=GBK -static -o tocalc tocalc.cpp tomath.cpp
32位程序：
g++ -fexec-charset=GBK -static -m32 -o tocalc tocalc.cpp tomath.cpp

*/

#include <cstdio>
#include <cstdlib>
#include "tomath.h"
int main(){
	//文件统一采用UTF-8格式编码
	//编译时中文采用GBK编码
	// printf("hello world!\n");
	// printf("你好你好！\n");getchar();
	toCalcMain();//运行高精度计算器主程序

	
	return 0;
}