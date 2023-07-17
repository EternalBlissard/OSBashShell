#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <pthread.h>
#define maxSize 128*128
void *chaitanya(void *a){
    char **b=a;
    char result[maxSize] = { 0x0 };

    for (int i = 1; b[i]!=NULL; i++) {
        strcat(result, b[i]);
        strcat(result," ");
    }
    printf("%s \n",result);
    system(result);
    pthread_exit(NULL);
    return NULL;
}
void *ls(void *a){
    char **b=a;
    char result[maxSize] = { 0x0 };
    strcat(result,"./ls");
    for (int i = 0; b[i]!=NULL && strcmp(b[i],"&t")!=0; i++) {
        strcat(result," ");
        strcat(result, b[i]);
        
    }
    //printf("%s \n",result);
    system(result);
    pthread_exit(NULL);
    return NULL;
}
void *rm(void *a){
    char **b=a;
    char result[maxSize] = { 0x0 };
    strcat(result,"./rm");
    for (int i = 0; b[i]!=NULL && strcmp(b[i],"&t")!=0; i++) {
        strcat(result," ");
        strcat(result, b[i]);
        
    }
    //printf("%s \n",result);
    system(result);
    pthread_exit(NULL);
    return NULL;
}
void *mkdir(void *a){
    char **b=a;
    char result[maxSize] = { 0x0 };
    strcat(result,"./mkdir");
    for (int i = 0; b[i]!=NULL && strcmp(b[i],"&t")!=0; i++) {
        strcat(result," ");
        strcat(result, b[i]);
    }
    system(result);
    pthread_exit(NULL);
    return NULL;
}
void *cat(void *a){
    char **b=a;
    char result[maxSize] = { 0x0 };
    strcat(result,"./cat");
    for (int i = 0; b[i]!=NULL && strcmp(b[i],"&t")!=0; i++) {
        strcat(result," ");
        strcat(result, b[i]);
    }
    system(result);
    pthread_exit(NULL);
    return NULL;
}
void *date(void *a){
    char **b=a;
    char result[maxSize] = { 0x0 };
    strcat(result,"./date");
    for (int i = 0; b[i]!=NULL && strcmp(b[i],"&t")!=0; i++) {
        strcat(result," ");
        strcat(result, b[i]);   
    }
    system(result);
    pthread_exit(NULL);
    return NULL;
}

void Stringswapper(char **a,char**b){
    char *temp=*a;
    *a=*b;
    *b=temp;
}
char *line_read(){
    char* input=malloc(sizeof(char)*2048);
    fgets(input,2048,stdin);
    return input;
}
char **line_split(char *line){
    char **args = malloc(sizeof(char*)*2048);
    char *arg=strtok(line," \n\t\a");
    int i=0;
    while(arg!=NULL){
        args[i]=arg;
        arg=strtok(NULL," ");
        //printf("%s\n",args[i]);
        i++;
    }
    args[i]=NULL;
    return args;
}
int list_dir(){
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
            if ( strcasecmp(arr[y - 1], arr[y]) > 0 ) {
                Stringswapper(&arr[y],&arr[y-1]);
            }
        }
    }
    int indx;
    if(arr[0]==NULL){
            return 1;
        }
    else{    
        for( indx = 0 ; arr[indx] != NULL ; indx++ ) {
            printf("%s  ", arr[indx]);
        }
    }
    closedir(d);
    return 0;
}
void echoer(char ** argv){
    int _flag = 0;
    int nflag = 0;
    int emptflag=0;
    int i=0;
    if(strcmp(argv[0],"echo")==0){
        i=i+1;
    }else{
        printf("Invalid Command not supported");
        return;
    }
    if (argv[i][strlen(argv[i])-1] == '\n') 
        {
            argv[i][strlen(argv[i])-1] = 0;
        }
    if(!argv[i]){
        printf("\n");
        return;
    }
    else if (strcmp(argv[i],"-n")==0 && argv[i+1] == NULL){
        return;
    }
    else{
        for(i;argv[i]!=NULL ;i++){
            if (argv[i][strlen(argv[i])-1] == '\n') 
            {
                argv[i][strlen(argv[i])-1] = 0;
            }
            if(strcmp(argv[i],"-n")==0){
                nflag=1;
                if(_flag){
                    printf("%s  ",argv[i]);
                }
            }
            else if(strcmp(argv[i],"*")==0){
                _flag=1;
                if(emptflag){
                    printf("%s  ",argv[i]);
                }
                int dirflag=list_dir();
                if(dirflag){
                    emptflag=1;
                    if(argv[i+1]==NULL){
                        printf("*\n");
                        return;
                    }
                }
            }
            
            else{
                    printf("%s ",argv[i]);
                }
            }
            printf("\n");
            return;
        }
    }    
