/*Includes-------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*Global varibales-----------------------------------*/

/*main function--------------------------------------*/
int main( int argc, char **argv) {
int fd1,fd2;
char c;
ssize_t size;
fd1=open(argv[1],O_RDONLY,0644);
if(-1==fd1) {
 printf("Could not open this file %s \r\n",argv[1]); 
 return -1;
 }
fd2=open(argv[2], O_CREAT|O_RDWR,0644);
if(-1==fd2){
 printf("Could not open this file %s \r\n",argv[2]); 
 return -1;
}

size=read(fd1, &c, 1);
while(size!=0){
if(-1==size){
  printf("Could not read from this file %s \r\n",argv[1]); 
 return -1;
}
 if(-1==write(fd2, &c, 1)){
  printf("Could not write in this file %s \r\n",argv[2]); 
 return -1;
 }
 size=read(fd1, &c, 1);
}
    
    close(fd1);          		//close the first file
    close(fd2);				//close the second file
    return 0;
}

