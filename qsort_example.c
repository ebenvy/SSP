/*
 * qsort_example.c
 *
 *  Created on: 2017. 8. 29.
 *      Author: LGCNS
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char abType[2];
	int nCount;
}TYPE;
TYPE* typeList;
int compare_fun(void* a, void* b);
void main()
{
	typeList = malloc(sizeof(TYPE)*10);
	for(int i=0;i<10; i++)
	{
		sprintf(typeList[i].abType,"A%d",i);
		typeList[i].nCount = 10-i;
	}
	for(int i=0;i<10; i++)
	{
		printf("%.2s: %d\n",typeList[i].abType,typeList[i].nCount);
	}
	qsort(typeList,10,sizeof(TYPE),compare_fun);
	for(int i=0;i<10; i++)
	{
		printf("%.2s: %d\n",typeList[i].abType,typeList[i].nCount);
	}

}
//오름 차순
int compare_fun(void* a, void* b)
{
	TYPE *left = (TYPE *)a;
	TYPE *right = (TYPE *)b;

	if(left->nCount> right->nCount)
	{
		return 1;
	}
	return -1;
}
//내림 차순
/*int compare_fun(void* a, void* b)
{
	TYPE *left = (TYPE *)a;
	TYPE *right = (TYPE *)b;

	if(left->nCount< right->nCount)
	{
		return 1;
	}
	return -1;
}*/
