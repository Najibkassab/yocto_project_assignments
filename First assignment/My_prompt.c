#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
char input[100];
printf("ready!! type anything you want:\r\n");
while(1){
printf("My_prompt>");
fgets(input, sizeof(input), stdin);
if(strcmp(input,"exit\n")!=0){
 printf("My_prompt> you said %s",input);
}else{
 printf("Good Bye!!\r\n");
 exit(0);
 }
}
return 0;
}

