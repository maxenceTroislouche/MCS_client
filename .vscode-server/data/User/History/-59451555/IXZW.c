#include "streamInc.h"

#define HIHI "Hihi"
#define PW "pw"
#define ABORT "ABORT"

void dialogueSrv(int sd, struct sockaddr_in *srv);

int main()
{
    int sock;
    struct sockaddr_in svc;
    struct sockaddr_in sock_info;
    socklen_t infoLen = sizeof(struct sockaddr);
    CHECK(sock = socket(PF_INET, SOCK_STREAM, 0), "Can't create socket");
    svc.sin_family = PF_INET;
    svc.sin_port = htons(PORT_SVC);
    svc.sin_addr.s_addr = inet_addr(INADDR_SVC);
    memset(&svc.sin_zero, 0, 8);

    CHECK(connect(sock, (struct sockaddr *)&svc, sizeof svc), "Can't connect"); // Dialogue avec le serveur
    CHECK(getsockname(sock, (struct sockaddr *)&sock_info, &infoLen), "Can't get sock name");
    printf("Server listening on %s, port %d\n", inet_ntop(AF_INET, &sock_info.sin_addr, buffer, sizeof(buffer)), ntohs(sock_info.sin_port));
    getpeername(sock, (struct sockaddr *)&sock_info, &infoLen);
    printf("Connected to server %s on port %d\n", inet_ntop(AF_INET, &sock_info.sin_addr, buffer, sizeof(buffer)), ntohs(sock_info.sin_port));
    dialogueSrv(sock, &svc);
    close(sock);

    return 0;
}

void dialogueSrv(int sd, struct sockaddr_in *srv)
{
    // On envoie Hihi
    printf("On envoie Hihi\n");
    write(sd, HIHI, sizeof(HIHI));

    // On lit la réponse, si ABORT alors bruh
    char buffer[MAX_BUFF];

    printf("On attend la réponse du serveur\n");

    read(sd, buffer, MAX_BUFF);

    printf("Reponse du serveur : %s\n", buffer);

    if (strcmp(buffer, PW) != 0)
    {
        printf("Le Hihi a échoué !\n");
        return;
    }
    // Sinon si pw
    // On demande à l'utilisateur un username et un pw
    char username[101];
    char password[101];

    printf("Quel est votre username ?\n");
    fgets(username, 100, stdin);
    printf("Votre username est %s\n", username);

    // On retire le \n en trop
    username[strlen(username) - 1] = '\0';

    printf("Quel est votre password ?\n");
    fgets(password, 100, stdin);
    printf("Votre password est %s\n", password);

    // On retire le \n en trop
    password[strlen(password) - 1] = '\0';

    strcpy(buffer, username);
    strcat(buffer, ":");
    strcat(buffer, password);

    printf("La chaine concaténée est <%s>\n", buffer);

    // On envoie les infos au serveur
    write(sd, buffer, MAX_BUFF);

    // On lit la réponse
    read(sd, buffer, MAX_BUFF);

    printf("Réponse du serveur : %s\n", buffer);

    // Si ABORT on quitte
    if (strcmp(buffer, OK) != 0)
    {
        printf("L'authentification a échoué !\n");
        return;
    }

    // Si OK on lit le fichier
    printf("Authentification réussie !\n");

    // Création du fichier
    FILE *fichier = NULL;
    fichier = fopen("reponse_serveur.txt", "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de la création du fichier !\n");
        return;
    }
    printf("Lecture des données du fichier\n");
    // Copie des données dans le fichier
    char response[MAX_BUFF];
    while (1)
    {
        read(sd, response, MAX_BUFF);
        printf("Lu : %s\n", buffer);
        if (strcmp(buffer, STOP) == 0)
        {
            break;
        }

        fputs(buffer, fichier);
    }

    fclose(fichier);

    printf("Réception réussie !\n");

    // Fin
}