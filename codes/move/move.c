#include"define.h"

//使用到的全局变量有island

void move()//移民
{
	GENE best[2];//存放两个最优个体
	int i, j, k;
	best[0] = island[1][0];
	best[1] = island[0][0];
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < MAXnum && island[i][j].makespan < best[i].makespan; j++);
		if (j != MAXnum)
		{
			for (k = MAXnum - 1; k > j; k--)
			{
				island[i][k] = island[i][k - 1];
			}
			island[i][j] = best[i];
		}
	}

}
