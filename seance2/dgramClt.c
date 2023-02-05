#include "dgramInc.h"

int main ()
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
  
  CHECK(connect(sock, (struct sockaddr *) &svc, sizeof(svc)), "Can't connect !");
  
  printf("Connecté !\n");

  CHECK(write(sock, MSG, strlen(MSG) + 1),"Can't send");

  printf("Message envoyé !\n");

  char buffer[100];

  /*
    L'erreur de connexion apparaitra lorsque le client va essayer de lire un message
    Si la connexion n'a pas lieu, la fonction read retournera une erreur
  */
  CHECK(read(sock, buffer, 100),"Can't receive");

  printf("Recu : %s\n", buffer);

  close (sock);
  return 0;
}
