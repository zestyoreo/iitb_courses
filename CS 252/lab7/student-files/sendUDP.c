// Program to send a single UDP packet of given size to a given destination
// Bhaskaran Raman, br@cse.iitb.ac.in, 09 Mar 2008

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 2000
#define MAXSIZE 4096

/* Print usage of program */
void usage(char *progname) {
  fprintf(stderr, "%s <remote-host> <pkt-size>\n",
	  progname);
} // End usage()

int main(int argc, char *argv[]) {
	
  /* The socket descriptor */
  int sock_fd;
  /* Address to which to send packets */
  struct sockaddr_in to_addr;
  /* Node to which to send packets */
  char to_host[256];
  /* Node to which to send packets */
  struct in_addr to_ip;
  /* Port to which to send packets */
  int to_port = PORT;
  /* The bytes to send (dummy content) */
  char buf[MAXSIZE];

   /* Get command-line arguments */
  if(argc != 3) { usage(argv[0]); exit(1); }
  strcpy(to_host, argv[1]);
  int pktsize = atoi(argv[2]);
  if((pktsize < 0) || (pktsize > MAXSIZE)) {
    fprintf(stderr, "Packet size has to be >= 0 and <= %d\n", MAXSIZE);
    exit(2);
  }

  /* socket */
  sock_fd = socket(PF_INET, SOCK_DGRAM, getprotobyname("udp")->p_proto);
  if(sock_fd < 0) { perror("socket failed"); exit(20); }
  fprintf(stderr, "socket successful\n");

  /* init to_addr */
  struct hostent *server = gethostbyname(to_host);
  bzero((char *)&to_addr, sizeof(to_addr));
  bcopy((char *)server->h_addr, (char *)&to_addr.sin_addr.s_addr,
	server->h_length);
  to_addr.sin_family = PF_INET;
  to_addr.sin_port = htons(to_port);

  int res = sendto(sock_fd, (void *)(buf), pktsize, 0,
		   (struct sockaddr *)&to_addr, sizeof(to_addr));
  if(res != pktsize) {
    perror("sendto");
    exit(3);
  }

} // End main()
