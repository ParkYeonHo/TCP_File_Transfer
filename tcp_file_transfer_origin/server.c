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

char *buffer1, *buffer2, *buffer3, *buffer4, *buffer5, *buffer6, *buffer7,
  *buffer;               // read file data to buffer ,  *buffer : selected buffer 
int file_size_ary[6];    // file size array 
int *real_file_size;     // selected file_size


void *file_send (void *vargp);

void
file_check (char *file_name)         
{                               

  if (strcmp (file_name, "1.mkv") == 0)    
    {                                            

		real_file_size=malloc(file_size_ary[0]);   // dynamic allocation file size
		*real_file_size=file_size_ary[0];
        buffer = malloc(file_size_ary[0]);          // dynamic allocation buffer size 
		buffer = buffer1;

    }
  else if (strcmp (file_name, "2.fna") == 0)
    {
    
	real_file_size=malloc(file_size_ary[1]);
	        *real_file_size=file_size_ary[1];
	        buffer = malloc(file_size_ary[1]);
	        buffer = buffer2;
	}
  else if (strcmp (file_name, "a.mp3") == 0)
    {
    
	real_file_size=malloc(file_size_ary[2]);
	        *real_file_size=file_size_ary[2];
	        buffer = malloc(file_size_ary[2]);
	        buffer = buffer3;
	}
  else if (strcmp (file_name, "b.mp3") == 0)
    {
    
	real_file_size=malloc(file_size_ary[3]);
	        *real_file_size=file_size_ary[3];
	        buffer = malloc(file_size_ary[3]);
	        buffer = buffer4;
	}
  else if (strcmp (file_name, "c.mp3") == 0)
    {
    
	real_file_size=malloc(file_size_ary[4]);
	        *real_file_size=file_size_ary[4];
	        buffer = malloc(file_size_ary[4]);
	        buffer = buffer5;
	}
  else if (strcmp (file_name, "d.mp3") == 0)
    {
    
	real_file_size=malloc(file_size_ary[5]);
	        *real_file_size=file_size_ary[5];
	        buffer = malloc(file_size_ary[5]);
	        buffer = buffer6;
	}
  else
    {
	        
	real_file_size=malloc(file_size_ary[6]);
	        *real_file_size=file_size_ary[6];
	        buffer = malloc(file_size_ary[6]);
	        buffer = buffer7;
	}

	
	
}

void *
file_send (void *vargp)
{

  char buf[BUFSIZE];
  char filename[BUFSIZE];
  int *ns = (int *) vargp;

  int fd;

  read (*ns, filename, BUFSIZE);   //read  file name requested by the client to array

  file_check (filename);            // checking what file is

  fd = open (filename, O_RDONLY);

  if (fd == -1)
    {
      perror ("file open");
      exit (1);
    }

    send (*ns, buffer,*real_file_size, 0);  // Transfer file to clients


  close (fd);
  close (*ns);
  free (ns);
  return NULL;
}



int
main (int argc, char *argv[])
{


  int size;
  int count;
  FILE *p1, *p2, *p3, *p4, *p5, *p6, *p7;
  char path[30];
  struct sockaddr_in sin, cli;
  int sd, clientlen = sizeof (cli);
  pthread_t tid;
  int *ns;

  getcwd (path, 1024);
  strcat (path, argv[2]);
  chdir (path);                // change directory 

  // preloading
  // 1.mkv

  p1 = fopen ("1.mkv", "r");
  fseek (p1, 0, SEEK_END);
  file_size_ary[0] = ftell (p1);
  buffer1 = malloc (file_size_ary[0] + 1);
  memset (buffer1, 0, file_size_ary[0] + 1);
  fseek (p1, 0, SEEK_SET);
  fread (buffer1, file_size_ary[0], 1, p1);

  // 2.fna
  p2 = fopen ("2.fna", "r");
  fseek (p2, 0, SEEK_END);
  file_size_ary[1] = ftell (p2);
  buffer2 = malloc (file_size_ary[1] + 1);
  memset (buffer2, 0, file_size_ary[1] + 1);
  fseek (p2, 0, SEEK_SET);
  fread (buffer2, file_size_ary[1], 1, p2);

  // a.mp3
  p3 = fopen ("a.mp3", "r");
  fseek (p3, 0, SEEK_END);
  file_size_ary[2] = ftell (p3);
  buffer3 = malloc (file_size_ary[2] + 1);
  memset (buffer3, 0, file_size_ary[2] + 1);
  fseek (p3, 0, SEEK_SET);
  fread (buffer3, file_size_ary[2], 1, p3);

  // b.mp3
  p4 = fopen ("b.mp3", "r");
  fseek (p4, 0, SEEK_END);
  file_size_ary[3] = ftell (p4);
  buffer4 = malloc (file_size_ary[3] + 1);
  memset (buffer4, 0, file_size_ary[3] + 1);
  fseek (p4, 0, SEEK_SET);
  fread (buffer4, file_size_ary[3], 1, p4);

  // c.mp3
  p5 = fopen ("c.mp3", "r");
  fseek (p5, 0, SEEK_END);
  file_size_ary[4] = ftell (p5);
  buffer5 = malloc (file_size_ary[4] + 1);
  memset (buffer5, 0, file_size_ary[4] + 1);
  fseek (p5, 0, SEEK_SET);
  fread (buffer5, file_size_ary[4], 1, p5);

  // d.mp3
  p6 = fopen ("d.mp3", "r");
  fseek (p6, 0, SEEK_END);
  file_size_ary[5] = ftell (p6);
  buffer6 = malloc (file_size_ary[5] + 1);
  memset (buffer6, 0, file_size_ary[5] + 1);
  fseek (p6, 0, SEEK_SET);
  fread (buffer6, file_size_ary[5], 1, p6);
 
  // kernel.tar
  p7 = fopen ("kernel.tar", "r");
  fseek (p7, 0, SEEK_END);
  file_size_ary[6] = ftell (p7);
  buffer7 = malloc (file_size_ary[6] + 1);
  memset (buffer7, 0, file_size_ary[6] + 1);
  fseek (p7, 0, SEEK_SET);
  fread (buffer7, file_size_ary[6], 1, p7);




  fclose (p1);
  fclose (p2);
  fclose (p3);
  fclose (p4);
  fclose (p5);
  fclose (p6);
  fclose (p7);


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

  while (1)                                    // loop
    {                                       

      ns = (int *) malloc (sizeof (int));       // ns : socket descriptor
      if ((*ns = accept (sd, (struct sockaddr *) &cli, &clientlen)) == -1) // accept client request
	{
	  perror ("accept");
	  exit (1);
	}

      pthread_create (&tid, NULL, file_send, ns); // make a new thread to process client request
    }
  return 0;
}
