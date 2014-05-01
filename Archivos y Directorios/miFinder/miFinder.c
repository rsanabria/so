#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
#include<sys/types.h>
#include<ftw.h>
#include<unistd.h>

int main (int argc, char *argv[]){

int dir (const char *, const struct stat *, int);

if(argc == 1)
  ftw(".",dir,10);
else
 ftw(argv[1],dir,10);
return 0;

}

int dir(const char *nombre, const struct stat *status, int type){

if(type == FTW_NS)
   return 0;
if (type == FTW_D)
 //printf((status->st_mode & S_IRUSR) ? "r\n" :"-\n");
 printf("%s\n",nombre);

return 0;
}





















