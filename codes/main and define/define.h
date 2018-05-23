#pragma once
#ifndef __DEFINE__H__
#define __DEFINE__H__

/*****************头文件定义*********************/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdbool.h>
#include<ctype.h>

/*******************常量定义**********************/

#define MAXlen 1000	//染色体长度
#define MAXnum 1000	//种群容量
#define MOVEage 30	//移民间隔
#define MAXage 1000	//最大代数
#define ISLAND 2	//岛屿数量
#define MUTATION 0.1	//突变概率
#define CROSS 0.5	//交叉概率

/*******************结构定义**********************/

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


/*************声明全局变量*******************/

extern DATA **data;//输入数据
extern GENE island[2][MAXnum];//岛屿
extern PROCESS **Process;//使用二维数组存放解码出的设计图
extern int Element;//需加工的工件总数
extern int Machine;//机器总数
extern int Job;//总操作数
extern int MutantRange;//发生突变的区间
extern int CrossoverRange;//发生交叉的区间
extern int after_select[ISLAND][MAXnum];//选择后的基因映射
extern double Sum_fitness[2];//岛屿中所有个体适应度的和

/************************FOR DEBUG***********************

	extern int mutanted[ISLAND][MAXnum];//表示经过突变的个体mutanted[island][index of the mutanted]


*/

/*******************声明全局函数**************************/

extern void input(void);
extern void InitGen(void);
extern void decode(GENE* unit);
extern void sort(int x, int y, GENE *island, GENE *temporary);
extern void crossover(int group);
extern void move(void);
extern void mutant(void);


#endif