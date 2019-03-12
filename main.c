#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sat.h"
#include "util.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "usage %s: [FORMULA-FILE]\n", argv[0]);
		exit(1);
	}

	init_lib(argv[1]);

	while (1) {
	  	// Decodes and forms the formula
	    formula *f = next_formula();
			if (f == NULL) {
				break;
			}
			pretty_print(f);
			printf("\n");
		// Makes a default assignment for the formula
	    assignment *a = make_assignment(f);

	    // Calculate end value
	    int end = 0;
	    for(int x = 0; x < a->size; x++)
	    {
	    	 end += ((int) pow((double)10,(double)x));
	    }

	    // Test incremental assignments up until end value
	    int solutionFound = false;
	    do {
	    	if(interpret(f,a) == 1) { solutionFound = true; break; }
	    } while(!incA(a,end));

	    // Test end case and print the satisfiability result
	    if(solutionFound || interpret(f,a) == 1 ) { printf("1\n"); }
	    else { printf("0\n"); }

	    // Free a and f
	    free_assignment(a);
	    free_formula(f);
	}

  free_lib();
  
  return 0;
}
