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
    char requete[MAX_BUFF];
    strcpy(requete, "GET / HTTP/1.1\r\nUser-Agent: 2iServer\r\nAccept: */*\r\nAccept-Encoding: identity\r\nHost: 10.1.0.24\r\nConnection: Keep-Alive\r\n\r\n");
    /*
        char requete[] = { 
        0x47, 0x45, 0x54, 0x20, 0x2f, 0x20, 0x48, 0x54, 
        0x54, 0x50, 0x2f, 0x31, 0x2e, 0x31, 0x0d, 0x0a, 
        0x55, 0x73, 0x65, 0x72, 0x2d, 0x41, 0x67, 0x65, 
        0x6e, 0x74, 0x3a, 0x20, 0x57, 0x67, 0x65, 0x74, 
        0x2f, 0x31, 0x2e, 0x32, 0x31, 0x0d, 0x0a, 0x41, 
        0x63, 0x63, 0x65, 0x70, 0x74, 0x3a, 0x20, 0x2a, 
        0x2f, 0x2a, 0x0d, 0x0a, 0x41, 0x63, 0x63, 0x65, 
        0x70, 0x74, 0x2d, 0x45, 0x6e, 0x63, 0x6f, 0x64, 
        0x69, 0x6e, 0x67, 0x3a, 0x20, 0x69, 0x64, 0x65, 
        0x6e, 0x74, 0x69, 0x74, 0x79, 0x0d, 0x0a, 0x48, 
        0x6f, 0x73, 0x74, 0x3a, 0x20, 0x31, 0x30, 0x2e, 
        0x31, 0x2e, 0x30, 0x2e, 0x32, 0x34, 0x0d, 0x0a, 
        0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 
        0x6f, 0x6e, 0x3a, 0x20, 0x4b, 0x65, 0x65, 0x70, 
        0x2d, 0x41, 0x6c, 0x69, 0x76, 0x65, 0x0d, 0x0a, 
        0x0d, 0x0a };
    */

    printf("Requete à envoyer au serveur web : %s\n", requete);

    CHECK(write(sd, requete, strlen(requete) + 1), "Can't send");
    printf("Requete envoyée !\n");

    printf("Lecture de la réponse serveur !\n");
    CHECK(read(sd, reponse, sizeof(reponse)), "Can't read");
    printf("Message recu %s\n", reponse);

    printf("Message en ascii : \n");
    for (int i = 0; i < strlen(reponse); i++) {
        printf("%d ", reponse[i]);
    }
    printf("\n");
    char string_parser[5];
    strcpy(string_parser, "\r\n\r\n");
    // TODO : parser la reponse du serveur pour retourner un fichier contenant la donnée demandée
}
