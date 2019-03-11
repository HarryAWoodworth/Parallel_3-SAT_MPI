#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

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
	// Makes a default assignment for the formula
    assignment *a = make_assignment(f);

// do your thing

    pretty_print(f);
    printf("\n");
    int returnVal = interpret(f,a);
    printf("Answer: %d\n",returnVal);
	
	/*
		a->map[0] = 1;
		a->map[1] = 1;
		a->map[2] = 0;
	*/

    free_assignment(a);
    free_formula(f);
  }

	free_lib();
  
  return 0;
}
