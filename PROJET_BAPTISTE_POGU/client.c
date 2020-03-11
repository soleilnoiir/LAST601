#include "client.h"


int main(int argc, char *argv[]){

    int sockfd;
    struct sockaddr_in adresseServeur;
    char msg[256];

    /* Récupération des arguments */
    if (argc != 2){
        fprintf(stderr,"IP\n");
        fprintf(stderr,"port\n");
        exit(EXIT_FAILURE);
    }

    /* Création de la socket */
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Erreur lors de la création de la socket ");
        exit(EXIT_FAILURE);
    }

    /* Création de l'adresse du serveur */
    memset(&adresseServeur, 0, sizeof(struct sockaddr_in));
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(atoi(argv[2]));
    if(inet_pton(AF_INET, argv[1], &adresseServeur.sin_addr) != 1) {
        perror("Erreur lors de la conversion de l'adresse ");
        exit(EXIT_FAILURE);
    }
    memset(msg, 0, 256);
    strcpy(msg, "coucou");

    /* Envoi du message */
    if(sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr*)&adresseServeur, sizeof(struct sockaddr_in)) == -1) {
    perror("Erreur lors de l'envoi du message ");
    exit(EXIT_FAILURE);
    }
    printf("Client : message envoyé.\n");

    /* Fermeture de la socket */
    if(close(sockfd) == -1) {
    perror("Erreur lors de la fermeture de la socket ");
    exit(EXIT_FAILURE);
  }
