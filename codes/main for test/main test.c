#include"define.h"

DATA **data = NULL;//输入数据data[Element][Machine]
GENE island[ISLAND][MAXnum];//2个岛屿
PROCESS **Process = NULL;//使用二维数组存放解码出的设计图Process[Machine][Element]
int after_select[ISLAND][MAXnum];//选择后基因的映射after_select[island][index of the selected],当after_selected[i][j]=-1时,表示已经进行过基因操作或是未选择
int Element;//需加工的工件总数
int Machine;//机器总数
int Job;//总操作数，也就是基因的实际长度
int age;//当前进化代数
int MutantRange = (int)(((double)RAND_MAX)*MUTATION);//当rand()的值在[0,MutantRange]时发生突变
int CrossoverRange = (int)(((double)RAND_MAX)*CROSS);//当rand()的值在[0,CrossoverRange]时发生交叉
double Sum_fitness[2];//岛屿中所有个体适应度的和
int main(void)
{
	/**************************
	*	input();		//输入
	*	initGen();		//生成初始种群
	*	decode();		//解码
	*	fitness();		//计算适应度
	*	while(terminate())//是否达成跳出循环
	*	{
	*		sort();		//排序(依据适应度/运行时间)
	*		select();	//选择
	*		crossover();//交叉
	*		mutant();	//变异
	*		if(age%MOVEage==0)//判断是否迁移
	*			move();	//迁移
	*		decode();	//解码
	*		fitness();	//计算适应度
	*	}
	*	output();		//输出
	*	//animate();
	*	return 0;
	*/
	input();
	InitGen();
	return 0;
}

/*
2
3 3
0 (7,0) (3,1) (15,2)
1 (10,1) (17,0)
2 (7,0) (22,1)
-1
*/