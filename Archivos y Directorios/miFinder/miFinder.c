#include"cabecera.h"
#include"finder.h"

char *q1,*q2,*q3;
char *b1,*b2,*b3;
struct stat buffer;

int main (int argc, char *argv[]){

  // int callbackUno (const char *, const struct stat *, int);
  if (argv[2])
    b1 = argv[2];
  else{
    b1 = "*";
    printf("necesitas usar una bandera");
  }
  if (argv[3])
    q1 = argv[3];
  else
    q1 = "*";
  if(argc == 1)
    printf("finder [path] [-bandera]\n");
  else{
    if (argc ==4)
      ftw(argv[1],callbackUno,1);
  }
  return 0;

}





















