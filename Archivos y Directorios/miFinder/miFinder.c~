#include"cabecera.h"
#include"finder.h"

char *q1, *queryNombre,*queryPermisos,*queryTipos, *queryUsuario,  *queryExec[1024] ; 
char *b1, *banderaNombre,*banderaPermisos,*banderaTipos, *banderaUsuario = NULL;
int  argumentosExec;
struct stat buffer;

int main(int argc, char *argv[]){
	
	if (argc <4)
		printf("finder [ruta] [bandera] [valor], ...\n");
	else {
		prepararArgumentos(argc,argv);
		ftw(argv[1],callbackDos,1);
	}
	
	}
