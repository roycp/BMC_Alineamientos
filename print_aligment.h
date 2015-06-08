void PrintCellAligment(int i, int j, char* secuence1, char* secuence2, int gap_up, int gap_left) {
  if (gap_up == 1)
    printf ("_  %c\n", secuence2[i]);
  else if (gap_left == 1)
    printf ("%c  _\n", secuence1[j]);
  else
    printf ("%c  %c\n",secuence1[j], secuence2[i]);
}

void Aligment(int i, int j, char* secuence1, char* secuence2) {
  printf ("Aligment \nup down \n");

  while(i != 0 || j != 0) {
    char direction = arrows[i][j];

    if (((direction >> 1) & 0x01) == 1)  { //check diagonl
      PrintCellAligment (i-1, j-1, secuence1, secuence2, 0, 0);
      i -= 1;
      j -= 1;
    }
    else if (((direction >> 0) & 0x01) == 1) { //check up
      PrintCellAligment (i-1, j, secuence1, secuence2, 1, 0);
      i -= 1;
    }
    else if (((direction >> 2) & 0x01) == 1) { //check left
      PrintCellAligment (i, j-1, secuence1, secuence2, 0, 1);
      j -= 1;
    }
  }
}

void print_simple_matrix (int c_size, int r_size, int matrix[255][255]) {
  int i, j;
  printf ("\nMatrix\n");
  for (i = 0; i < r_size; i++) {
    for (j = 0; j < c_size; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf ("\n");
  }
}

void print_char_matrix (int c_size, int r_size, char matrix[255][255]) {
  int i, j;
  printf ("\nArrows Matrix\n");
  printf ("1 Up, 2 Diagonal, 4 Left\n");
  printf ("3 Up-Diagonal, 5 Up-Left, 6 Diagonal-Left\n");
  printf ("7 All directions\n");
  for (i = 0; i < r_size; i++) {
    for (j = 0; j < c_size; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf ("\n");
  }
}