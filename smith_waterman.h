#include "needleman_wunsh_structs.h"

int process_SW_cell_value(struct Position pos, char column_secuence_char, char row_secuence_char, struct CellAroundValues values) {
  struct MatchResults match_results;
  cell_match_results(column_secuence_char, row_secuence_char, values, &match_results);
  return max_zero(match_results.match, match_results.gap);
}

void process_smith_waterman(int c_size, int r_size, int values[255][255], char *secuence1, char *secuence2) {
  int i, j;

  for(i = 1; i < r_size; i++) {
    for(j = 1; j < c_size; j++) {
      struct Position cell_position;
      struct CellAroundValues cell_values;
      cell_position.row = i;
      cell_position.column = j;
      cell_values.upper = values[i - 1][j];
      cell_values.diagonal = values[i- 1][j -1];
      cell_values.left = values[i][j - 1];
      values[i][j] = process_SW_cell_value(cell_position, secuence1[j - 1], secuence2[i - 1], cell_values);
    }
  }
}

int *smith_waterman(int c_size, int r_size, int values[255][255], char *secuence1, char *secuence2) {
  init_matrix(c_size, r_size, values);
  process_smith_waterman(c_size, r_size, values, secuence1, secuence2);
}