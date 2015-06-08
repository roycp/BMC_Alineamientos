#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aligments.h"
#include "print_aligment.h"

// to run: ./needleman_wunsch 0 secuence1 (top) secuence2 (left)
// 0 Needlaman-Wunsch, 1 Smith-Waterman
int main(int argc, char** argv) {
  printf ("\nTo run: ./needleman_wunsch 0 secuence1 secuence2\n");
  printf ("0 Needlaman-Wunsch, 1 Smith-Waterman\n");
  printf ("On the matrix, secuence1: top sequence, secuence2: left sequence\n\n");
  int SW = 0;
  if (argc > 1) {
    SW = atoi(argv[1]);
  }
  else
    return 0;

  int values[255][255];
  int c_size, r_size;
  init_arrow_matrix();
  c_size = (int) strlen(argv[2]) + 1;
  r_size = ((int) strlen(argv[3])) + 1;

  if (SW) {
    smith_waterman(values, argv[2], argv[3]);
    print_simple_matrix (c_size, r_size, values);
  } else {
    needleman_wunsch(values, argv[2], argv[3]);
    print_simple_matrix (c_size, r_size, values);
    Aligment(r_size-1, c_size-1, argv[2], argv[3]);
    print_char_matrix (c_size, r_size, arrows);
  }

  return 0;
}
