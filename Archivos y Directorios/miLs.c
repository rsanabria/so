#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#define BUFFER_SIZE 512
void archivo(struct stat buffer,const char * path){

char tiempo[100],bufferTiempo[100];

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
}
void directorio(const char *path,int x){
DIR *dir;
struct stat buffer;
struct dirent *mi_dir;
dir = opendir(path);
while(( mi_dir = readdir(dir)) != NULL)
   if(strcmp(mi_dir->d_name,"." ) && strcmp(mi_dir->d_name,".."))
   if(x){
     stat(mi_dir->d_name,&buffer);
     archivo(buffer,mi_dir->d_name);
}else
   printf("%s\n", mi_dir->d_name);

}
void ls(const char *path,const char *path2)
{
struct stat buffer;
stat(path,&buffer);
if((buffer.st_mode & S_IFREG) !=0)
   archivo(buffer, path);
else if(!strcmp(path,"-l"))
   directorio(path2, 1);
else
   directorio(path,0);
}

void main(int argc, char *argv[]){
if(argv[2])
   ls(argv[1],argv[2]);
else
   ls(argv[1],NULL);


}

