/* Codi solucio de la practica: SERVIDOR */

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

#define MIDA_BUFFER 1024
#define MIDA_MAX_NOMBRE 2

unsigned short tracta_parametres(char buffer[]);

unsigned short tracta_parametres(char buffer[]){
    unsigned char aux;
    int i,j;
    if (strstr(buffer, " ") == NULL || strstr(buffer, "\0") == NULL) { // ha de contanir espai
        printf("Format incorrecte");
        return (-1);
    }
    char *nombres = strtok(buffer, " "); //split string, using " " separator
    char* nombre_1 = nombres;
    char* nombre_2 = strtok(NULL, " ");
    char param1 = atoi(nombre_1);
    char param2 = atoi(nombre_2);
    if (param1 >= 0 && param1 <= 99 && param2 >= 0 && param2 <= 99 ){
        unsigned short multiplication_result = param1*param2; 
        return multiplication_result;
    }
    else{
        printf("Parametres incorrectes!");
    } 
    return -1;
}

int main(){
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in serv_adr, client_adr;
    char buffer_send[MIDA_BUFFER], buffer[MIDA_BUFFER];
    socklen_t mida;
    int n, i;
    
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);

    /* Posem les dades del socket */
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port = htons(44444);

    /* Enllacem el socket */
    n = bind(s, (struct sockaddr*)&serv_adr, sizeof(serv_adr)); // if successful returns 0 if not -1

    if (n < 0)
    {
        printf("No s'ha pogut enllacar el socket\n");
    }
    else
    {
        printf("Servidor operatiu!\n");
        /* Servidor operatiu! */
        while(1){
            n = recvfrom(s, buffer, 1024, 0, (struct sockaddr*)&client_adr, &mida);
            if (n == -1){
                perror("Error when receiving data!");
                close(s);
                return (-1);
            }
            unsigned short multiplication = tracta_parametres(buffer);
            sprintf(buffer_send, "%d", multiplication);
            sendto(s, buffer_send, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, sizeof(client_adr));
        }
    }
    /* Tanquem el socket */
    close(s);
    return 0;
}