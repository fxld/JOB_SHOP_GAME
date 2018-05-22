#include"define.h"

DATA **data=NULL;//输入数据data[Element][Machine]
GENE island[ISLAND][MAXnum];//2个岛屿
PROCESS **Process=NULL;//使用二维数组存放解码出的设计图Process[Machine][Element]
int after_select[ISLAND][MAXnum];//选择后基因的映射after_select[island][index of the selected],当after_selected[i][j]=-1时,表示已经进行过基因操作或是未选择
int Element;//需加工的工件总数
int Machine;//机器总数
int Job;//总操作数，也就是基因的实际长度
int age;//当前进化代数
int MutantRange ;//当rand()的值在[0,MutantRange]时发生突变
int CrossoverRange ;//当rand()的值在[0,CrossoverRange]时发生交叉
double Sum_fitness[2] ;//岛屿中所有个体适应度的和

/***************************FOR DEBUG*************************************
*	int mutanted[ISLAND][MAXnum];//表示经过突变的个体mutanted[island][index of the mutanted]
*
*/

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
	input();//输入

	data = (DATA**)malloc(Element * sizeof(DATA*));//data申请内存
	for (int i = 0; i < Element; i++)
	{
		data[i] = (DATA*)malloc(Machine * sizeof(DATA));
	}
	Process = (PROCESS**)malloc(Machine * sizeof(PROCESS*));//Process申请内存
	for (int i = 0; i < Machine; i++)
	{
		Process[i] = (PROCESS*)malloc(Element * sizeof(PROCESS));
	}
	GENE *temporary = NULL;//临时空间
	temporary = (GENE*)malloc(MAXnum * sizeof(GENE));

	code();//生成初始种群

	for (int i = 0; i < ISLAND; i++)//解码计算适应度and排序
	{
		for (int j = 0; j < MAXnum; i++)
		{
			decode(&island[i][j]);//解码计算适应度
			Sum_fitness[i] += island[i][j].fitness;
		}
		sort(0, MAXnum, island[i], temporary);//排序
	}
	
	srand((unsigned int)time(NULL));
	for (age = 0; age < MAXage; age++)//进化
	{
		//调用判断函数判断是否达成跳出循环的条件

	}

	if (island[0][0].makespan < island[1][0].makespan)//选择出当前最优解，解码后存入Process中
	{
		decode(&island[0][0]);
	}
	else
	{
		decode(&island[1][0]);
	}
	/*此时Process中存放的是最优解的解析图*/
	output();//输出

	/****************内存释放****************/
	for (int i = 0; i < Element; i++)
	{
		free(data[i]);
	}
	free(data);
	for (int i = 0; i < Machine; i++)
	{
		free(Process[i]);
	}
	free(Process);
	free(temporary);
	system("pause");
	return 0;
}
