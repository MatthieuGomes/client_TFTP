#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
    if(argc<3){
		printf("Il manque un ou plusieurs arguments");
		return 0;
	}
    char* host = argv[1];
    char* file = argv[2];
    char* port = "69";
    printf("Le nom de l\'hote est : %s\n", host); // Le nom du fichier est ... 
    printf("Le nom du fichier est : %s\n", file); // Le nom de l'hote est ...
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    struct addrinfo *res;
    int error = getaddrinfo(host,port,&hints,&res);
    char serv_adress[50]= "";
    if(error==0){
		printf("Le serveur à bien été trouvé\n");
		inet_ntop(AF_INET, &res->ai_addr->sa_data[2], serv_adress, sizeof(serv_adress));
		printf("L\'adresse du serveur est : %s \n",serv_adress); // On affiche l'adresse du serveur hôte
	}
	else{
		printf("Erreur lors de la recherche du serveur : %s\n",gai_strerror(error));
		return 0;
	}
    int sock;
    if((sock=socket (AF_INET , SOCK_DGRAM, IPPROTO_UDP))<0){
		perror("socket error");
		return 0;
	}
	else{
		printf("Le socket à bien été réservé et son descripteur est : %d\n",sock);
	}
	struct sockaddr *dest_connect_data={port,serv_adress}; // On créé ici la structure qui stock les information concernant la destination
	char *RRQ="";
	int error_sendrequest = sendto(sock,RRQ, sizeof(RRQ),MSG_OOB,dest_connect_data,sizeof(dest_connect_data));
	printf("première requete envoyée, erreur retournée :%s",gai_strerror(error_sendrequest));
	
}
