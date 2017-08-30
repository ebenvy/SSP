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
	//if(data)
		//free(data);
}


void printPerson(gpointer item) {
	printf("%d\n", GPOINTER_TO_INT(item));
}
gint sorter(gconstpointer a, gconstpointer b, gpointer data) {
	if(GPOINTER_TO_INT(a) >GPOINTER_TO_INT(b))
		return 1;
	return -1;

}
int main()
{


	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	 GQueue* q = g_queue_new();

	 g_queue_push_tail(q, GINT_TO_POINTER(1));
	 g_queue_push_tail(q, GINT_TO_POINTER(4));
	 g_queue_push_tail(q, GINT_TO_POINTER(3));
	 g_queue_push_tail(q, GINT_TO_POINTER(2));

	 printf("Original queue: \n");
	 g_queue_foreach(q, (GFunc)printPerson, NULL);
	 g_queue_sort(q, (GCompareDataFunc)sorter, NULL);
	 printf("Sorted queue: \n");
	 g_queue_foreach(q, (GFunc)printPerson, NULL);
	 g_queue_free_full(q,_free_fun);


	return 0;
}



