/*Includes-------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

/*Global varibales-----------------------------------*/


/*main function-------------------------------------*/
int main( int argc, char **argv) {
for(int i=1;i<argc;i++){
   printf("%s ",argv[i]);
}
printf("\r\n");
    return 0;
}

