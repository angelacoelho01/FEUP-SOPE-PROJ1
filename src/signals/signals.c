#include "signals.h"

void handler_ctrlc_parent(int sig) {
	signal(SIGINT, handler_ctrlc_parent); // reset 
	
	// Receives signal
	printf("\nParent received signal %u\n", sig);
	
	int status;
	pid_t ret = waitpid(-1, &status, WNOHANG);
	
    if (ret == 0) { // unterminated children exist!
		// if there are child processes! - sends to child group		
		if (kill(0, SIGUSR1) != 0) // SEND SIGNAL TO EVERY PROCESS WITH SAME GROUP ID - PARENT + DESCENDANTS
			perror("Error sending SIGUSR1 to children!");
	}

    else {
		// if there aren't descendants - send signal 2 to himself
		kill(getpid(), SIGUSR2);
	}
}


void display_child_info(int sig) {
	signal(SIGUSR1, display_child_info); // reset 
	
	// --> Display current process info <--
	printf("CHILD: Process no %u; (info extra ...)\n", getpid());
		
	// send signal 2 to parents - display finished
	if (kill(getppid(), SIGUSR2) != 0)
		perror("Error sending SIGUSR2 to parent!");
	
	// STOP himself
	if (kill(getpid(), SIGSTOP) != 0)
		perror("Error sending SIGSTOP to himself"); 
}

void term_prompt(int sig) {

    char c;

	signal(SIGUSR2, term_prompt); // reset 
	
	// --> Display Parent process info - Supremo
	printf("PARENT: Process no %u; (info extra ...)\n", getpid());
	
	// --> Confirm exit prompt
	printf("\nDo you wish to continue? (y/n)\n");
    
	scanf("%c", &c);
    flush_in();
	
	if (c == 'n') { 
		// really wants to terminate
		
		if (kill(0, SIGTERM) != 0) // Terminate all processes including himself
			perror("Error sending SIGTERM to the descendents");

	} 
    
    else { 
		// continue processing descendants
		if (kill(0, SIGCONT) != 0) 
			perror("Error sending SIGCONT to the child");
        printf("Resuming...\n");
	}
}

void handler_term(int sig) {
	printf("Termitating!!...\n"); // to registrate the signal
	exit(EXIT_CTRLC); 
}
