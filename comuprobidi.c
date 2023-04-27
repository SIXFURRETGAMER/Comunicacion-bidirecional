// Christopher Dominguez Solis 4CM1

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256

int tuberia_emisor_receptor[2];
int tuberia_receptor_emisor[2];
int pid;
char mensaje[MAX];
char listo[]="listo";

int main(int argc, char const *argv[]) {
  if (pipe (tuberia_emisor_receptor)==-1){
    perror ("pipe");
    exit (-1);
  }

  if (pipe (tuberia_receptor_emisor)==-1)
  {
    perror("pipe");
    exit (-1);
  }

  if ((pid=fork())==-1)
  {
    perror ("fork");
    exit (-1);
  } else if (pid==0){
    while (read(tuberia_emisor_receptor[0],mensaje,MAX) > 0 && strcmp (mensaje,"FIN\n")!=0)
	{
      printf("Proceso receptor. MENSAJE:%s\n",mensaje);
    write(tuberia_receptor_emisor[1],listo,5+1);
    }

    close (tuberia_emisor_receptor[0]);
    close (tuberia_emisor_receptor[1]);

    close(tuberia_receptor_emisor[0]);
    close(tuberia_receptor_emisor[1]);

    exit (0);
  }
  else
  {
    do
    {
        printf("Proceso emisor. Introduce el mensaje:\n");
        fgets (mensaje,sizeof (mensaje),stdin)!=NULL;
        write(tuberia_emisor_receptor[1],mensaje,strlen(mensaje)+1)>0;
        read(tuberia_receptor_emisor[0],listo,5);
    }
    while (strcmp(listo,"listo\n")!=0 && strcmp(mensaje,"FIN\n")!=0 );

    close(tuberia_receptor_emisor[1]);
    close(tuberia_receptor_emisor[0]);

    close (tuberia_emisor_receptor[1]);
    close (tuberia_emisor_receptor[0]);
    exit (0);
  }
}
