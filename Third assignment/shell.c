/*Includes-------------------------------------------*/
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/*PreProcessor Variables-----------------------------*/
#define MAXNUMBEROFLOCALVARIABLE 100
#define MAXNUMBEROFSTRINGLITERAL 100

/*Global Variables-----------------------------------*/
char LocalVariable[MAXNUMBEROFLOCALVARIABLE][MAXNUMBEROFSTRINGLITERAL];

/*Functions Prototype --------------------------------*/
int wordcount(char *buffer);
void wordToken(char *buffer);
void CommandPareser(void);
bool isLocalVariable(char *buffer);
bool FindVariable(char *buffer, int *location);
void ParserEnv(char buffer[], char *NamerBuffer, char *ValueBuffer);
/*main function--------------------------------------*/
int main(int argc, char **argv) {
  pid_t PIDValue = 0;
  int *status;

  while (1) {
    PIDValue = fork();
    if (PIDValue == -1) {
      printf("error while forking\r\n");
      return -1;
    } else if (PIDValue == 0) {
      printf("Enter your command>>");
      CommandPareser();
    } else {
      wait(status);
    }
  }
  return 0;
}

/*Command Parser ------------------------------------------*/
void CommandPareser(void) {
  char buf[100];
  fgets(buf, 100, stdin);
  if (buf[0] != 0x0A) {
    buf[strlen(buf) - 1] = '\0';
    wordToken(buf);
  } 
}

/*Words counter --------------------------------------------*/
int wordcount(char *buffer) {
  int count = 0;
  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == ' ' && buffer[i+1] != ' ')
      count++;
  }
  count++;
  return count;
}

/*Words tokner ---------------------------------------------*/
void wordToken(char *buffer) {
  char nameenv[100] = {0};
  char valeenv[100] = {0};
  int VariableLocation = 0;
  static int LocalIndex = 0;
  char *ptr = NULL;
  int CommandNumber = wordcount(buffer);
  char *Command[CommandNumber];
  int index = 0;
  if (!isLocalVariable(buffer)) {
    ptr = strtok(buffer, " ");
    while (ptr != NULL) {
      Command[index] = ptr;
      index++;
      ptr = strtok(NULL, " ");
    }
    if (Command[0][0] == '/') {
      char *argv1[] = {NULL};
      char *envp1[] = {NULL};

      for (int k = 0; k <= CommandNumber; k++) {
        argv1[k] = Command[k];
      }
      argv1[CommandNumber] = NULL;
      execve(Command[0], argv1, envp1);
    } else if (!strcmp(Command[0], "set")) {
      for (int i = 0; i < LocalIndex; i++) {
        printf("Local_Variable[%d]:%s\r\n", i, LocalVariable[i]);
      }
    } else if (!strcmp(Command[0], "export")) {
      if (FindVariable(Command[1], &VariableLocation)) {
        ParserEnv(LocalVariable[VariableLocation], nameenv, valeenv);
        if (!setenv(nameenv, valeenv, 1))
          printf("added successfully\r\n");
        else
          printf("add failed\r\n");
      } else
        printf("Variable not found\r\n");

    } else {
      char *argv2[] = {NULL};
      for (int k = 0; k <= CommandNumber; k++) {
        argv2[k] = Command[k];
      }
      argv2[CommandNumber] = NULL;
      execvp(Command[0], argv2);
    }
  } else {
    strcpy(&LocalVariable[LocalIndex][0], buffer);
    LocalIndex++;
  }
}

/*Local Variable ---------------------------------------------*/
bool isLocalVariable(char *buffer) {
  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == '=')
      return true;
  }
  return false;
}

/*Find Variable ---------------------------------------------*/
bool FindVariable(char *buffer, int *location) {
  bool result = false;
  for (int i = 0; i < MAXNUMBEROFLOCALVARIABLE; i++) {
    if (LocalVariable[i][0] == buffer[0]) {
      result = true;
      *location = i;
    }
  }
  return result;
}
/*Parser Environment Variable ---------------------------------------------*/
void ParserEnv(char *buffer, char *NamerBuffer, char *ValueBuffer) {
  int Namelen = 0, Valuelen = 0;

  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == '=')
      break;
      else
      Namelen++;
  }

  strncpy(&NamerBuffer[0], &buffer[0], Namelen);

  for (int i = Namelen; i < strlen(buffer); i++) {
    if (buffer[i] == '0')
      break;
      else 
      Valuelen++;
  }
  strncpy(ValueBuffer, &buffer[Namelen + 1], Valuelen);
}
