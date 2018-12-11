// Hand program that takes a success percentage p, and returns success or failure based on that percentage

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> 
#include <string.h>
#include <gsl/gsl_rng.h>
//#include <mytools.h>
gsl_rng * r;
  
int main(int argc, char** argv) 
{ 

  int chance, opt;
  extern char *optarg;
  extern int optind, opterr, optopt;
  // get tim ein milliseconds
  extern unsigned long int gsl_rng_default_seed;
  const gsl_rng_type * T;
  struct timeval tv;
  gettimeofday(&tv, NULL);
  gsl_rng_env_setup();
  gsl_rng_default_seed = (tv.tv_usec);
  unsigned long int L  = time(0);

  T = gsl_rng_default;
  r = gsl_rng_alloc(T);
  unsigned long int rngNormProb =  gsl_rng_get(r);
  double uniform = gsl_rng_uniform(r);


  opt = getopt(argc, argv, "");
  if (opt == -1){
      chance = atoi(argv[optind]);
  }
  else{
      fprintf(stderr, "usuage is ./hand <successPercentage> ");
     }
    
   

    float probability = ((rngNormProb)/(gsl_rng_max(r)+1))%100;
    // generate random number, if within succesful range, set Successful to true
    
    bool Successful = ((100*uniform) < chance);
 
    // if successful, print success, else print failure
   
    if (Successful==true){

      exit(10);
    }
    else{

      exit(0);
    }
   
   return 0; 
} 