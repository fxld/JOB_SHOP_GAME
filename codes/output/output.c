#include"define.h"
/*
使用的全局变量：Element,Machine,BestProcess
*/
void output(void)//命令行输出
{
	int i, j;
	for (i = 0; i < Machine; i++)
	{
		printf("M%d", i);
		for (j = 0; j < Element&&BestProcess[i][j].component != -1; j++)
		{
			printf(" (%d,%d-%d,%d)", BestProcess[i][j].start, BestProcess[i][j].component, BestProcess[i][j].operation, BestProcess[i][j].end);
		}
		printf("\n");
	}
	printf("Time Used: %.3fs\n",(double)clock()/1000);
	printf("End Time: %d", BestMakeSpan);
}