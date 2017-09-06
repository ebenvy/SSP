/*
 * typeSeperate.c
 *
 *  Created on: 2017. 9. 6.
 *      Author: LGCNS
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE_UNIT 20
typedef struct type_struct
{
	char type[20];
	int count;
}TYPE;
TYPE* typeList;
int nCountType;
int nSizeList;
int main()
{

	char buf[1024]={0,};
	while(1)
	{
		memset(buf, 0x00, sizeof(buf));
		scanf("%s",buf);

		if(strlen(buf)==1 && buf[0]=='q')
			break;
		if(nCountType >= nSizeList )
		{
			nSizeList = (int)((nCountType/SIZE_UNIT)+1)*SIZE_UNIT;
			typeList = (TYPE*)realloc(typeList,sizeof(TYPE)*nSizeList);
		}

		enrollType(buf);
	}
	printTypeInfo();
	free(typeList);
	return 0;
}

void enrollType(char* type)
{
	int i;
	for(i=0;i<nCountType;i++)
	{
		if((strlen(typeList[i].type) == strlen(type))&&memcmp(typeList[i].type,type,strlen(type))==0)
		{
			typeList[i].count++;
			break;
		}
	}
	if( i == nCountType)
	{
		memcpy(typeList[i].type, type, strlen(type));
		typeList[i].count =1;
		nCountType++;
	}

}

void printTypeInfo()
{
	for(int i=0;i<nCountType;i++)
	{
		printf("%.20s: %d\n",typeList[i].type, typeList[i].count);
	}
}
