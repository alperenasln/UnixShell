#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h> 
#define NUM_THREADS 16

//Function declarations that we used for this assignment
int scan(char *str, char split);
void *systemcall(void *call);
void receive(char *process);
void split_process(char *line);
void interactiveMode();

// Scans the input string and returns number of | and ;
int scan(char *str, char split) {
	int i = 0;
	int j = 0;
	while(str[i] != '\0') {
		int c = (int) str[i];
		if(c == (int) split) {
			j++;
		}

		i++;
	}
	
	return j;
}

// Function for systemcalls which comes from threads
void *systemcall(void *call) {
	char *consoleCommand;
    int i;
    consoleCommand = (char *) call;
	i = system(consoleCommand);
	if (i == -1) {
		printf("There is no such that command as %s\n", consoleCommand);
	}
	
	pthread_exit(NULL);
}

// Takes the threads and receives it to pthread.
// Another functionality of it is splits the processes.
void receive(char *process) {
	pthread_t threads[NUM_THREADS];
	int thread_index = scan(process, ';');
	int exitting = 0;
	int rc;
	char *ptr = strtok(process, ";");
	char **thread_alloc = (char **)malloc((thread_index++ + 1) * sizeof(char *));

	int i = 0;
	while(ptr != NULL){
		thread_alloc[i] = (char *)malloc(100 * sizeof(char));
		strcpy(thread_alloc[i], ptr);
		if(!strcmp(thread_alloc[i], "quit")){
            exitting = 1;
        }

        ptr = strtok(NULL, ";");
		i++;
	}
	//Creates threads and return code
	for(int i = 0; i < thread_index; i++) {
		rc = pthread_create(&threads[i], NULL, systemcall, (void *)thread_alloc[i]);
		pthread_join(threads[i], NULL);
		if (rc) {
            printf("Error! Return code is %d\n", rc);
            exit(-1);
       }
	}

	if(exitting){
        	exit(0);
    }
}

// Splits the line and send the process to thread with receive function.
void split_process(char *line) {
	int seps = scan(line, '|');
	char *ptr = strtok(line, "|");
	char **process_arr = (char **)malloc((seps++ + 1) * sizeof(char *));

	int i = 0;
	while(ptr != NULL){
		process_arr[i] = (char *)malloc(100 * sizeof(char));
		strcpy(process_arr[i], ptr);
		
		ptr = strtok(NULL, "|");
		i++;
	}	

	for(int i = 0; i < seps; i++) {
		if (process_arr[i] != NULL) {
			receive(process_arr[i]);
		}
	}
}
//Interactive mode 
void interactiveMode(){
    char input[255];
    while(1) {
        
			printf("prompt> ");
			gets(input);
			split_process(input);
		}
		system("clear");
}


int main(int argc, char *argv[]) {
    
	char input[255];
	FILE* file;
	
    system("clear");
	
    printf("|----------------------------------|\n");
	printf(" Shell is waiting for your commands  \n");
	printf("|----------------------------------|\n");

	// Batch mode 
	if(argv[1] != NULL) {
		
        int i = 1;
		while(argv[i] != NULL) {
			int j = 1;
			char line[512];
			file = fopen(argv[i], "r");
			while(fgets(line, sizeof(line), file) != NULL) {
				printf("In %d line, file %d: %s", j, i, line);
				receive(line);
				printf("\n");
				j++;
			}
			
			i++;
			fclose(file);
		}
        
		
	}
	
	else {
        interactiveMode();
	

    }
	return 0;
}
