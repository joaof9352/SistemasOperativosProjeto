#ifndef __AURRASD__
#define __AURRASD__

typedef struct sFilter{
    char* nome;
    char* path;
    int running;
    int max;
} *FILTER;

typedef struct sFilters{
    FILTER* filters;
    int atual;
    int max;
} *FILTERS;


#endif