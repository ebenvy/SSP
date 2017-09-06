/*
 * readDirectory.c
 *
 *  Created on: 2017. 9. 6.
 *      Author: LGCNS
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <error.h>

int main()
{
	  DIR *dir;
	  struct dirent *ent;
	  dir = opendir ("./");
	  if (dir != NULL) {

			  /* print all the files and directories within directory */
			  while ((ent = readdir (dir)) != NULL) {
				  //파일명에 .log 포함된 경우
				  	  if(strstr(ent->d_name,".log")!= NULL)
				  		  printf ("%s\n", ent->d_name);
			  }
			  closedir (dir);
	  } else {
			  /* could not open directory */
			  perror ("");
			  return EXIT_FAILURE;
	  }
}
