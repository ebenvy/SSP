/*
 * conv_03.c popen사용하여 코드 변환
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct car
{
	char carNo[4];
	char dot;
	char rideTime[10];
	char tmp;
}CAR;

typedef struct carlist
{
	char carNo[4];
	int carCount;
	int totalRideTime;
	double avgRideTime;
}CARLIST;

int nTotalCnt;
int nCountCar;
void readFile();
void makeTypeList();
void writeEachLogFile();

CAR stCar[100];
CARLIST stCarList[20];

int main(void)
{
	readFile();
	makeTypeList();
	writeEachLogFile();
}

void readFile()
{
	FILE *fp;
	int result=0;
	fp = fopen("input01.dat", "rb");

	while(1)
	{
		result=fread(&stCar[nTotalCnt], sizeof(CAR), 1, fp);

		if(result <= 0)
		{
			printf("read file finish\n");
			break;
		}
		nTotalCnt++;
	}

	if(fp)
	{
		fclose(fp);
	}
}


void makeTypeList()
{
	 int i=0;
	 int j=0;

	 for(i=0; i<nTotalCnt; i++)
	 {
		 for(j=0; j<(nCountCar+1); j++)
		 {
			 if(memcmp(stCar[i].carNo, stCarList[j].carNo, sizeof(stCar[i].carNo))==0)
			{
				 stCarList[j].carCount++;
				 stCarList[j].totalRideTime += atoi(stCar[i].rideTime);
				 break;
			}

			 if(j==nCountCar)
			 {
				 memcpy(stCarList[j].carNo, stCar[i].carNo, sizeof(stCar[i].carNo));
				 stCarList[j].carCount = 1;
				 stCarList[j].totalRideTime = atoi(stCar[i].rideTime);
				 nCountCar++;
				 break;
			 }
		 }
	 }

}

void writeEachLogFile()
{
	int i=0;
	int j=0;
	FILE *fp[20];
	FILE *fconv;
	char fileName[20] ={0,};
	char convBuf[20] ={0,};
	char msg[20] ={0, };

	for(i=0; i<nCountCar; i++)
	{

		printf("%.4s\n",stCarList[i].carNo);
		sprintf(fileName, "%.4s_log.txt", stCarList[i].carNo);
		fp[i] = fopen(fileName, "wb");

		sprintf(convBuf, "./conv.exe %.4s", stCarList[i].carNo);

		fconv = popen(convBuf, "r");

		if(fconv== NULL)
		{
			printf("popen fail\n");
			break;
		}

		while(fgets(msg, 20, fconv) != NULL)
		{

		}

		for(j=0; j<nTotalCnt; j++)
		{
			if(memcmp(stCarList[i].carNo, stCar[j].carNo, sizeof(stCarList[i].carNo))==0)
			{
				fprintf(fp[i], "%s@%.10s\n",msg, stCar[j].rideTime);
			}

		}

		if(fp[i])
		{
			fclose(fp[i]);
		}

	}


}
