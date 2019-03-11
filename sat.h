#ifndef __SAT_H
#define __SAT_H

#include <stdlib.h>

// Type of connective
typedef enum { AND, OR, NEG, VAR } connective;

// Encoding of a formula in 3-SAT form in C
typedef struct formula
{
  union
  {

    struct // AND (X /\ Y)
    {
      struct formula *f; // [X]
      struct formula *next; // [Y] Points to the next AND clause
    } land; 

    struct // OR (X \/ Y \/ Z)
    {
      struct formula *f1; // [X]
      struct formula *f2; // [Y]
      struct formula *f3; // [Z]
    } lor;

    struct // NEG (!X)
    {
      struct formula *f; // [X]
    } lneg;

    struct // Variable (X)
    {
      int lit; // Int literal (0 for false, 1 for true)
    } lvar;

  };

  connective conn; // Enum for AND, OR, NEG, VAR

} formula;

typedef struct assignment {
  int *map;
  int size;
} assignment;

// Print a formula in string encoding to the console
void pretty_print(formula *f);

// Allocate and zero out memory for a formula of a given type
formula* form(connective c);
// Traverse the formula and allocate an assignment that will make space
// for the highest variable in the formula
assignment* make_assignment(formula *f);

// Cleanup memory allocated for formula and assignment
void free_formula(formula *f);
void free_assignment(assignment *a);

// Interpret function
int interpret(formula *f, assignment *a);

#endif
