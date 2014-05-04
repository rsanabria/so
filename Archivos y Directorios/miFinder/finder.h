extern char  *queryNombre,*queryPermisos,*queryTipos, *queryUsuario, *queryExec[1024] ;
extern char *banderaNombre,*banderaExec;
extern int argumentosExec;
struct stat buffer;


int prepararArgumentos(int numeroArgumentos, char *argumentos[]){
	int i,j, k =0;
	
	for (i = 2; i<numeroArgumentos;i++){
		if ( !strcmp(argumentos[i],"-nombre")){
			banderaNombre = argumentos[i];
			queryNombre   = argumentos[i+1];
		}	
		else if ( !strcmp(argumentos[i],"-permisos")){
			//banderaPermisos = argumentos[i];
			queryPermisos   = argumentos[i+1];
		}
		else if ( !strcmp(argumentos[i],"-tipo")){
			//banderaTipos = argumentos[i];
			queryTipos   = argumentos[i+1];
		}
		else if (!strcmp(argumentos[i], "-usuario")){
			//banderaUsuario = argumentos[i];
			queryUsuario   = argumentos[i+1];
		}
		else if (!strcmp(argumentos[i], "-exec")){
			for(j = i+1;j<numeroArgumentos;j++){
				queryExec[k] = argumentos[j];
				k++;
				argumentosExec = k;
			}
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

void exec(const char * path,char *query[]){
		if(query[0]){
		query[argumentosExec] = (char *)path;
		    if(fork() == 0)	
				execvp(query[0],query);
			else {
				wait(0);
				}
		}
		else{
			miStat(path);
					
			}
			
}
	
void analizarPerm(const char * path, const char * query){
	if(query){
		int statchmod = buffer.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
		char permisos[15];
		sprintf(permisos, "%04o", statchmod);
		if (!strcmp(permisos,query)){
			exec(path, queryExec);
		}
	}
	else
		exec(path,queryExec);
}
void analizarUsuario(const char * path, const char *query){
	if (query){
		
		struct passwd *pwd = getpwuid(buffer.st_uid);
		if(!strcmp(pwd->pw_name,query)){
			analizarPerm(path,queryPermisos);
		}
	
	}
	else
		analizarPerm(path, queryPermisos);
	
}
void analizarDir(const char * path, const char * query){
	

				if(query){
					if(!strcmp(query,"dir")){ 
						if (S_ISDIR(buffer.st_mode)){
							
							analizarUsuario(path,queryUsuario);
						}
					}
					else if (!strcmp(query,"reg")){ 
						
						if (S_ISREG(buffer.st_mode))
							analizarUsuario(path,queryUsuario);
					}
					
	
				}
				else{
					analizarUsuario(path,queryUsuario); // si no hay queryTipos ve con la siguiente opcion Usuario
			    }

				
			 
}

int buscarArchivo(const char * path){
	if(stat(path,&buffer)< 0)  {  
		printf("%s\n",path);
        return 1;
    }
	analizarDir(path,queryTipos);	
	return 0;
}

void busquedaNombre(const char *path, char * query){
	DIR *dir;
	struct dirent *mi_dir;
	dir = opendir(path);
	char ruta[1024];   
	while(( mi_dir = readdir(dir)) != NULL){
		if(strcmp(mi_dir->d_name,"." ) && strcmp(mi_dir->d_name,"..")){
			strcpy(ruta, path);
            strcat(ruta, "/");
            strcat(ruta, mi_dir->d_name);
			if(query){
				if(!strcmp(mi_dir->d_name,query)){
					buscarArchivo(ruta);
				}
			}
			else
				buscarArchivo(ruta);
					
		}
	}
    
	closedir(dir);
}

	
int callbackDos(const char *nombre, const struct stat *status, int type){
	
	if(type == FTW_NS)
	   return 0;
	 if (type == FTW_D){
		 if (banderaNombre)
			busquedaNombre(nombre,queryNombre);
		else
			busquedaNombre(nombre,NULL);
	 }
	return 0;
	}
