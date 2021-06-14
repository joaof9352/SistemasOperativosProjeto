#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#include "aurras.h"



int main(int argc, char const *argv[]) {

    int enviarString = 0;

    char string[MESSAGESIZE];
    string = "";
    if(argc == 1) {
        char* arr = "./aurras status\n";
        write(STDOUT_FILENO,arr,strlen(arr));
        char* arr2 = "./aurras transform input-filename output-filename filter-id-1 filter-id-2 ...\n"
        write(STDOUT_FILENO,arr2,strlen(arr2));
    } else {
        if(argv[1] == "status") {

            sprintf(string,"status");

        }else if(argv[1] == "transform"){
            if(argc < 5)
                exit(error("Argumentos inválidos"));
            
            for(int i = 1; i < argc; i++){
                sprintf(string,"%s %s",string,argv[i]);
            }
        }
    }

    if(enviarString){

            /* ENVIAR PEDIDO */
            int status;
            status = mkfifo(cliente_server_fifo,0666);
            if(status == -1 && errno != EEXIST)
                perror("Creating Client_Server_fifo");
            
            int client_server_fifo = open("client_server_fifo", O_WRONLY);
            if(client_server_fifo == -1)
                perror("Opening Client_Server_fifo");
            
            write(client_server_fifo, string, strlen(string));
            close(client_server_fifo);

            /* ESPERAR RESPOSTA */
            int bytesRead = 0;

            status = mkfifo(server_client_fifo,0666);
            if(status == -1 && errno != EEXIST)
                perror("Creating server_client_fifo");
            

            int server_client_fifo = open("server_client_fifo", O_RDONLY);
            if(server_client_fifo == -1)
                perror("Opening server_client_fifo");

            while((bytesRead = read(server_client_fifo, string, 1024)) > 0)
                write(STDOUT_FILENO, string, bytesRead);

            close(server_client_fifo);
    }

    return 0;
}

int error(char* str){
    write(STDOUT_FILENO, str, strlen(str));
    return 0;
}