#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int bytes_read;
    char buf[100];
    int fd = open("client_server_fifo",O_RDONLY);
    while((bytes_read = read(fd,buf,100))>0){
        write(STDOUT_FILENO,buf,bytes_read);
    }
    return 0;
}