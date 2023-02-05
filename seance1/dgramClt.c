#include "dgramInc.h"

int
main ()
{
  int sock;
  struct sockaddr_in svc;

// Création de la socket pour envoi de la requête
  CHECK (sock = socket (PF_INET, SOCK_DGRAM, 0), "Can't create");
// Préparation de l’adressage du service à contacter
  svc.sin_family = PF_INET;
  svc.sin_port = htons (PORT_SVC);
  svc.sin_addr.s_addr = inet_addr (INADDR_SVC);
  memset (&svc.sin_zero, 0, 8);
// Envoi d’un message au serveur
// PAUSE ("Before call to sendto");
  CHECK (sendto
	 (sock, MSG, strlen (MSG) + 1, 0, (struct sockaddr *) &svc,
	  sizeof svc), "Can't send");

  char buffer[100];

  socklen_t SvcLen = sizeof(svc);

  CHECK (recvfrom
	     (sock, buffer, sizeof (buffer), 0, (struct sockaddr *) &svc,
	      &SvcLen), "Can't receive");

  printf("Recu : %s\n", buffer);

  // PAUSE ("Before call to close");
  close (sock);
  return 0;
}
