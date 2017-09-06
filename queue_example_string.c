/*
 * queue_example_string.c
 *
 *  Created on: 2017. 8. 30.
 *      Author: LGCNS
 */


#include<stdio.h>
#include<glib.h>
#include<string.h>
#include<stdlib.h>
typedef struct PERSON
{
	char abName[15];
	int nAge;
}PERSON;
static void _free_fun(gpointer data)
{
	printf("free_fun\n");
	if(data)
		free(data);
}


void printPerson(gpointer item) {
	printf("%s\n", (char*)item);
}
gint sorter(gconstpointer a, gconstpointer b, gpointer data) {
	return memcmp((char*)a, (char*)b, strlen((char*)a)>strlen((char*)b)?strlen((char*)a):strlen((char*)b));
}
int main()
{


	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	 GQueue* q = g_queue_new();
	// char buf[1024]={0,};
	 char* buf;
	 buf= malloc(strlen("Misa"));
	 sprintf(buf,"%s","Misa");
	 g_queue_push_tail(q, buf);
	 buf= malloc(strlen("Binna"));
	 sprintf(buf,"%s","Binna");

	 g_queue_push_tail(q, buf);
	 buf= malloc(strlen("Jeon"));
	 sprintf(buf,"%s","Jeon");

	 g_queue_push_tail(q, buf);

	 buf= malloc(strlen("Lim"));
	 sprintf(buf,"%s","Lim");

	 g_queue_push_tail(q, buf);

	 printf("Original queue: \n");
	 g_queue_foreach(q, (GFunc)printPerson, NULL);
	 g_queue_sort(q, (GCompareDataFunc)sorter, NULL);
	 printf("Sorted queue: \n");
	 g_queue_foreach(q, (GFunc)printPerson, NULL);
	 printf("%s\n",(char*)g_queue_pop_head(q));

	 g_queue_free_full(q,_free_fun);


	return 0;
}



