#include"define.h"
/*
使用的全局变量：Element,Machine,Process
*/
void output(void)
{
	int i, j;
	for (i = 0; i < Machine; i++)
	{
		printf("M%d", i);
		for (j = 0; j < Element&&Process[i][j].component != -1; j++)
		{
			printf(" (%d,%d-%d,%d)", Process[i][j].start, Process[i][j].component, Process[i][j].operation, Process[i][j].end);
		}
		printf("\n");
	}
	printf("Time Used: %.3f\n",(double)clock()/1000);
	printf("End Time: %d", BestMakeSpan);
}