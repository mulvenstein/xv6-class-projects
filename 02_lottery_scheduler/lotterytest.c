#include "syscall.h"
#include "types.h"
#include "user.h"
#include "pstat.h"
#include "param.h"

void spin();

int main(int argc, char *argv[]){

	int tickets[] = {100, 200, 300};
	int pids[] = {0, 0, 0};

	struct pstat info;

	int i, rc;
	// create three children
	for(i = 0; i < 3; i++){
		rc = fork();
		if(rc == 0) {
			settickets(tickets[i]);
			spin();
			exit();
		} else {
			pids[i] = rc;        
		}
	}
	// prevent parent from using too much CPU
	settickets(10);


	// perodically print process information
	for(i = 0; i < 5000; i++){
		sleep(500);
		if(getpinfo(&info) < 0)
			exit();
		printf(1, "PID\tTICKETS\tTICKS\n");
		for (int i = 0; i < NPROC; ++i) {
			if(info.inuse[i] == 1){
				printf(1, "%d\t%d\t%d\n", info.pid[i], info.tickets[i], info.ticks[i]);
			}
		}
	}

	// kill all children
	for (int i = 0; i < 3; ++i) {
		kill(pids[i]);
	}
	for (int i = 0; i < 3; ++i) {
		wait();
	}
	exit();
}

// infinite computing loop
void spin(){
	volatile int sink = 0;
	for(;;){
		sink = sink + 1;
		sink = sink + 1;
		sink = sink + 1;
	}
}

