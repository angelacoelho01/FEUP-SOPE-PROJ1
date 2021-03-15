#include "signals.h"

void ctrlcReceived(int sig) {
	signal(SIGINT, ctrlcReceived); // reset 
	
	// printf("\nParent received signal %u\n", sig); // to test purposes
	
	int status;
	
    if (0 == waitpid(-1, &status, WNOHANG)) { // unterminated children exist
		// Send SIGUSR1 to every process with the same groupId as the sender (himself + descendents)
		if (kill(0, SIGUSR1) != 0) 
			perror("SIGUSR1");
	} else {
		// Send SIGUSR2 to himself
		kill(getpid(), SIGUSR2);
	}
}

void displayInfo(int sig) {
	signal(SIGUSR1, displayInfo); // reset 
	
	// --> Display current process info <--
	printf("Process PID: %u; (info extra ...)\n", getpid());
		
	// Send SIGUSR2 to the parent - display finished
	if (kill(getppid(), SIGUSR2) != 0)
		perror("SIGUSR2");
	
	// Send SIGSTOP to himself
	if (kill(getpid(), SIGSTOP) != 0)
		perror("SIGSTOP"); 
}

void questionPrompt(int sig) {
	signal(SIGUSR2, questionPrompt); // reset 

	// --> Display principal process info <--
	printf("Process PID: %u; (info extra ...)\n", getpid());
	
	// Confirm exit prompt
	printf("\nDo you really want to terminate the program (y/n)? ");
	char answer = readAnswer();
	
	// Continue all processes including himself
	if (kill(0, SIGCONT) != 0) 
		perror("SIGCONT");
	
	if (answer == 'y') { 
		// Terminate all processes including himself
		if (kill(0, SIGTERM) != 0) 
			perror("SIGTERM");
	} 
}

void terminate(int sig) {
	// to registrate the signal
	printf("Termitating!!...\n");  // to test purposes
	
	exit(EXIT_CTRLC); 
}