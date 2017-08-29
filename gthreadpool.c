/*
 * gthread.c
 *
 *  Created on: 2017. 8. 29.
 *      Author: LGCNS
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

void mythread(gpointer data, gpointer user_data)
{
	 for(int i = 0; i<10;i++)
	{
		printf("%d\n", GPOINTER_TO_INT(data));
		printf("%s\n", user_data);
		sleep(1);
	}

}

void main()
{


    char *user_data = "this is user_data";



    GThreadPool *pool;

    if(!g_thread_supported())
         g_thread_init(NULL);

     /* create thread pool 10°³*/
     pool = g_thread_pool_new(mythread, user_data, 10, FALSE, NULL);
     if (pool==NULL)
         printf("ERROR\n");


    for(int i = 0; i<20;i++)
    {
    	 g_thread_pool_push(pool, GINT_TO_POINTER(i), NULL);
    }
    /* start three threads */

     g_thread_pool_free(pool, FALSE,TRUE);

}
