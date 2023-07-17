#include <stdio.h>
#include <dirent.h>
#include <string.h>
void Stringswapper(char **a,char**b){
    char *temp=*a;
    *a=*b;
    *b=temp;
}
void main(int argc, char **argv) {
    int mflag = 0;
    int rflag = 0;
    int i=0;
    if(strcmp(argv[0],"ls")==0){
        i=i+1;
    }else if(strcmp(argv[1],"ls")==0){
        i=i+2;
    }
    else{
        printf("Invalid Command not supported");
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
            
            if(strcmp(argv[i],"-m")==0){
                mflag=1;
            }
            else if(strcmp(argv[i],"-r")==0){
                rflag=1;
            }
            else{
                printf("Command not Available/Supported");
                //printf("%d",strcmp(argv[i],"-r")==0);
                return;
            }
        }
    }
    if(argv[i]==NULL){
        DIR *d = opendir(".");
        struct dirent *dir;
        int len = 0;
        char *arr[2048];
        dir=readdir(d);
        do {
            if((dir = readdir(d)) == NULL){
                break;
            }
            if(dir->d_name[0] == '.') {
                continue;
            }
            arr[len] = dir->d_name;
            len++;
        }while(1);
        int x, y;
        for (x = 1; x < len; x++) {
            for (y = 1; y < len; y++) {
                if (!rflag) {
                    if ( strcasecmp(arr[y - 1], arr[y]) > 0 ) {
                        Stringswapper(&arr[y],&arr[y-1]);
                    }
                }
                else {
                    if (strcasecmp(arr[y - 1], arr[y]) < 0) {
                        Stringswapper(&arr[y],&arr[y-1]);
                    }
                }
            }
        }
        int indx;
        if(arr[0]==NULL){
            return;
        }
        else if(!mflag){
        for( indx = 0 ; arr[indx] != NULL ; indx++ ) {
            printf("%s  ", arr[indx]);
        }
        printf("\n");
        }
        else{
            for( indx = 0 ; arr[indx] != NULL ; indx++ ) {
            if(arr[indx+1]==NULL){
                printf("%s  ", arr[indx]);
                continue;
            }
            printf("%s,  ", arr[indx]);
        }
        printf("\n");
        }
        
        closedir(d);
        }
    else{
        printf("Directories not Supported");
    }
}

