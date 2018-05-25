#include"define.h"

//全局变量有age

#define END 0
#define CONTINUE 1

int terminate(void)
{
	if (age >= MAXage)	//固定代数终止
		return END;
	return CONTINUE;
}