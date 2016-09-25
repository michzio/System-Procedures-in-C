#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exec_cmd.h"

#define BUF_SIZE 128

char *exec_cmd(const char *cmd) {
    
    char buf[BUF_SIZE];
    char *result;
    FILE *pipe;
    
    result = malloc(sizeof(char)*BUF_SIZE);
    
    if((pipe = popen(cmd, "r")) == NULL) {
        fprintf(stderr, "popen: failed!\n");
        return NULL;
    }
    
    while(!feof(pipe)) {
        if(fgets(buf, BUF_SIZE, pipe) != NULL) {
            //printf("new len: %d vs old len: %d\n", strlen(result)+strlen(buf), strlen(buf));
            result = realloc(result, (strlen(result)+strlen(buf))* sizeof(char) );
            strcat(result, buf);
        }
    }
    
   if(pclose(pipe) < 0)  {
        printf("pclose: failed!\n");
        return NULL;
    }


    return result;
}