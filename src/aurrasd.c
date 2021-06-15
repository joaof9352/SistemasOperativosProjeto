#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "aurrasd.h"

FILTER initFilter(char* id, char* path, int max){
    FILTER f = (FILTER) malloc(sizeof(struct sFilter));
    f->max = max;
    f->nome = strdup(id);
    f->path = strdup(path);
    f->running = 0;
    return f;
}

FILTERS initFilters(){
    FILTERS fs = (FILTERS) malloc(sizeof(struct sFilters));
    fs->filters = malloc(sizeof(FILTER) * 1);
    fs->atual = 0;
    fs->max = 1;
    return fs;
}

void addFilter(FILTERS fs, char* id, char* path, int max){
    if(fs->atual == fs->max){
        fs->max *= 2;
        printf("Aumentado para %d\n", fs->max);
        fs->filters = realloc(fs->filters,fs->max * sizeof(FILTER));
    }
    printf("Adicionado ao lugar %d\n", fs->atual);
    fs->filters[fs->atual++] = initFilter(id,path,max);
}

void printFilters(FILTERS fs){
    for(int i = 0; i < fs->atual; i++){
        printf("%s: %d/%d\n", fs->filters[i]->nome,fs->filters[i]->running,fs->filters[i]->max);
    }
}

// ./bin/aurrasd "/home/joao/Desktop/grupo-xx (Linux Intel)/etc/aurrasd.conf" aa
int main(int argc, char *argv[]){
    /* Função tem que ter 3 argumentos ./servidor config filtersFolder */
    if(argc != 3 ){
        char* str = "Argumentos inválidos\n";
        write(STDOUT_FILENO, str, strlen(str));
        exit(1);
    }

    /* Path para filters */
    char* filters_path = strdup(argv[2]);
    FILTERS fs = initFilters();
    
    /* Abrir e ler ficheiro de configuração dos filters */
    int fd_filters = open(argv[1],O_RDONLY);
    if(fd_filters == -1){
        perror("Configuration file");
        exit(1);
    }
    int i = 0;
    char* str;
    char *buf = malloc(sizeof(char) * 2048);
    read(fd_filters,buf,2048);
    while((str = strsep(&buf,"\n")) != NULL){
        printf("%d\n",i++);
        char* id = strsep(&str," ");
        char* path = strsep(&str, " ");
        int max = atoi(strsep(&str, " "));
        printf("%d\n",max);
        addFilter(fs, id, path, max);
    }
    printf("cona\n");
    //free(buf);
    printf("cona\n");
    printFilters(fs);


    return 0;
}