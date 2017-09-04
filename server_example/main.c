/*
 * main.c
 *
 *  Created on: 2017. 9. 4.
 *      Author: LGCNS
 */

#include<stdio.h>
#include<stdlib.h>
#include"./server.h"

void __attribute__((constructor))console_setting_for_eclipse_debugging(void)
{
	setvbuf(stdout,NULL, _IONBF,0);
	setvbuf(stderr,NULL, _IONBF,0);
}
void* inputMenuLoop();
void printMenu();


int main()
{
	pthread_t thread;

	pthread_create(&thread, NULL, inputMenuLoop, NULL);
	connectServer();

}
void printMenu()
{
	printf("===============================\n");
	printf("=1. send message to all =\n");
	printf("=2. print connected client info =\n");
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

		switch(nMenu)
		{
		case 1:
			printf("send message \n");
			scanf("%s",buf);
			broadcast(buf);

			break;
		case 2:
			printf(" print connected client info \n");
			printf("%d clients are connected\n",getClientNumber());
			break;
		default:
			printf(" quit program\n");
			exit(1);
			break;
		}

	}
}