void cdchanger(char ** argv){
    char s[100];
    if (argv[1]!=NULL && argv[1][strlen(argv[1])-1] == '\n') 
        {
            argv[1][strlen(argv[1])-1] = 0;
        }
    if(argv[1]!=NULL && argv[2]!=NULL){
        printf("More Aguements than necessary");
        return;
    }
    if(argv[1]==NULL){
        chdir("/home/kali");
    }else if(strcmp(argv[1],"~")==0){
        chdir("/home/kali");
    }else if(strcmp(argv[1],"..")==0){
        chdir("..");
    }else {
        if (chdir(argv[1]) != 0){
        perror("chdir() to failed");  
        return ;}
    }
    return;
}
void pwdgiver(char ** argv){
    int Pflag = 0;
    int Lflag = 0;
    int i=0;
    if(strcmp(argv[0],"pwd")==0){
        i=i+1;
    }else{
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
            
            if(strcmp(argv[i],"-P")==0){
                Pflag=1;
            }
            else if(strcmp(argv[i],"-L")==0){
                Lflag=1;
            }
            else{
                printf("Command not Available/Supported\n");
                return;
            }
        }
    }

    if(!argv[i]){
        char s[512];
        printf("%s\n",getcwd(s,512));
    }else{
        printf("pwd: Too Many Arguements");
        return;
    }
}
void Pexecutor(char ** args){
    if(strcmp(args[0],"ls")==0){
        pthread_t pid;
        pthread_create(&pid,NULL,&ls,args);
        pthread_join(pid,NULL);
        return ;
    }else if(strcmp(args[0],"date")==0){
        pthread_t pid;
        pthread_create(&pid,NULL,&date,args);
        pthread_join(pid,NULL);
        return ;
    }else if(strcmp(args[0],"cat")==0){
        pthread_t pid;
        pthread_create(&pid,NULL,&cat,args);
        pthread_join(pid,NULL);
        return ;
    }else if(strcmp(args[0],"rm")==0){
        pthread_t pid;
        pthread_create(&pid,NULL,&rm,args);
        pthread_join(pid,NULL);
        return ;
    }else if(strcmp(args[0],"mkdir")==0){
        pthread_t pid;
        pthread_create(&pid,NULL,&mkdir,args);
        pthread_join(pid,NULL);
        return; 
    }else{
        printf("%s :Command not found",args[0]);
    }
}
void executor(char ** args){
    if(strcmp(args[0],"ls")==0){
        int pid=fork();
        if(pid==-1){printf("Forking failed");}
        if(pid==0){
        execvp("./ls",args++);
        }else{
            wait(NULL);
        }
    }else if(strcmp(args[0],"date")==0){
        int pid=fork();
        if(pid==-1){printf("Forking failed");}
        if(pid==0){
        execvp("./date",args++);
        }else{
            wait(NULL);
        }
    }else if(strcmp(args[0],"cat")==0){
        int pid=fork();
        if(pid==-1){printf("Forking failed");}
        if(pid==0){
        execvp("./cat",args++);
        }else{
            wait(NULL);
        }
    }else if(strcmp(args[0],"rm")==0){
        int pid=fork();
        if(pid==-1){printf("Forking failed");}
        if(pid==0){
        execvp("./rm",args++);
        }else{
            wait(NULL);
        }
    }else if(strcmp(args[0],"mkdir")==0){
        int pid=fork();
        if(pid==-1){printf("Forking failed");}
        if(pid==0){
        execvp("./mkdir",args++);
        }else{
            wait(NULL);
        }
    }else if(strcmp(args[0],"cd")==0){
        cdchanger(args);
    }else if(strcmp(args[0],"pwd")==0){
        pwdgiver(args);
    }else if(strcmp(args[0],"echo")==0){
        echoer(args);
    }
    else{
        printf("%s : command not found\n",args[0]);
    }
}
int main(int argc,char **argv){
    char* inputline;
    char **args;
    while(1){
        printf(">");
        inputline=line_read();
        args=line_split(inputline);
        //printf("%s",args[0]);
        if(args[0]!=NULL){
            int flag=0;
            int i=0;
            for(;args[i]!=NULL;i++){
                if (args[i][strlen(args[i])-1] == '\n') {
                    args[i][strlen(args[i])-1] = 0;
                }
                if(strcmp(args[i],"&t")==0 && args[i+1]==NULL){
                    flag=1;
                }
            }
            if(!flag){
                executor(args);
            }else{
                Pexecutor(args);
                //printf("&t found");
            }
        }
        
        
    }
    return 0;
}
