#include "signals.h"

pid_t pid = -1;

void handler_ctrlc_parent(int sig) {
	signal(SIGINT, handler_ctrlc_parent); // reset 
	
	// recebe o signal
	printf("Parent recebeu o signal %u do ctrl-c\n", sig);
	
	if (pid != -1 && pid != 0) { // HAS A CHILD??
		// se tiver filhos!  - envia para o grupo dos filhos?
		if (kill(pid, SIGUSR1) != 0) // TERMINAR OS PROCESSOS DE FILHOS/NETOS TODOS 
			perror("Error sending SIGUSR1 to children!");
	} else {
		// senao tiver filhos! - envia SIGUSR2 para si proprio
		kill(getpid(), SIGUSR2);
	}
}

void display_child_info(int sig) {
	signal(SIGUSR1, display_child_info); // reset 
	
	// --> fazer display da informação do processo em execução
	printf("FILHO: Sou o processo %u; (info extra ...)\n", getpid());
		
	// enviar SIGUSR2 aos seus pais - indica que acabaram o seu display
	if (kill(getppid(), SIGUSR2) != 0)
		perror("Error sending SIGUSR2 to parent!");
	
	// fazer stop a eles proprios
	if (kill(getpid(), SIGSTOP) != 0)
		perror("Error sending SIGSTOP to him self"); // este sinal nao pode ser tratado
}

void make_question(int sig) {

    char c;

	signal(SIGUSR2, make_question); // reset 
	
	// --> fazer display da info do processo principal - pai supremo
	printf("PAI: Sou o processo %u; (info extra ...)\n", getpid());
	
	// --> faz a pergunta e recebe a resposta
	printf("\nPretende mesmo terminar o programa?(y/n)\n");
	scanf("%c", &c); // just to test purposes
	
	if (c == 'y') { 
		// really wants to terminate
		if (kill(pid, SIGCONT) != 0) // TERMINAR OS PROCESSOS DE FILHOS/NETOS TODOS 
			perror("Error sending SIGCONT to the descendents");
		if (kill(pid, SIGTERM) != 0) // TERMINAR OS PROCESSOS DE FILHOS/NETOS TODOS 
			perror("Error sending SIGTERM to the descendents");
		if (kill(getpid(), SIGTERM) != 0)
			perror("Error sending SIGTERM to him self"); // TERMINAR ELE PROPRIO
	} else { 
		// continue processing
		if (kill(pid, SIGCONT) != 0) // TERMINAR OS PROCESSOS DE FILHOS/NETOS TODOS 
			perror("Error sending SIGCONT to the child");
	}
}


void handler_term(int sig) {
	printf("Termitating!!...\n"); // to registrate the signal
	exit(EXIT_CTRLC); 
}
