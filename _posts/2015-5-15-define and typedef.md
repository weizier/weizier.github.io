---
layout: post
title: define and typedef in C++
---
typedef int* pint;
#define PINT int*;

	const pint p;   //是为指针常量
	const PINT p;  //是为常量指针

#define 是宏命令，在编译前，由预处理器做替代，如同文本编辑的替代命令，把程序中的所有遇到的词，全部替代。

#define PINT int* 
就是把所有的词 PINT 替换成 int * ，替换完毕再编译。 

typedef int* pint; 是语句，由编译器在编译过程中编译处理。
int* x; 和
pint x; 的声明是等价的

typedef int* pint;
long int* x; 声明是可以的，但
long pint x; 不可以。

#define PINT int* 
long int* x; 声明是可以的，
long PINT x; 也是可以的。
从上两种情况对比，你就知道两者的区别

long,short,signed,unsigned 叫 “Modifiers”

const，volatile 叫 “Qualifiers"

const pint p; 锁定 pint 类型，锁定初始化后的指针地址。

const PINT p; 预处理为
const int * p;  锁定初始化后的指针指向的值

再比如typedef void (*Fun)(void);  //一个指向无返回值无参数的函数的指针，本质是一个指针。再加上typedef关键字之后，就是定义了一个该指针的新类型
char (*pFun)(int);//定义了一个指针，该指针规定指向一个以int类型数据为参数，返回值是char类型的函数