#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <fcntl.h>
#include <stdint.h>
#include <fstab.h>
struct	passwd	*pwent;	
struct	group	*grent;

int main (int argc, char *argv[])
{
        if (argc < 2)  {
                printf("Uso: %s archivo archivo2 archivo3 ...\n", argv[0]);
                exit(1);
        }
        struct stat buffer;
        int argumentos, estado;
        const char *archivo;
        archivo=(char*)(malloc(sizeof(char)));

        for (argumentos = 1; argumentos < argc; argumentos++)      {
                archivo = argv[argumentos];
                estado = stat(archivo, &buffer);
                if ( estado == -1 )       {
                        printf("Error fatal\n");
                        exit(1);
                }       else{
                        printf("   File: '%s'\n", archivo);
			printf("   Size: %jd\t\t", (intmax_t)buffer.st_size);
                        printf("Blocks: %d\t", buffer.st_blksize);
			printf("IO Block: %d\t", buffer.st_blocks);

			printf("");
				switch( buffer.st_mode & S_IFMT) {
				case	S_IFDIR:	
					printf("directory\n");
					break;
				case	S_IFCHR:	
					printf("character\n");
					break;
				case	S_IFBLK:	
					printf("block\n");
					break;
				case	S_IFREG:	
					printf("regular file\n");
					break;
				case	S_IFLNK:	
					printf("symbolic Link\n");
					break;
				case	S_IFSOCK:	
					printf("socket\n");
					break;
				case	S_IFIFO:	
					printf("fifo\n");
					break;
				default		:	
					printf("Unknown\n");
			}
                        printf("Device	: %d\t\t", buffer.st_dev);
			printf("Inode: %d\t", buffer.st_ino);
                        printf("Links: %d\n", buffer.st_nlink);
			 printf("Acces:(%04o/",buffer.st_mode&07777);
			switch( buffer.st_mode & S_IFMT) {
			case	S_IFDIR:	
				printf("d");
				break;
			case	S_IFCHR:	
				printf("c");
				break;
			case	S_IFBLK:	
				printf("b");
				break;
			case	S_IFREG:	
				printf("-");
				break;
		#ifndef SYSV
			case	S_IFLNK:	
				printf("l");
				break;
		#ifndef BSD2_9
			case	S_IFSOCK:	
				printf("s");
				break;
		#endif BSD2_9
		#else SYSV
			case	S_IFIFO:	
				printf("f");
				break;
		#endif SYSV
		#ifdef MASSCOMP
			case	S_IFCTG:	
				printf("c");
				break;
		#endif MASSCOMP
			default		:	
				printf("?");
			}	
			
			printf( (buffer.st_mode & S_IRUSR) ? "r" : "-");
			printf( (buffer.st_mode & S_IWUSR) ? "w" : "-");
			printf( (buffer.st_mode & S_IXUSR) ? "x" : "-");
			printf( (buffer.st_mode & S_IRGRP) ? "r" : "-");
			printf( (buffer.st_mode & S_IWGRP) ? "w" : "-");
			printf( (buffer.st_mode & S_IXGRP) ? "x" : "-");
			printf( (buffer.st_mode & S_IROTH) ? "r" : "-");
			printf( (buffer.st_mode & S_IWOTH) ? "w" : "-");
			printf( (buffer.st_mode & S_IXOTH) ? "x " : "-");
			printf(")  ");                
			setpwent();
			pwent = getpwuid(buffer.st_uid);
			printf("Uid: (%d/%s)\t", buffer.st_uid, pwent ? pwent->pw_name : "???");
			setgrent();
			grent = getgrgid(buffer.st_gid);
			printf("Gid: (%d/%s)\n", buffer.st_gid, grent ? grent->gr_name : "???");                        
			printf("Access: %.24s\n",ctime(&buffer.st_atime));
			printf("Modify: %.24s\n",ctime(&buffer.st_mtime));
			printf("Change: %.24s\n",ctime(&buffer.st_ctime));
              }

	}
}
