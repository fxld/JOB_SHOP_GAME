#include"define.h"

//使用到的全局变量有data，Job，Element，Process,BestMakeSpan,BestProcess

void decode(GENE* unit)
{
	int i, j, k, m, e, t;
	int num[2][1000] = { 0 };//第0行是工件当前安排到第几个工序，第1行是工件当前完成时间，列数最多使用Element列
	int maxtime = 0;//记录makespan
	for (i = 0; i < Machine; i++)
	{
		for (j = 0; j < Element; j++)
		{
			Process[i][j].component = -1;
		}
	}
	for (k = 0; k < Job; k++)//gene[k]
	{
	//	printf("%d\n", Job);
		e = unit->gene[k];//工件
		m = data[e][num[0][e]].line;//机器
		t = data[e][num[0][e]].time;//时间
		
		
		for (j = 0; Process[m][j].component != -1; j++)//贪心法，寻找可以插入的位置
		{
			if (Process[m][j + 1].component == -1)//需要插入j与j+1之间，若j已经是最后一个操作，就跳过
			{
				if (j == 0 && Process[m][j].start >= t && Process[m][j].start - num[1][e] >= t)
				{
					Process[m][j + 1] = Process[m][j];
					break;
				}
				else continue;
			}
			else if (j == 0 && Process[m][j].start >= t && Process[m][j].start - num[1][e] >= t)
			{
				for (i = Element - 1; i > j; i--)//将j之后的操作全体后移
				{
					Process[m][i] = Process[m][i - 1];
				}
				goto fixbug;
			}
			if ((Process[m][j + 1].start - num[1][e] >= t) && (Process[m][j + 1].start - Process[m][j].end >= t))
			{
				if (j == 0)
				{
					for (i = Element - 1; i > j; i--)//将j之后的操作全体后移
					{
						Process[m][i] = Process[m][i - 1];
					}
					j++;
					goto fixbug;
				}
				break;
			}
		}
		if (Process[m][j].component != -1 && j != 0)//若找到可插入位置，则component一定不为-1
		{
			for (i = Element - 1; i > j; i--)//将j之后的操作全体后移
			{
				Process[m][i] = Process[m][i - 1];
			}
			j++;
		}
		
fixbug:		Process[m][j].component = e;
		if (j == 0)
		{
			Process[m][j].start = num[1][e];
		}
		else
		{
			Process[m][j].start = Process[m][j - 1].end > num[1][e] ? Process[m][j - 1].end : num[1][e];
		}
		Process[m][j].end = Process[m][j].start + t;
		Process[m][j].operation = num[0][e]++;
		maxtime = maxtime > Process[m][j].end ? maxtime : Process[m][j].end;
		num[1][e] = Process[m][j].end;
	}
	unit->makespan = maxtime;//完工时间
	if (BestMakeSpan > maxtime)//最优设计图的保存
	{
		BestMakeSpan = maxtime;
		for (i = 0; i < Machine; i++)
		{
			memcpy(BestProcess[i], Process[i], Element * sizeof(PROCESS));
		}
	}
	//unit->fitness = fitnesscalc(unit->makespan);//适应度
}
/*
int main(void)
{
	input();
	
	GENE test = { { 2,5,5,1,1,1,1,0,1,2,5,4,5,3,0,4,0,3,0,2,3,2,3,2,3,0,1,5,4,5,0,2,4,3,4,4 },0,0 };
	decode(&test);
	return 0;
}
/*typedef struct//解码出的单个机器上的单个工序
{
int component;//工件号
int start;//开始时间
int end;//完成时间
}PROCESS;
Process设计图
data[Element][Machine]输入数据
island[ISLAND][MAXnum]种群
island.gene-->date-->Process
*/