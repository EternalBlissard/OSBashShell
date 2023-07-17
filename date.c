#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>

void main(int argc, char **argv) {
    int i=0;
    if(strcmp(argv[0],"date")==0){
        i=i+1;
    }else if(strcmp(argv[1],"date")==0){
        i=i+2;
    }
    else{
        printf("Invalid Command not supported");
        return;
    }
    int uflag=0;
    int rflag=0;
    time_t t = time(NULL);
    struct tm *local;
    
    if(argv[i] == NULL) {
        local = localtime(&t);
        printf("EDT %s", asctime(local));
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
            
            if(strcmp(argv[i],"-u")==0){
                uflag=1;
            }
            else if(strcmp(argv[i],"-r")==0){
                rflag=1;
            }
            else{
                printf("Command not Available/Supported\n");
                return;
            }
        }
    }
    if(uflag && !rflag){
        local = gmtime(&t);
        printf("UTC %s", asctime(local));
        return;
    }
    if(rflag && argv[i]==NULL){
        printf("-r requires a file arguement\n");
        return;
    }
    if(rflag && argv[i]!=NULL && argv[i+1]!=NULL){
        printf("Given Multiple Arguements to -r\n");
        return;
    }
    if(rflag && argv[i]!=NULL && argv[i+1]==NULL){
        struct stat stats;
        int flag=0;
        DIR *d = opendir(".");
        struct dirent *dir;
        int len = 0;
        char *arr[2048];
        dir=readdir(d);
        do {
            if((dir = readdir(d)) == NULL){
                break;
            }
            if(strcmp(dir->d_name,argv[i])==0) {
                flag=1;
                break;
            }
            arr[len] = dir->d_name;
            len++;
        }while(1);
        closedir(d);
        if(!flag){
            printf("File not Found\n");
            return;
        }else{
            stat(argv[i],&stats);
            if(!ctime(&stats.st_mtime)){
                printf("Unable to Trace Back Time Due to Improper types");
            }
            else{
            printf("Last Modificatication Time EDT %s",ctime(&stats.st_mtime));
            }
            return;
        }
    }
    
}        