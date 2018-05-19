#include"define.h"
DATA **data;//输入数据
GENE island[2][MAXnum];//2个岛屿
PROCESS **Process;//使用二维数组存放解码出的设计图
int Element;//需加工的工件总数
int Machine;//机器总数
int Job;//总操作数，也就是基因的实际长度
int main()
{
	int i;
	data = (DATA**)malloc(Element * sizeof(DATA*));
	for (i = 0; i < Element; i++)
	{
		data[i] = (DATA*)malloc(Machine * sizeof(DATA));
	}
	system("pause");
	return 0;
}