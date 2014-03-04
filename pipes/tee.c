#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define SIZE 512

int main(int charc, char **argv)
{
	pid_t pid;
	int tuberia[2], readbytes;
	char buffer[SIZE], buffer2[SIZE];
	FILE *archivo;
	pipe(tuberia);
	
	if ( (fork()) == 0) {
		archivo = fopen(argv[1], "w");
		close (tuberia[1]);
		while ( (readbytes = read(tuberia[0], buffer, SIZE)) > 0 ) {
			write(1, buffer, readbytes);
			fprintf(archivo,"%s",buffer);
		}
		close(tuberia[0]);
		fclose(archivo);
	}
	else {
    		close( tuberia[0] );
		while ( (readbytes = read(0, buffer2, SIZE)) > 0 )
			write(tuberia[1], buffer2, readbytes);
			
	close(tuberia[1]);

}

}
