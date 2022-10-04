/* Codi solucio de la practica: CLIENT */

/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
socklen_t mida;

int main(int argc, char **argv){
 
    if (argc != 2) {
        printf("Us: %s IP\n", argv[0]);
        exit(0);
    }
    
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in adr;
    char buffer[1024], buffer_rcv[1024]; // i just wanna send X bytes
    int i;
    unsigned short num1, num2;

    printf("Introdueix numero 1\n");
    scanf("%hd", &num1);

    printf("Introdueix numero 2\n");
    scanf("%hd", &num2);

    sprintf(buffer, "%d %d", num1, num2);

    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);

    adr.sin_family = AF_INET;
    adr.sin_port = htons(44444);

    /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */
    adr.sin_addr.s_addr = inet_addr(argv[1]);

    sendto(s, buffer, sizeof(buffer), 0, (struct sockaddr*)&adr, sizeof(adr));
    int n = recvfrom(s, buffer_rcv, sizeof(buffer_rcv), 0, (struct sockaddr*)&adr, NULL);
    printf("%s\n",buffer_rcv);

    /* Tanquem el socket */
    close(s);
    return 0;
}
