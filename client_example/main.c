
#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include"./client.h"
void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}


void* inputMenuLoop();
void printMenu();
void requestGoods();
int main(int argc, char **argv)
{

	pthread_t thread;
	if(argc != 2){
	  printf("Usage : %s <client name> \n", argv[0]);
	  exit(1);
	}
	pthread_create(&thread, NULL, inputMenuLoop, NULL);
	connectServer(argv[1]);

}

void printMenu()
{
	printf("===============================\n");
	printf("=1. send message                 =\n");
	printf("===============================\n");
}
void* inputMenuLoop()
{
	int nMenu;
	char buf[1024]={0,};
	while(1)
	{
		printMenu();
		scanf("%d",&nMenu);
		printf("[%d]",nMenu);
		switch(nMenu)
		{
		case 1:
			printf(" send message\n");
			scanf("%s",buf);
			send_message(buf);
			break;

		default:
			printf(" quit program\n");
			exit(1);

			break;
		}

	}
}
