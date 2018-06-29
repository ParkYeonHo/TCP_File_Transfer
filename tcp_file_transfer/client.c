#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define BUFSIZE 1400

int
main (int argc, char *argv[])
{

  int sd;
  struct sockaddr_in sin;
  char buf[BUFSIZE];
  char buf1[BUFSIZE];

  int fd;
  int len;

  fd = open (argv[3], O_WRONLY | O_CREAT, 0666); // open file using descriptor 
 
  memset ((char *) &sin, '\0', sizeof (sin));       
  sin.sin_family = AF_INET;
  sin.sin_port = htons (atoi (argv[1]));           // connect port
  sin.sin_addr.s_addr = inet_addr (argv[2]); //serer ip

  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == 1)
    {
      perror ("socket");
      exit (1);
    }


  if (connect (sd, (struct sockaddr *) &sin, sizeof (sin)))
    {
      perror ("connect");
      exit (1);
    }

   strcpy (buf,argv[3]);                 // copy file name to buf

   write(sd, buf,sizeof(buf));           // send filename which client want to



  while ((len = recv (sd, buf1, sizeof (buf1), 0)) != 0) // receive file data from server
    {
      write (fd, buf1, len);               // write data to file
    } 



  close (fd);
  close (sd);
  return 0;
}
