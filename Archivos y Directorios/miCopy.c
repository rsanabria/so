#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#define BUFFER_SIZE 512

void main(int argc, char *argv[]){
	
	char buffer[BUFFER_SIZE];
	int fd,fd2,readbytes;

	if( (fd=open(argv[1],O_RDONLY)) < 0){
		perror("open");
		exit(-1);
	}

	
	if( (fd2 = creat(argv[2],S_IRUSR |S_IWUSR )) < 0){
		perror("open");
		exit(-1);
	}	

	while((readbytes = read(fd,buffer, BUFFER_SIZE))> 0)
		write(fd2, buffer,readbytes);	


	close(fd);
	close(fd2);

}

