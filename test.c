#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
char input[100];

printf("ready!! type anything you want:\r\n");
while(1){
fgets(input, sizeof(input), stdin);
if(strcmp(input,"exit\n")!=0){
 printf("you said %s\r\n",input);
}else{
 printf("Good Bye!!\r\n");
 exit(0);
 }
}
return 0;
}

