#include <stdio.h>
#include <stdlib.h>


main(){

int pid, pid2;
int c= 0;
printf("Proceso %d , hijo de 1(el shell)\n",getpid());
while(c < 3){
pid = fork();
if (pid == 0)
	printf("Proceso %d , hijo de %d\n",getpid(),getppid());

	if (pid != 0 ){
		wait(NULL);
		pid2 = fork();
		if (pid2 == 0)
		printf("Proceso %d , hijo de %d\n",getpid(),getppid());
		if (pid2 != 0){
			wait(NULL);
			exit(1);
		}
	}
	c++;
}
}