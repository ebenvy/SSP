
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

void mythread(gpointer data, gpointer user_data)
{

	 for(int i = 0; i<10;i++)
	{
		printf("%d\n", GPOINTER_TO_INT(data));

		sleep(1);
	}

}

void main()
{

    GThreadPool *pool;

    if(!g_thread_supported())
         g_thread_init(NULL);

     /* create thread pool 10*/
     pool = g_thread_pool_new(mythread, NULL, 10, FALSE, NULL);
     if (pool==NULL)
         printf("ERROR\n");


    for(int i = 0; i<20;i++)
    {
    	 g_thread_pool_push(pool, GINT_TO_POINTER(i), NULL);
    }
    /* start three threads */

     g_thread_pool_free(pool, FALSE,TRUE);

}
