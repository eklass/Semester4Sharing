#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFF_SIZE 1024 
#define PARSE_ARR_SIZE 100

char ** parseInput(char input[]){
	//Entferne NewLine
	strtok(input, "\n");
	//Lege 2D-Array auf den HEAP
	char **buffer = (char**)malloc(PARSE_ARR_SIZE*sizeof(char*));
	if(buffer == NULL){
		perror("\nparseInput(): Fehler bei malloc!!!\n");
	}
	
	//split string
	char delimiter[] = " ";
	char delimiter2[] = "$";
	char *ptr;
	ptr = strtok(input, delimiter);
	int i;
	
	for(i=0;ptr != NULL;i++) {
		
		char * blub = ptr;
		if(blub[0]){
			//strtok(ptr,delimiter2);
			//buffer[i]=getenv(ptr);
		} else {
			buffer[i]=ptr;
		}
		ptr = strtok(NULL, delimiter);
	}
	return buffer;
}

void changeDirectory(char **parsed){
	//case "cd"
	if(strcmp(parsed[1],"") == 0){
		int ret = chdir(getenv("HOME"));
		if(ret != 0){
			perror("changeDirectory(): chdir failed! (1)");
		}
	} else{
		//case "cd X"
		char buf[PATH_MAX+1];
		const char * tmp = realpath(parsed[1],buf);
		//printf("\nDEBUG:'%s','%s'\n",tmp,parsed[1]);
		int ret = chdir(tmp);
		if(ret != 0){
			perror("changeDirectory(): chdir failed! (2)");
		}
	}
}

void handleSet(char **parsed){
	
}

void createChild(char **parsed){
	pid_t pid = fork();
	if(pid <0){
		perror("fehler bei fork.");
	} else if( pid == 0){//child
		execvp(parsed[0],parsed);
		exit(0);
		
	} else if( pid > 0 ){//parent waits
		waitpid(pid,NULL,0);
	}
	
}

int main(){
	char userIn[BUFF_SIZE];
	char userName[BUFF_SIZE];
	getlogin_r(userName, BUFF_SIZE);

	printf("Willkommen zur Minden-Mini-Shell!\n");
	
	//Set initial workingdirectory
	int ret = chdir(getenv("HOME"));
		if(ret != 0){
			perror("main(): chdir failed! (1)");
		}
	
	//mainloop
	while(1){
		//fetching user input + splitting string
        char my_cwd[1024];
        printf("%s@%d ~$ ", userName,getcwd(my_cwd,1024));
		fgets(userIn,BUFF_SIZE,stdin);
		//printf("\nINPUT: %s\n",userIn);
		char **parsed=parseInput(userIn); //access: parsed[0]
				
		
		if(strcmp(parsed[0],"exit") == 0
					|| strcmp(parsed[0],"exit\n") == 0){//check for exit
			printf("Shell Terminated.");
			exit(0);
		} else if(strcmp(parsed[0],"cd") == 0
					|| strcmp(parsed[0],"cd\n") == 0){//check cd
			changeDirectory(parsed);
		} else if(strcmp(parsed[0],"set") == 0
					|| strcmp(parsed[0],"set\n") == 0){//check set
			handleSet(parsed);
		} else{ //fork
		createChild(parsed);
		}
		
		free(parsed);
	}

	

	return 1;
}
