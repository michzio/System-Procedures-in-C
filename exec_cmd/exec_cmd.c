#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

char *exec_cmd(const char *cmd);

int main(void) {
    
    char *output;
    output = exec_cmd("echo 'Hello, world!' | nc localhost 2016 -w 1");
    
    printf("Output: %s\n", output); 
    
    free(output);
    return 0;
}

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