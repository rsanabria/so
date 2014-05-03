extern char *q1,*q2,*q3;
extern char *b1,*b2,*b3;
struct stat buffer;


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

int buscarArchivo(const char * path,char * query){

        if(stat(path,&buffer)< 0)  {  
            printf("%s\n",path);
        return 1;
        }
		if(query){		
		if(!strcmp(query,"dir")){ 
			if (S_ISDIR(buffer.st_mode))
				miStat(path);
		}
		else if (!strcmp(query,"reg")){ 
			if (S_ISREG(buffer.st_mode))
				miStat(path);
	}
}
	else
		miStat(path);
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


void busquedaTipo(const char *path, char * query){    
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
		   
		   busquedaTipo(nombre,q1);
		}
		else if(!strcmp(b1,"-permisos")){
		   //busquedaPermisos(nombre,q1);		
		}   
	   
	   
	 }
	return 0;
	}
	
