#include "streamInc.h"

void dialogueSrv (int sd, struct sockaddr_in *srv);

int main ()
{
  int sock;
  struct sockaddr_in svc;
  struct sockaddr_in sock_info;
  socklen_t infoLen=sizeof(struct sockaddr);
  CHECK (sock = socket (PF_INET, SOCK_STREAM, 0), "Can't create");
  svc.sin_family = PF_INET;
  svc.sin_port = htons (PORT_SVC);
  svc.sin_addr.s_addr = inet_addr (INADDR_SVC);
  memset (&svc.sin_zero, 0, 8);
  //PAUSE("Before connect");
  CHECK (connect (sock, (struct sockaddr *) &svc, sizeof svc), "Can't connect");	// Dialogue avec le serveur
  CHECK (getsockname(sock, (struct sockaddr *) &sock_info, &infoLen),"Can't get sock name");
  printf("Server listening on %s, port %d\n",inet_ntop(AF_INET,&sock_info.sin_addr,buffer,sizeof(buffer)),ntohs(sock_info.sin_port));
  getpeername(sock, (struct sockaddr *) &sock_info, &infoLen);
  printf("Connected to server %s on port %d\n",inet_ntop(AF_INET,&sock_info.sin_addr,buffer,sizeof(buffer)),ntohs(sock_info.sin_port));
  dialogueSrv (sock, &svc);
  close (sock);
  return 0;
}

void dialogueSrv (int sd, struct sockaddr_in *srv)
{
  char reponse[MAX_BUFF];
  PAUSE("Before write 100");
  CHECK (write (sd, MSG, strlen (MSG) + 1), "Can't send");
  CHECK ((read (sd, reponse, sizeof (reponse))), "Can't receive");
  printf("Answer received from server: %s\n",reponse);
}
