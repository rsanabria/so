#include"cabecera.h"
#include"finder.h"

char *q1, *queryNombre,*queryPermisos,*queryTipos, *queryUsaurio ;
char *b1, *banderaNombre,*banderaPermisos,*banderaTipos, *banderaUsuario = NULL;
int  multiplesArgumentos;
struct stat buffer;

int main(int argc, char *argv[]){
	
	if (argc <4)
		printf("finder [ruta] [bandera] [valor], ...\n");
	else if (argc ==4)	{
		multiplesArgumentos = 0; //false
		b1 = argv[2];
		q1 = argv[3];
		ftw(argv[1],callbackUno,1);
	}
	else {
		multiplesArgumentos = 1; // true
		prepararArgumentos(argc,argv);
		ftw(argv[1],callbackDos,1);
	}
	
	}




















