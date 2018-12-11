// fork hand processes
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
  // setting up variables for get opt
  int chance, opt;
  extern char *optarg;
  extern int optind, opterr, optopt;
  int verbose=0;
  int numP;

  // loop for getopt to parse cmd line args
  while ((opt = getopt (argc, argv, "p:v")) != -1)
    {
      switch (opt)
	{
	// percentage chance is found, record the percentage
	case 'p':
	  chance = atoi(optarg);
	  break;

	// verbose is selected, set verbose to true
	case 'v':
	  verbose = 1;
	  break;
	}
    }
    // setting number of child processes to create from optind
  
    if (opt == -1){
    numP = atoi(argv[optind]);
    }
  

  // turn chance back into a string in order to pass it to hand
  int length = snprintf( NULL, 0, "%d", chance );
  char* chan = malloc( length + 1 );
  snprintf( chan, length + 1, "%d", chance );
   
  // setting up PID stuff for forking and new processes
  pid_t pid;
  int x = 1;
  int processCounter;
  double failed = 0.00, passed = 0.00;
  int i;

  // loop for creating child processes one at a time
  for (processCounter = 0; processCounter < numP; processCounter++)
  {
    pid = fork();
    // child process
    if (pid == 0) {
      // set arglist for calling hand
      char * argv_list[] = {"./hand",chan,NULL}; 
  
      // if call to hand failed
      if(execv("./hand",argv_list) == -1){
        printf("Call failed\n");
      }

    }
    else { // parent process
      
      // wait for exit status of child
      int waitstatus;
      wait(&waitstatus);
      i = WEXITSTATUS(waitstatus);

      // if child returns 10, pass, else its a fail 
      if (i == 10){
	passed++;
      }
      else{
	failed++;
      }

      // if verbose option is selected, print child PID's and results
      if(verbose){
	if (i == 10){
	  printf("PID %d returned %s.\n", (int)pid, "Success");
	}
	else{
	  printf("PID %d returned %s.\n", (int)pid, "Failed");
	} 
      }
    }
  }

  // print out stats
  printf("Created %d processes.\n",numP);
  printf("Succeeded -  %2.0f  \n", passed);
  printf("Success -  %4.2f\%  \n", (passed/(passed+failed))*100.0);
  printf("Failed -  %2.0f  \n", failed);
  printf("Failure -  %4.2f\%  \n", (failed/(passed+failed))*100.0);

  // release memory
  free(chan);

  exit(0);
}