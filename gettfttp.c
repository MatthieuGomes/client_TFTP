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
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_DGRAM;
    hints.ai_protocol=IPPROTO_UDP;
    struct addrinfo *res;
    int error_address = getaddrinfo(host,port,&hints,&res);
    char serv_address[50]= "";
    if(error_address==0){
		printf("Le serveur à bien été trouvé\n");
		inet_ntop(AF_INET, &res->ai_addr->sa_data[2], serv_address, sizeof(serv_address));
		printf("L\'adresse du serveur est : %s \n",serv_address); // On affiche l'adresse du serveur hôte
	}
	else{
		printf("Erreur lors de la recherche du serveur : %s\n",gai_strerror(error_address));
		return 0;
	}
    int sock=0;
    // Ici, on test si le socket est bien reservé en testant si le numéro qui lui est attribué est bien surpérieur à 0
    if((sock=socket (AF_INET , SOCK_DGRAM, IPPROTO_UDP))<0){
		perror("socket error");
		return 0;
	}
	else{
		printf("Le socket à bien été réservé et son descripteur est : %d\n",sock);
	}
	int opcode =1;
	char* mode="octet";
	struct sockaddr_in to;
	to.sin_family= AF_INET;
	inet_aton(serv_address,&to.sin_addr);
	to.sin_port = htons(69);
	int size=2+strlen(file)+1+strlen(mode)+1;
	char *p;
	char request[size];
	*(short*) request=htons(1);
	p=request+2;
	strcpy(p,file);
	p+=strlen(file)+1;
	strcpy(p,mode);
	p+=strlen(mode)+1;
	int error_req=sendto(sock,request,p-request,0,(struct sockaddr*)&to,sizeof(to));
	printf("Le code d'erreur vaut = %s\n",gai_strerror(error_req));
	char* recv_buffer[256];
	struct sockaddr from;
}