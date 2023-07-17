#include <stdio.h>
#include <string.h>

void main(int argc, char **argv) {
    int Eflag = 0;
    int nflag = 0;
    int i=0;
    if(strcmp(argv[0],"cat")==0){
        i=i+1;
    }else if(strcmp(argv[1],"cat")==0){
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
            
            if(strcmp(argv[i],"-E")==0){
                Eflag=1;
            }
            else if(strcmp(argv[i],"-n")==0){
                nflag=1;
            }
            else{
                printf("Command not Available/Supported");
                return;
            }
        }
    }
    if(argv[i] == NULL) {
        char line[2048];
        int ind = 0;
        do{
            ind=ind+1;
            fgets(line, 2048, stdin);
            if(nflag) {
                printf("%d ", ind++);
            }
            int line_len=strlen(line);
            if(line[line_len-1] == '\n') {
                line[line_len-1] = 0;
            }
            printf("%s", line);
            if(Eflag) {
                printf("$");
            }
            printf("\n");
        }
        while(1);
        return;
    }
    int ind = 0;
    for( ; argv[i] != NULL ; i++) {
        if (argv[i][strlen(argv[i])-1] == '\n') {
            argv[i][strlen(argv[i])-1] = 0;
        }
        FILE *f = fopen(argv[i], "r");
        if(!f) {
            printf("File does not exist.\n");
            return;
        }
        char line[2048];
        while (fgets(line, 2048, f) != NULL) {
            ind++;
            int line_len=strlen(line);
            if(!Eflag) {
                if(line[line_len-1]== '\n') {
                    line[line_len-1] = 0;
                }
            }
            else {
                if(line[line_len-1] == '\n') {
                    line[line_len-1] = '$';
                }
            }
            if(!nflag) {
                printf("%s\n", line);
            }
            else {
                printf("%d %s\n", ind,line);
            }
        }
        fclose(f);
    }
}