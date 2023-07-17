#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int isDir(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

void main(int argc, char **argv) {
    int dflag = 0;
    int fflag = 0;
    int i=0;
    if(strcmp(argv[0],"rm")==0){
        i=i+1;
    }else if(strcmp(argv[1],"rm")==0){
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
            
            if(strcmp(argv[i],"-d")==0){
                dflag=1;
            }
            else if(strcmp(argv[i],"-f")==0){
                fflag=1;
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
    if(!fflag && !dflag){
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
                printf("No Such File OR Directory\n");
                return;
            }
            else if(errno==20){
                FILE *f = fopen(argv[i], "r");
                remove(argv[i]);
                fclose(f);
            }
            
            }
            else{
                printf("%s is a Directory\n",argv[i]);
                return;
            }
        }   
    }
    else if(fflag && !dflag){
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
                continue;
            }
            else if(errno==20){
                FILE *f = fopen(argv[i], "r");
                remove(argv[i]);
                fclose(f);
            }
            
            }
            else{
                printf("%s is a Directory\n",argv[i]);
                continue;
            }
        }
    }else if(!fflag && dflag){
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
                printf("No Such File OR Directory\n");
                return;
            }
            else if(errno==20){
                FILE *f = fopen(argv[i], "r");
                remove(argv[i]);
                fclose(f);
            }
            
            }
            else{
                //printf("%s is a Directory\n",argv[i]);
                int dirflag=rmdir(argv[i]);
                if(dirflag==-1){
                    printf("Directory %s is not Empty\n",argv[i]);
                    return;
                }
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
                continue;   
            }
            else if(errno==20){
                FILE *f = fopen(argv[i], "r");
                remove(argv[i]);
                fclose(f);
            }
            
            }
            else{
                int dirflag=rmdir(argv[i]);
                if(dirflag==-1){
                    
                    printf("Directory %s is not Empty\n",argv[i]);
                    continue;
                }
            }
        }
    }
    return; 
}      
