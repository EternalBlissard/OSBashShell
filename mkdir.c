#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

void main(int argc, char **argv) {
    int pflag = 0;
    int vflag = 0;
    int i=0;
    if(strcmp(argv[0],"mkdir")==0){
        i=i+1;
    }else if(strcmp(argv[1],"mkdir")==0){
        i=i+2;
    }
    else{
        printf("Invalid Command not supported\n");
        return;
    }
    for(i;argv[i]!=NULL ;i++){
        if (argv[i][strlen(argv[i])-1] == '\n') 
        {
            argv[i][strlen(argv[i])-1] = 0;
        }
        if(argv[i][0]!='-'){
            break;
        }else{
            
            if(strcmp(argv[i],"-p")==0){
                pflag=1;
            }
            else if(strcmp(argv[i],"-v")==0){
                vflag=1;
            }
            else{
                printf("Command not Available/Supported\n");
                return;
            }
        }
    }
    if(argv[i]==NULL){
        printf("Insufficient Arguements Given\n");
        return;
    }
    if(!pflag){
        for(;argv[i]!=NULL;i++){
            if (argv[i][strlen(argv[i])-1] == '\n') 
            {
                argv[i][strlen(argv[i])-1] = 0;
            }
            DIR *dir;
            struct dirent *dp;
            if ((dir = opendir (argv[i])) == NULL) {
                int errnum=errno; 
                if(errno==2){
                    struct stat st = {0};
                    if (stat(argv[i], &st) == -1) {
                        if(mkdir(argv[i], 0777) != 0) {
                            printf("Failed to Created %s\n",argv[i]);
                            continue;
                        }
                        if(!vflag){
                            continue;
                        }else{
                            printf("Successfully Created directory : %s\n", argv[i]);
                        }
                    }else{
                        printf("Failed to Create the %s directory",argv[i]);
                    }
                }    
                else if(errno==20){
                    printf("%s: Cannot Create Dir File Already exists \n",argv[i]);
                    continue;
                }
            }
            else{
                printf("%s: Directory Already exists \n",argv[i]);
                continue;
            }
        }
    }else{
        for(;argv[i]!=NULL;i++){
            if (argv[i][strlen(argv[i])-1] == '\n') 
            {
                argv[i][strlen(argv[i])-1] = 0;
            }
            DIR *dir;
            struct dirent *dp;
            if ((dir = opendir (argv[i])) == NULL) {
                int errnum=errno; 
                if(errno==2){
                    struct stat st = {0};
                    if (stat(argv[i], &st) == -1) {
                        char *p;
                        for(p = argv[i] + 1; *p; p++) {
                            if(*p == '/') {
                                *p = 0;
                                mkdir(argv[i], 0777);
                                *p = '/';
                            }
                            mkdir(argv[i], 0777);
                        }
                        if(!vflag){
                            continue;
                        }else{
                            printf("Successfully Created directory : %s\n", argv[i]);
                        }
                    }else{
                        printf("Failed to Create the %s directory",argv[i]);
                    }
                }    
                else if(errno==20){
                    printf("%s: Cannot Create Dir File Already exists \n",argv[i]);
                    continue;
                }
            }
            else{
                // printf("%s: Directory Already exists \n",argv[i]);
                continue;
            }
        }
    }
}