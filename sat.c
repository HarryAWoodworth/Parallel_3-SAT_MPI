#include "sat.h"

#include <stdlib.h>
#include <stdio.h>

// Form a formula with default values from a connective and return it
// (AND, OR, NEG, VAR)
formula* form(connective c)
{
  // Allocate space for a formula
  formula *f = malloc(sizeof(formula)); 
  // Save the type of formula
  f->conn = c;
  // Switch on the type, set things to default (NULL or -1)
  switch (f->conn) {
    case AND:
      f->land.f = NULL;
      f->land.next = NULL;
      break;
    case OR:
      f->lor.f1 = NULL;
      f->lor.f2 = NULL;
      f->lor.f3 = NULL;
      break;
    case NEG:
      f->lneg.f = NULL;
      break;
    case VAR:
      f->lvar.lit = -1;
      break;
  }
  // Return the formula
  return f;
}

// Free a created formula
void free_formula(formula *f) {
  switch (f->conn) {
    case AND:
      free_formula(f->land.f);
      if (f->land.next != NULL) {
        free_formula(f->land.next);
      }
      break;
    case OR:
      free_formula(f->lor.f1);
      free_formula(f->lor.f2);
      free_formula(f->lor.f3);
      break;
    case NEG:
      free_formula(f->lneg.f);
      break;
    case VAR:
      break;
  }
	free(f);
} 

void pretty_print(formula *f) {
  switch (f->conn) {
    case AND:
      pretty_print(f->land.f);
      if (f->land.next != NULL) {
        printf(" /\\ ");
        pretty_print(f->land.next);
      }
      break;
    case OR:
      printf("(");
      pretty_print(f->lor.f1);
      printf(" \\/ ");
      pretty_print(f->lor.f2);
      printf(" \\/ ");
      pretty_print(f->lor.f3);
      printf(")");
      break;
    case NEG:
      printf("!");
      pretty_print(f->lneg.f);
      break;
    case VAR:
      printf("%d", f->lvar.lit);
      break;
  }
}

// Get the highest var in the formula
int highest(formula *f) {
  switch (f->conn) {
    case AND: {
      int h1 = highest(f->land.f);
      if (f->land.next != NULL) {
        int h2 = highest(f->land.next);
        return h1 > h2 ? h1 : h2;
      } else {
        return h1;
      }
    }
    case OR: {
      int h1 =  highest(f->lor.f1);
      int h2 = highest(f->lor.f2);
      int h3 = highest(f->lor.f3);
      int h4 = h1 > h2 ? h1 : h2;
      return h4 > h3 ? h4 : h3;
    }
    case NEG:
      return highest(f->lneg.f);
    case VAR:
      return f->lvar.lit;
    default:
      return -1;
  }
}

// Create an assignment for the formula, set everything to 0 default
assignment* make_assignment(formula *f) {
  int size = highest(f) + 1;
  assignment *a = malloc(sizeof(assignment));
  a->map = malloc(sizeof(int) * size);
  a->size = size;
  for (int i = 0; i < a->size; i++) {
    a->map[i] = 0;
  }
  return a;
}

void free_assignment(assignment *a) {
  free(a->map);
	free(a);
}

// Evaluates f (0: false 1: true)
int interpret(formula *f, assignment *a)
{
  switch (f->conn) {
    // Go through the chain of clauses and return 
    // 1 if all are true, otherwise return 0
    case AND: {
      if(interpret(f->land.f,a) == 1) {
        if(f->land.next != NULL) {
          return interpret(f->land.next,a);
        } 
        return 1;
      } 
      return 0;
    }
    // If any of the three formulas return true, return 1
    // otherwise return 0
    case OR: {
      if(interpret(f->lor.f1,a) == 1) return 1;
      if(interpret(f->lor.f2,a) == 1) return 1;
      if(interpret(f->lor.f3,a) == 1) return 1;
      return 0;
    }
    // Return the opposite of the interpretation
    // of the formula
    case NEG: {
      int ret = interpret(f->lneg.f,a);
      if(ret == 0) return 1;
      if(ret == 1) return 0;
      return -1;
    }
    // Return the literal from assignment map (0 or 1)
    case VAR: {
      return a->map[f->lvar.lit];
    }
    default: 
      return -1;
  }
}

// Increment the boolean values in a 
// by simulating binary addition
// return true if a is all 1's
bool incA(assignment *a)
{
  bool allOnes = true;
  for(int index = 0; index < a->size; index++)
  {
    if(a->map[index] == 0) {
      allOnes = false;
      break;
    }
  }
  if(allOnes) { return true; }

  ////////////////////// STOPPPED HERE!!!!!
}
