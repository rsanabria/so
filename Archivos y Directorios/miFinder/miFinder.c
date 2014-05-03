#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>
#include<ftw.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include <pwd.h>
#include <grp.h>
#include<string.h>

char *query;
struct stat buffer;

int archivo(const char * path){

char tiempo[100],bufferTiempo[100];
        if(stat(path,&buffer)< 0)  {  
            printf("%s\n",path);
        return 1;
        }

struct passwd *pwd = getpwuid(buffer.st_uid);
struct group *gr = getgrgid(buffer.st_gid);

strftime (bufferTiempo, 100, "%d.%m.%Y %H:%M ", localtime(&buffer.st_mtime)); 
 
    printf( (S_ISDIR(buffer.st_mode)) ? "d" : "-");
    printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
    printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
    printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
    printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
    printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
    printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
    printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
    printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
    printf( (buffer.st_mode & S_IXOTH) ? "x " : "- ");
    
    printf("%d ",buffer.st_nlink);
    
    printf("%s ", pwd->pw_name);
    printf("%s ", gr->gr_name);
        
     printf("%d ",buffer.st_size);
 
    printf("%s",bufferTiempo);
   printf("%s\n",path);
    return 0;
}
void directorio(const char *path){
    
DIR *dir;
struct dirent *mi_dir;
dir = opendir(path);
char ruta[1024];   
while(( mi_dir = readdir(dir)) != NULL){
   if(strcmp(mi_dir->d_name,"." ) && strcmp(mi_dir->d_name,".."))  {
        if(!strcmp(query,"*"))
            query = mi_dir->d_name;
        if(!strcmp(mi_dir->d_name,query)){
                strcpy(ruta, path);
                strcat(ruta, "/");
                strcat(ruta, mi_dir->d_name);
                archivo(ruta);
        }
}
}
    
closedir(dir);
}


int main (int argc, char *argv[]){

int callback (const char *, const struct stat *, int);
if (argv[2])
    query = argv[2];
else
    query = "*";
if(argc == 1)
  ftw(".",callback,100);
else
 ftw(argv[1],callback,1);
return 0;

}

int callback(const char *nombre, const struct stat *status, int type){

if(type == FTW_NS)
   return 0;
if (type == FTW_D)
    directorio(nombre);

return 0;
}





















