#include <stdio.h>
#include <string.h>
int GAP_PENALTY = 2;

void print_matrix(int c_size, int r_size, int matrix[255][255], char *secuence1, char *secuence2);
int needleman_wunch_gap_penalty(int value, int penalty);
void init_standard_needleman_wunsch(int c_size, int r_size, int matrix[255][255]);

void init_matrix(int c_size, int r_size, int matrix[255][255]) {
  int i, j;

  matrix[0][0] = 0;
  for (i = 1; i < r_size; i++) {
    for (j = 1; j < c_size; j++) {
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

  init_standard_needleman_wunsch(c_size, r_size, matrix);
}

void init_standard_needleman_wunsch(int c_size, int r_size, int matrix[255][255]) {
  int i, j;
  for(i = 1; i < r_size; i++) {
    matrix[i][0] = needleman_wunch_gap_penalty(matrix[i - 1][0], GAP_PENALTY);
  }

  for(j = 1; j < c_size; j++) {
    matrix[0][j] = needleman_wunch_gap_penalty(matrix[0][j - 1], GAP_PENALTY);
  }
}

int needleman_wunch_gap_penalty(int value, int penalty) {
  return (value - penalty);
}

char *int_to_string(int value) {
  static char str[5];
  sprintf(str, "%d", value);
  return str;
}

void print_matrix(int c_size, int r_size, int matrix[255][255], char *secuence1, char *secuence2) {
  int columns_size, rows_size, i, j, columns_index;
  int rows_index = 0;
  char string_values[255] = "    ";
  int output_size;

  columns_size = (int) c_size;
  rows_size = (int) r_size;
  output_size = (int) strlen(string_values);

  for (columns_index = 0; columns_index < (columns_size -1); columns_index++) {
    strcat(string_values, "   ");
    string_values[output_size] = secuence1[columns_index];
    output_size = (int) strlen(string_values);
  }

  strcat(string_values, "\n");
  output_size++;

  for (i = 0; i < rows_size + 1; i++) {
    for (j = 0; j < columns_size + 1; j++) {
      if (i == 0 && j == 0) {
        strcat(string_values, "  ");
        output_size = (int) strlen(string_values); 
      }
      if (j == 0 && i > 1) {
        string_values[output_size] = '\0';
        string_values[output_size] = secuence2[rows_index];
        strcat(string_values, " ");
        output_size = (int) strlen(string_values);
        rows_index++;
      }
      if (j > 0 && i > 0) {
        strcat(string_values, int_to_string(matrix[i - 1][j -1]));
        if ((j + 1)  == (columns_size + 1)) {
          strcat(string_values, "\n");
        } else {
          strcat(string_values, " ");
        }
        output_size = (int) strlen(string_values);
      }
    }
  }

  printf("%s", string_values);
}

void get_upper_secuence(int c_size, int r_size, int values[255][255], char *secuence1, char *secuence2) {
  int i,j, upper_gap, left_gap, diagonal_value, max_value;
  char aux[1] = "";
  char aligment_1[255];
  char aligment_2[255];
  i = r_size;
  j = c_size;

  strcpy(aligment_1, "\n");
  strcpy(aligment_2, "\n");

  while ((i != 0) && (j != 0)) {
    upper_gap = values[i -1][j];
    left_gap = values[i][j -1];
    diagonal_value = values[i -1][j -1];
    max_value = max(upper_gap, left_gap);
    max_value = max(max_value, diagonal_value);

    if (max_value  == upper_gap) {
      strcat(aux, "_");
      strcat(aux, aligment_1);
      strcpy(aligment_1, aux);
      strcpy(aux, "");

      aux[0] = secuence2[i];
      strcat(aux, aligment_2);
      strcpy(aligment_2, aux);
      strcpy(aux, "");

      i--;
    }

    if (max_value == left_gap) {
      strcat(aux, "_");
      strcat(aux, aligment_2);
      strcpy(aligment_1, aux);
      strcpy(aux, "");

      aux[0] = secuence1[j];
      strcat(aux, aligment_1);
      strcpy(aligment_1, aux);
      strcpy(aux, "");

      j--;
    }

    if (max_value == diagonal_value) {
      aux[0] = secuence1[j];
      strcat(aux, aligment_1);
      strcpy(aligment_1, aux);
      strcpy(aux, "");

      aux[0] = secuence2[i];
      strcat(aux, aligment_2);
      strcpy(aligment_2, aux);
      strcpy(aux, "");
      i--;
      j--;
    }
  }

  printf("%s", aligment_1);
  printf("%s", aligment_2);
}

int max(int a, int b) {
  int max;
  max = a > b ? a : b;
  return max;
}

int process_match(char column_char_value, char row_char_value, int evaluation_value) {
  int match_value;
  match_value = (column_char_value == row_char_value) ? 1 : -1;
  return evaluation_value + match_value;
}

int process_cell_value(char column_secuence_char, char row_secuence_char, int diagonal_value, int upper_value, int left_value) {
  int match, gap, up_gap, left_gap;
  match = process_match(column_secuence_char, row_secuence_char, diagonal_value);
  up_gap = needleman_wunch_gap_penalty(upper_value, GAP_PENALTY);
  left_gap = needleman_wunch_gap_penalty(left_value, GAP_PENALTY);
  gap = max(up_gap, left_gap);
  return max(match, gap);
}

void process_needleman_wunsch(int c_size, int r_size, int values[255][255], char *secuence1, char *secuence2) {
  int i, j;

  for(i = 1; i < r_size; i++) {
    for(j = 1; j < c_size; j++) {
      values[i][j] = process_cell_value(secuence1[j - 1], secuence2[i - 1], values[i - 1][j - 1], values[i -1][j], values[i][j -1]);
    }
  }
}

int *needleman_wunsch(int c_size, int r_size, int values[255][255], char *secuence1, char *secuence2) {
  init_matrix(c_size, r_size, values);
  process_needleman_wunsch(c_size, r_size, values, secuence1, secuence2);
  get_upper_secuence(c_size, r_size, values, secuence1, secuence2);
}

int main(int argc, char** argv) {

  char secuence1[10] = "ATTGTGATCC";
  char secuence2[10] = "TTGCATCGGC";
  int values[255][255];
  int c_size, r_size;
  c_size = (int) strlen(secuence1);
  r_size = ((int) strlen(secuence2)) + 1;

  needleman_wunsch(c_size, r_size, values, secuence1, secuence2);
  print_matrix(c_size, r_size, values, secuence1, secuence2);

  return(0);
}
