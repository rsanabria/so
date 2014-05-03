#include"cabecera.h"
#include"finder.h"

char *query;
struct stat buffer;

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





















