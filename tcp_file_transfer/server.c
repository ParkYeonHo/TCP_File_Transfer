#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 1400

int file_size;


void *
file_send (void *vargp)
{

  char *buffer;
  char buf[BUFSIZE];
  char filename[BUFSIZE];

  int *ns = (int *) vargp;
  int file_size;

  FILE *p;

  read (*ns, filename, BUFSIZE);	//read  file name from client

  if (p = fopen (filename, "r"))
    {

      fseek (p, 0, SEEK_END);	// move to end of file
      file_size = ftell (p);	// calculate file size
      buffer = malloc (file_size + 1);
      memset (buffer, 0, file_size + 1);
      fseek (p, 0, SEEK_SET);	// move to beginning of the file
      fread (buffer, file_size, 1, p);
    }

  send (*ns, buffer, file_size, 0);	// transfer file to clients


  close (*ns);
  free (ns);
  fclose (p);
  return NULL;
}


int
main (int argc, char *argv[])
{


  char path[30];
  struct sockaddr_in sin, cli;
  int sd, clientlen = sizeof (cli);
  pthread_t tid;
  int *ns;

  getcwd (path, 1024);
  strcat (path, argv[2]);
  chdir (path);			// change directory 


  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("socket");
      exit (1);
    }

  memset ((char *) &sin, '\0', sizeof (sin));
  sin.sin_family = AF_INET;
  sin.sin_port = htons (atoi (argv[1]));
  sin.sin_addr.s_addr = inet_addr ("0.0.0.0");


  if (bind (sd, (struct sockaddr *) &sin, sizeof (sin)))
    {
      perror ("bind");
      exit (1);
    }

  if (listen (sd, 5))
    {
      perror ("listen");
      exit (1);
    }


  while (1)			// accpet client request 
    {

      ns = (int *) malloc (sizeof (int));	// ns : socket descriptor
      if ((*ns = accept (sd, (struct sockaddr *) &cli, &clientlen)) == -1)	// accept client request
	{
	  perror ("accept");
	  exit (1);
	}

      pthread_create (&tid, NULL, file_send, ns);	// make a new thread to process client request
    }
  return 0;
}
