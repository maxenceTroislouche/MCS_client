#include "streamInc.h"
void dialogueSrv(int sd, struct sockaddr_in *srv);
int main()
{
    int sock;
    struct sockaddr_in svc;
    // Création de la socket d’appel et de dialogue
    CHECK(sock = socket(PF_INET, SOCK_STREAM, 0), "Can't create");
    // Préparation de l’adressage du service à contacter
    svc.sin_family = PF_INET;
    svc.sin_port = htons(PORT_SVC);
    svc.sin_addr.s_addr = inet_addr(INADDR_SVC);
    memset(&svc.sin_zero, 0, 8);
    // PAUSE("Before connect");
    // Demande d’une connexion au service
    CHECK(connect(sock, (struct sockaddr *)&svc, sizeof svc), "Can't connect"); // Dialogue avec le serveur
    dialogueSrv(sock, &svc);
    close(sock);
    return 0;
}

// Fonction gérant le dialogue avec le serveur
void dialogueSrv(int sd, struct sockaddr_in *srv)
{
    char reponse[MAX_BUFF];
    // Envoi du message MSG au serveur : la réponse sera OK
    // PAUSE("Before write 100");
    printf("Envoi de <%s> !\n", MSG);
    CHECK(write(sd, MSG, strlen(MSG) + 1), "Can't send");
    // PAUSE("Before read 100");
    printf("Lecture de la réponse serveur !\n");
    CHECK(read(sd, reponse, sizeof(reponse)), "Can't send");
    printf("Message recu %s\n", reponse);
    // Envoi du message ERR au serveur : la réponse sera NOK
    // PAUSE("Before write 200");
    printf("Envoi du message d'erreur : <%s> !\n", ERR);
    CHECK(write(sd, ERR, strlen(ERR) + 1), "Can't send");
    // PAUSE("Before read 100");
    printf("Lecture de la réponse serveur ...\n");
    CHECK(read(sd, reponse, sizeof(reponse)), "Can't send");
    printf("Message recu %s\n", reponse);
    // Envoi du message BYE au serveur : la réponse sera la fin du dialogue
    // PAUSE("Before write 000");
    printf("Envoi de la fin de connexion <%s> ...", BYE);
    CHECK(write(sd, BYE, strlen(BYE) + 1), "Can't send");
    // PAUSE("Before read 100");
    printf("Lecture de la réponse serveur !\n");
    CHECK(read(sd, reponse, sizeof(reponse)), "Can't send");
}
