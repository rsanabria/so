extern char *q1, *queryNombre,*queryPermisos,*queryTipos, *queryUsaurio ;
extern char *b1, *banderaNombre,*banderaPermisos,*banderaTipos, *banderaUsuario, *banderaExec;
extern int multiplesArgumentos;
struct stat buffer;


int prepararArgumentos(int numeroArgumentos, char *argumentos[]){
	int i;
	
	for (i = 2; i<numeroArgumentos;i++){
		if ( !strcmp(argumentos[i],"-nombre")){
			banderaNombre = argumentos[i];
			queryNombre   = argumentos[i+1];
		}	
		else if ( !strcmp(argumentos[i],"-permisos")){
			banderaPermisos = argumentos[i];
			queryPermisos   = argumentos[i+1];
		}
		else if ( !strcmp(argumentos[i],"-tipos")){
			banderaTipos = argumentos[i];
			queryTipos   = argumentos[i+1];
		}
	}
	return 0;
}

int miStat(const char *path){
	
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
   return 0;
	}


	
void analizarPerm(const char * path, const char * query){
			miStat(path);
			//if (buffer.st_mode&077777 == atoi(query)){
			////printf("%04o\n",buffer.st_mode&atoi(query));
			//miStat(path);
		//}
			//else{
				
				//printf("%d",atoi(query));
				//exit(1);
			//}
	}
void analizarDir(const char * path, const char * query){
	
			if(multiplesArgumentos)
				if(query != NULL){
					if(!strcmp(query,"dir")){ 
						if (S_ISDIR(buffer.st_mode))
							analizarPerm(path,queryPermisos);

					}
					else if (!strcmp(query,"reg")){ 
						if (S_ISREG(buffer.st_mode))
							analizarPerm(path,queryPermisos);

					}
	
				}
				else
					analizarPerm(path,queryPermisos); // si no hay queryTipos ve con la siguiente opcion Permisos
				else{
					if(!strcmp(query,"dir")){ 
						if (S_ISDIR(buffer.st_mode))
							miStat(path);
					}
					else if (!strcmp(query,"reg")){ 
						if (S_ISREG(buffer.st_mode))
							miStat(path);
					}
	
				}	
			 
}

int buscarArchivo(const char * path,char * query){

        if(stat(path,&buffer)< 0)  {  
            printf("%s\n",path);
        return 1;
        }
        if(multiplesArgumentos)
			analizarDir(path,queryTipos);
		else{
		if(query && (!strcmp(b1,"-tipo"))){
			analizarDir(path,query);		
		}
		else if (query && (!strcmp(b1,"-permisos")))
				analizarPerm(path,query);
	else{	
		miStat(path);
	}
}	
    return 0;
}

void busquedaNombre(const char *path, char * query){
    
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
                buscarArchivo(ruta,NULL);
        }
}
}
    
closedir(dir);
}


void busqueda(const char *path, char * query){    
DIR *dir;
struct dirent *mi_dir;
dir = opendir(path);
char ruta[1024];   
while(( mi_dir = readdir(dir)) != NULL){
   if(strcmp(mi_dir->d_name,"." ) && strcmp(mi_dir->d_name,".."))  {
        strcpy(ruta, path);
        strcat(ruta, "/");
        strcat(ruta, mi_dir->d_name);
        buscarArchivo(ruta,query);
        }
}

    
closedir(dir);
}

int callbackUno(const char *nombre, const struct stat *status, int type){
	
	if(type == FTW_NS)
	   return 0;
	 if (type == FTW_D){
	   if (!strcmp(b1,"-nombre")){
	     busquedaNombre(nombre,q1);
	   }
	   else if (!strcmp(b1,"-tipo")){
		   
		   busqueda(nombre,q1);
		}
		else if(!strcmp(b1,"-permisos")){
		   busqueda(nombre,q1);		
		}   
	   
	   
	 }
	return 0;
	}
	
int callbackDos(const char *nombre, const struct stat *status, int type){
	
	if(type == FTW_NS)
	   return 0;
	 if (type == FTW_D){
		 if (banderaNombre)
			busquedaNombre(nombre,queryNombre);
	 }
	return 0;
	}
