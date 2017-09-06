#include<stdio.h>
#include<time.h>
char* Timet2ASCTime(time_t t);
time_t ASCTime2Timet(char* ascTime);
int main()
{
	time_t tNow, tTime;
	char abTime[15]="20170906144300";
	//현재시간 출력하기
	time(&tNow);
	printf("%s\n",Timet2ASCTime(tNow));

	//asc time -> time_t
	printf("%d\n",tTime=ASCTime2Timet(abTime));
	//time_t -> asc time
	printf("%s\n",Timet2ASCTime(tTime));
	return 0;
}
time_t ASCTime2Timet(char* ascTime)
{
	struct tm timeInfo;
	char year[4];
	char mon[2];
	char day[2];
	char hour[2];
	char min[2];
	char sec[2];
	memcpy(year,ascTime,4);
	memcpy(mon,ascTime+4,2);
	memcpy(day,ascTime+6,2);
	memcpy(hour,ascTime+8,2);
	memcpy(min,ascTime+10,2);
	memcpy(sec,ascTime+12,2);

	memset(&timeInfo,0x00,sizeof(timeInfo));
	timeInfo.tm_year = atoi(year)-1900;
	timeInfo.tm_mon = atoi(mon)-1;
	timeInfo.tm_mday = atoi(day);
	timeInfo.tm_hour = atoi(hour);
	timeInfo.tm_min = atoi(min);
	timeInfo.tm_sec = atoi(sec);
	return mktime(&timeInfo);

}
char* Timet2ASCTime(time_t t)
{
	struct tm timeInfo;

	localtime_r(&t,&timeInfo);

	printf("%d %d %d %d \n",timeInfo.tm_year+1900,timeInfo.tm_mon+1,timeInfo.tm_mday,timeInfo.tm_hour,timeInfo.tm_min);
	return asctime(&timeInfo);
}
