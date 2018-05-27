#include"define.h"

//全局变量有age

#define END 0
#define CONTINUE 1

int terminate(void)
{
	if (age >= MAXage||clock()>TIMELIMIT)	//固定代数终止、超时终止
		return END;
	return CONTINUE;
}