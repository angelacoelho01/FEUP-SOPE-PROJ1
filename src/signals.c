#include "signals.h"

extern char *process_path;
extern unsigned int nftot;
extern unsigned int nfmod;

void registerAndIgnore(int sig) {
	signal(sig, registerAndIgnore);

	// printf("Signal %u received by pid %u and ignored!\n", sig, getpid());

	//register on log the received signal
	char SIGRECV[20];

	switch (sig)
	{
	case SIGHUP:
		strcpy(SIGRECV,"SIGHUP");
		break;
	case SIGQUIT:
		strcpy(SIGRECV,"SIGQUIT");
		break;
	case SIGSEGV:
		strcpy(SIGRECV,"SIGSEGV");
		break;
	case SIGPIPE:
		strcpy(SIGRECV,"SIGPIPE");
		break;
	case SIGALRM:
		strcpy(SIGRECV, "SIGALRM");
		break;
	case SIGCHLD:
		strcpy(SIGRECV,"SIGCHLD");
		break;
	default:
		strcpy(SIGRECV,"SIGNALRECEIVED");
		break;
	}

	writeToLogger(getpid(), SIGNAL_RECV, SIGRECV); //received SIGINT
}

void ctrlcReceived(int sig) {
	signal(SIGINT, ctrlcReceived); // reset

	// printf("\nParent received signal %u\n", sig); // to test purposes
	writeToLogger(getpid(), SIGNAL_RECV, STR_SIGINT); //received SIGINT

	int status;

	if (0 == waitpid(-1, &status, WNOHANG)) { // unterminated children exist
		// Send SIGUSR1 to every process with the same groupId as the sender (himself + descendents)
		printf("\n");
		if (kill(0, SIGUSR1) != 0)
			perror("SIGUSR1");
	} else {
		// Send SIGUSR2 to himself
		kill(getpid(), SIGUSR2);
	}
}

void displayInfo(int sig) {
	signal(SIGUSR1, displayInfo); // reset

	writeToLogger(getpid(), SIGNAL_RECV, STR_SIGUSR1); //received SIGUSR1

	// Display current process info
	printf("%u ; %s ; %u ; %u\n", getpid(), process_path, nftot, nfmod);

	// Send SIGUSR2 to the parent - display finished
	if (kill(getppid(), SIGUSR2) != 0)
		perror("SIGUSR2");

	// Send SIGSTOP to himself
	if (kill(getpid(), SIGSTOP) != 0)
		perror("SIGSTOP");
}

void questionPrompt(int sig) {
	signal(SIGUSR2, questionPrompt); // reset

	writeToLogger(getpid(), SIGNAL_RECV, STR_SIGUSR2); //received SIGUSR2

	// Display principal process info
	printf("%u ; %s ; %u ; %u\n", getpid(), process_path, nftot, nfmod);

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
	//printf("Termitating Process PID %u!!...\n", getpid());  // to test purposes

	writeToLogger(getpid(), SIGNAL_RECV, STR_SIGTERM); //received SIGTERM

	exit(EXIT_CTRLC);
}
