/*Includes-------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

/*Global varibales-----------------------------------*/


/*main function--------------------------------------*/
int main(int argc, char **argv) {
char *PWD;
size_t sizeofPWD;
PWD=getcwd(PWD, sizeofPWD);
printf("current directory is:%s\r\n",PWD);
    return 0;
}

