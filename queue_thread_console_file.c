/*
 * console_input.c
 *
 *  Created on: 2017. 8. 30.
 *      Author: LGCNS
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<errno.h>
#include<glib.h>
void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}
//char arr[1024][50]={0,};
//int nCount=0;

int typeCount =0;
static void _free_fun(gpointer data)
{
	if(data)
		free(data);
}

typedef struct
{
	char type[10];
	int count;
}TYPE_INFO;
TYPE_INFO typelist[10];
char arr[1024][50];
int totalRecordCount = 0;
static void* write_fun();
static void* read_file_fun();
static void* input_console_fun();
int isExit = 0;
FILE* fdRead;
FILE* fdWrite;
pthread_mutex_t mutex;
#include "sys/stat.h"
static size_t get_file_size (const char * file_name) ;
pthread_t inputThread;
GQueue* q;
void main()
{
	pthread_t writeThread;
	pthread_t readFileThread;


	//system("rm *log*.txt");
	//system("./generateFile.exe 100 1000");


	fdRead = fopen("generatedFile.txt","r");
	fdWrite = fopen("log.txt","w");
	q = g_queue_new();
	pthread_mutex_init(&mutex,NULL);

	pthread_create(&writeThread, NULL,write_fun,NULL);
	pthread_create(&readFileThread,NULL, read_file_fun,NULL);
	pthread_create(&inputThread,NULL, input_console_fun, NULL);
	pthread_detach(readFileThread);
	pthread_detach(inputThread);

	pthread_join(writeThread,NULL);
	//pthread_join(writeThread,NULL);
	//pthread_join(writeThread,NULL);
	//pthread_cancel(readFileThread);
	//pthread_cancel(inputThread);
	while(!isExit);

	//pthread_join(inputThread,NULL);
	pthread_mutex_destroy(&mutex);
	g_queue_free_full(q,_free_fun);
	fclose(fdRead);
	fclose(fdWrite);
}

void printMenu()
{
	printf("\nplease input string\n");
}


static void* read_file_fun()
{
	char buf[1024]={0,};
	size_t prevFileSize=0;
	int point;
	char* token;
	char* temp;
	while(!isExit)
	{
		if( point!=get_file_size("generatedFile.txt"))
		{

			memset(buf,0x00,sizeof(buf));
			if(fgets(buf,sizeof(buf),fdRead)!= NULL)
			{
				token= strtok(buf,"\r\n");
				printf("read from file: %s\n",token);
				if( buf[0]=='q' )
				{
					isExit = 1;
					break;
				}
				pthread_mutex_lock(&mutex);
				//memcpy(arr[totalRecordCount++],buf,strlen(buf));
				temp = (char*)malloc(strlen(buf)+1);
				memset(temp,0x00,strlen(buf)+1);
				memcpy(temp, buf,strlen(buf));
				g_queue_push_tail(q,temp );
				pthread_mutex_unlock(&mutex);
			}

			point =ftell(fdRead);
			//fseek(fdRead,point,SEEK_CUR);
			//prevFileSize = get_file_size("generatedFile.txt");
		}
		//printf("read attemp\n");
		usleep(100000);
	}

}
static void* write_fun()
{
	int nWriteCount =0;
	char* data;
	char* prevData =NULL;
	while(!isExit)
	{
		pthread_mutex_lock(&mutex);
		if( !g_queue_is_empty(q))
		{

			data = g_queue_pop_head(q);
			if(prevData==NULL || memcmp(prevData,data,strlen(data))!=0)
			{
				fprintf(fdWrite,"%s\n", data);
				//printf();
			}
			else
			{
				printf("중복\n");
			}
			if(prevData!= NULL)
				free(prevData);
			//nWriteCount++;
			//fprintf(fdWrite,"%s\n", data);
			prevData = (char*)malloc(sizeof(char)*strlen(data));
			memcpy(prevData,data,strlen(data));

		}
		pthread_mutex_unlock(&mutex);
		//printf("write attemp\n");
		usleep(100000);

	}
	while(!g_queue_is_empty(q))
	{

		data = g_queue_pop_head(q);
		if(prevData==NULL || memcmp(prevData,data,strlen(data))!=0)
		{
			fprintf(fdWrite,"%s\n", data);

		}
		if(prevData!= NULL)
			free(prevData);

		prevData = (char*)malloc(sizeof(char)*strlen(data));
		memcpy(prevData,data,strlen(data));
	}

}
static void* input_console_fun()
{
	char buf[1024]={0,};
	char* temp;
	while(!isExit)
	{
		printMenu();
		scanf("%s",buf);
		printf("read from console:%s\n",buf);
		if(strlen(buf)==1 && buf[0]=='q')
		{
			isExit = 1;
			break;
		}
		//뮤텍스 락
		pthread_mutex_lock(&mutex);
		//memcpy(arr[totalRecordCount++],buf,strlen(buf));
		temp = (char*)malloc(strlen(buf)+1);
		memset(temp,0x00,strlen(buf)+1);
		memcpy(temp, buf,strlen(buf));
		g_queue_push_tail(q,temp );
		pthread_mutex_unlock(&mutex);
		//뮤텍스 언락


	}

}
static size_t get_file_size (const char * file_name)
{
	struct stat sb;
	if (stat (file_name, & sb) != 0)
	{
		fprintf (stderr, "'stat' failed for '%s': %s.\n", file_name, strerror (errno));
		exit (EXIT_FAILURE);
	}
	return sb.st_size;
}


