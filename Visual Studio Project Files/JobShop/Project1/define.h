#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>


#define MAXlen 1000//染色体长度
#define MAXnum 1000//种群容量
#define MOVEage 30//移民间隔
#define MAXage 1000


typedef struct //存放输入的数据
{
	int line;//机器号
	int time;//加工时间
}DATA;

typedef struct //单个染色体
{
	int gene[MAXlen];//基因
	int makespan;//最长完工时间
	double fitness;//适应度
}GENE;

typedef struct//解码出的单个机器上的单个工序
{
	int component;//工件号
	int start;//开始时间
	int end;//完成时间
}PROCESS;


/************************声明全局变量***********************/
extern DATA **data;//输入数据
extern GENE island[2][MAXnum];//岛屿
extern PROCESS **Process;//使用二维数组存放解码出的设计图
extern int Element;//需加工的工件总数
extern int Machine;//机器总数
extern int Job;//总操作数