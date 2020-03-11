#include "serveur.h"

int main(int argc, char *argv[]){

    int sockfd;
    struct sockaddr_in adresseServeurUDP;
    char msg[256];

    /* Récupération des arguments */
    if (argc != 4){
        fprintf(stderr,"IP\n");
        fprintf(stderr,"port\n");
        fprintf(stderr,"HAUTEUR\n"); 
        fprintf(stderr,"LARGEUR\n");
        exit(EXIT_FAILURE);
    }

    /* Création de la socket */
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Erreur lors de la création de la socket ");
        exit(EXIT_FAILURE);
    }

    /* Création de l'adresse du serveur */
    memset(&adresseServeurUDP, 0, sizeof(struct sockaddr_in));
    adresseServeurUDP.sin_family = AF_INET;
    adresseServeurUDP.sin_port = htons(atoi(argv[1]));
    adresseServeurUDP.sin_addr.s_addr = htonl(argv[0]);
    
    /* Nommage de la socket */
    if(bind(sockfd, (struct sockaddr*)&adresseServeurUDP, sizeof(struct sockaddr_in)) == -1) {
        perror("Erreur lors du nommage de la socket ");
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente du message du client.\n");

    while(1){
        
    /* Attente de la requête du client */
        if(recvfrom(sockfd, &msg, sizeof(msg), 0, NULL, NULL) == -1) {
            perror("Erreur lors de la réception du message ");
            exit(EXIT_FAILURE);
        }
    }

    /* Fermeture de la socket UDP */
    if(close(sockfd) == -1) {
        perror("Erreur lors de la fermeture de la socket ");
        exit(EXIT_FAILURE);
    }

    printf("Serveur terminé.\n");
  
    return EXIT_SUCCESS;

}