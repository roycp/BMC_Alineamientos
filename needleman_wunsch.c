#include <stdio.h>
#include <string.h>


int matrix[255][255];

void init_matrix(size_t c_size, size_t r_size, int *matrix[255][255]) {
  int i, j;
  int c_length = (int) c_size;
  int r_length = (int) r_size;

  matrix[0][0] = 0;
  for (i = 1; i < r_length; i++) {
    for (j = 1; j < c_length; j++) {
      if ( j == 0) {
        matrix[i][j] = matrix[i-1][j] - 2;
      }
      if (i == 0) {
        matrix[i][j] = matrix[i][j -1] - 2;
      }
      if (i != 0 && j != 0) {
        matrix[i][j] = 0;
      }
    }
  }
  //for(i = 1; i < rows_lenght; i++) {
  //  matrix[i][0] = matrix[i-1][0] - 2;
  //}

  //for(j = 1; j < columns_lenght; j++) {
  //  matrix[0][j] = matrix[0][j - 1] - 2;
  //}
}

char *int_to_string(int value) {
  static char str[5];
  sprintf(str, "%d", value);
  return str;
}

void print_matrix(size_t c_size, size_t r_size, int *matrix[255][255], char *secuence1, char *secuence2) {
  int columns_size, rows_size, i, j, columns_index;
  int rows_index = 0;
  char string_values[255] = " ";
  int output_size;

  columns_size = (int) c_size;
  rows_size = (int) r_size;
  output_size = (int) strlen(string_values);

  for (columns_index = 0; columns_index < columns_size; columns_index++) {
    string_values[output_size + 1] = ' ';
    string_values[output_size] = secuence1[columns_index];
    output_size = (int) strlen(string_values);
  }

  strcat(string_values, "\n");

  for (i = 0; i < rows_size; i++) {
    for (j = -1; j < columns_size; i++) {
      if (j = -1) {
         string_values[output_size] = secuence2[rows_index];
         string_values[output_size + 1] = ' ';
         output_size = (int) strlen(string_values);
      } else {
        strcat(string_values, int_to_string(matrix[i][j]));
        if ((j + 1) == columns_size) {
          strcat(string_values, "\n");
          rows_index++;
        } else {
          strcat(string_values, " ");
        }
      }
    }
  }

  printf("%s", string_values);
}

int *needleman_wunsch(size_t c_size, size_t r_size, int *values[255][255], char *secuence1, char *secuence2) {
  init_matrix(c_size, r_size, values);
  print_matrix(c_size, r_size, values, secuence1, secuence2);
}

int main(int argc, char** argv) {

  char secuence1[7] = "AGTCCTA";
  char secuence2[7] = "GTCCTTA";
  //int values[7][7];
  size_t c_size, r_size;
  c_size = strlen(secuence1);
  r_size = strlen(secuence2);
  int values[255][255];

  needleman_wunsch(c_size, r_size, values, secuence1, secuence2);

  return(0);
}
