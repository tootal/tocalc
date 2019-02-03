/*

Create by tootal at 2019.2.2
Compiler version: MinGW-W64 gcc 8.1.0
Compile command: 

g++ -static -o tocalc tocalc.cpp tomath.cpp & tocalc

*/

#include <cstdio>
#include <cstdlib>
#include "tomath.h"
int main(){
	//文件统一采用UTF-8格式编码
	//Windows 系统下调节命令行窗口编码避免中文乱码
	system("chcp 65001 > nul");

	// printf("hello world!\n");
	// printf("你好你好！\n");getchar();
	toCalcMain();

	
	return 0;
}